
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"

#include "OpenGUI_Font.h"
#include "OpenGUI_FontCache.h"
#include "OpenGUI_FontAtlas.h"
#include "OpenGUI_TextureDataRect.h"
#include "OpenGUI_Imageset.h"

namespace OpenGUI{
	Texture* FontCache::getDebugTexture()
	{
		//FontAtlasList::reverse_iterator iter = mFontAtlasList.rbegin();
		FontAtlasList::iterator iter = mFontAtlasList.begin();
		//if(iter != mFontAtlasList.rend()){
		if(iter != mFontAtlasList.end()){
			FontAtlas* atlas = (*iter);
			return atlas->GetImageset()->getTexture();
		}
		return 0;
	}


	int _calcNewAtlasDimension(int estimatedDim)
	{
		return 512;
		/*
			This is just a fun little algorithm I decided to add that attempts to
			guess the best size in a dimension based on the glyph dimension.
			At the moment, it does an okay job, but really isn't anything that
			impressive.
		*/

		const int glyphSpacing = 2; //spacing used by FontAtlas
		const int minDimension = 64; //minimum dimension allowed
		const int maxDimension = 2048; //maximum dimension allowed
		const int defaultDimension = 512; //soft maximum dimension

		estimatedDim += (glyphSpacing * 2); //adjust estimate to account for glyph spacing

		//first establish the smallest size we can possibly fit into
		int size = minDimension;
		while(size < estimatedDim && size < maxDimension)
			size = size<<1;

		//catch sizes that just barely fit in the largest possible dimension.. (wtf are they doing?)
		if(size >= maxDimension){
			//that's the best we can do!
			return maxDimension;
		}

		//now try to work some freakish nonsensical magic in a vain attempt at guessing an appropriate size 
		int defaultWastedSpace = defaultDimension % estimatedDim;
		int idealWastedSpace = maxDimension;
		int idealSize = size;
		while(size <= maxDimension){
			int wastedSpace = size % estimatedDim;

			if(size <= defaultDimension){
				if(idealWastedSpace >= wastedSpace){ 
					idealWastedSpace = wastedSpace;
					idealSize = size;
				}
			}else{
				if(idealWastedSpace > wastedSpace){ 
					idealWastedSpace = wastedSpace;
					idealSize = size;
				}
			}

			size = size<<1;
		}

		return idealSize;
	}

	
	//############################################################################
	FontCache::FontCache()
	{
		LogManager::SlogMsg("INIT", OGLL_INFO3) << "Creating FontCache..." << Log::endlog;
	}
	//############################################################################
	FontCache::~FontCache()
	{
		LogManager::SlogMsg("SHUTDOWN", OGLL_INFO3) << "Destroying FontCache..." << Log::endlog;
		if(!mFontCacheGlyphSetList.empty()){
			LogManager::SlogMsg("FontCache", OGLL_WARN) << "STAGNANT GLYPHSETS DETECTED: "
				<< mFontCacheGlyphSetList.size() << Log::endlog;
		}
		
		_DestroyAllGlyphSets();
		_DestroyAllFontAtlas();
	}
	//############################################################################
	void FontCache::GetGlyph(Font* font, char glyph_charCode, const IVector2& glyph_pixelSize, FontGlyph& outFontGlyph)
	{
		FontCacheGlyphSet* glyphSet;
		glyphSet = _GetFontCacheGlyphSet(font, glyph_pixelSize);

		FontCacheGlyphSet::GlyphMap::iterator iter = glyphSet->mGlyphMap.find(glyph_charCode);
		if(iter != glyphSet->mGlyphMap.end()){
			outFontGlyph = (*iter).second;
			return;
		}

		LogManager::SlogMsg("FontCache", OGLL_INSANE) << "Cache Miss! :: CharCode:" 
			<< (unsigned int)glyph_charCode << Log::endlog;

		FontCache::_RenderGlyph(glyphSet, glyph_charCode);

		iter = glyphSet->mGlyphMap.find(glyph_charCode);
		if(iter != glyphSet->mGlyphMap.end()){
			outFontGlyph = (*iter).second;
			return;
		}
		
		//we should never reach this point
		OG_THROW(Exception::ERR_INTERNAL_ERROR, "Recently rendered glyph not found in glyphSet->mGlyphMap","FontCache::GetGlyph");
	}
	//############################################################################
	FontCacheGlyphSet* FontCache::_GetFontCacheGlyphSet(Font* font, const IVector2& glyph_pixelSize)
	{
		//search for the glyph set in the existing cache
		FontCacheGlyphSetList::iterator iter = mFontCacheGlyphSetList.begin();
		while(iter != mFontCacheGlyphSetList.end()){
			if( (*iter)->font == font &&
				(*iter)->glyphSize == glyph_pixelSize )
			{
				return (*iter);
			}
			iter++;
		}


		//this glyph set does not yet exist, so we should create it
		FontCacheGlyphSet* gset = new FontCacheGlyphSet;
		gset->font = font;
		gset->glyphSize = glyph_pixelSize;
		mFontCacheGlyphSetList.push_back(gset);

		return gset;
	}
	//############################################################################
	void FontCache::_RenderGlyph(FontCacheGlyphSet* glyphSet, char glyph_charCode)
	{
		char logChar[] = { glyph_charCode, 0};
		LogManager::SlogMsg("FontCache", OGLL_VERB) << "RenderGlyph-> "
			<< "(" << glyphSet->font->getFilename() << ") "
			<< "Size: " << glyphSet->glyphSize.toStr()
			<< " Glyph: " << glyph_charCode << "  "
			<< logChar
			<< Log::endlog;

		FontGlyph tmpFontGlyph;
		TextureDataRect tdr;
		FontGlyphMetrics glyph_metrics;
		
		//have font render the glyph into the data area
		glyphSet->font->renderGlyph(glyph_charCode, glyphSet->glyphSize, &tdr, glyph_metrics);

		//find a font atlas to accept the data
		FontAtlas* atlas = 0;
		FontAtlasList::iterator iter = mFontAtlasList.begin();
		while(iter != mFontAtlasList.end()){
			atlas = (*iter);
			if( atlas->GetAvailableChunk(glyphSet->glyphSize, IRect(), false) ){
				break;
			}
			iter++;
			atlas = 0;
		}

		if(!atlas){ //if there was no atlas ready to take the glyph, make one
			IVector2 nextAtlasSize = _calcNewAtlasSize(glyphSet->glyphSize);
			LogManager::SlogMsg("FontCache", OGLL_INFO3)
				<< "Growing FontCache size..."
				<< " new FontAtlas: " << nextAtlasSize.toStr()
				<< Log::endlog;
			atlas = new FontAtlas( nextAtlasSize );
			mFontAtlasList.push_back(atlas);
		}

		IRect chunkLocation;
		bool writeRet;
		writeRet = atlas->WriteChunk(&tdr, chunkLocation);

		std::stringstream ss;
		ss << "__FontCache:" << glyphSet->font->getFilename() << ":"
			<< glyphSet->glyphSize.toStr()
			<< ":" << (unsigned int)glyph_charCode;

		tmpFontGlyph.metrics = glyph_metrics;
		tmpFontGlyph.imageryPtr = atlas->GetImageset()->createImagery(ss.str(),chunkLocation);
		glyphSet->mGlyphMap[glyph_charCode] = tmpFontGlyph;
	}
	//############################################################################
	IVector2 FontCache::_calcNewAtlasSize(const IVector2& estimatedGlyphSize)
	{
		IVector2 retval;
		retval.x = _calcNewAtlasDimension(estimatedGlyphSize.x);
		retval.y = _calcNewAtlasDimension(estimatedGlyphSize.y);
		return retval;
	}
	//############################################################################
	void FontCache::FlushFont(Font* font)
	{
		LogManager::SlogMsg("FontCache", OGLL_INFO3) << "Flushing Font Glyphs ("
			<< font->getFilename() << ")..." << Log::endlog;

		//
		FontCacheGlyphSetList::iterator iter = mFontCacheGlyphSetList.begin();
		while(iter != mFontCacheGlyphSetList.end()){
			if( (*iter)->font == font )
			{
				FontCacheGlyphSet* gset = (*iter);
				if(gset){
					if(gset->font == font){
						LogManager::SlogMsg("FontCache", OGLL_VERB)
							<< "     ...flushing (" << font->getFilename() << ") <> "
							<< gset->glyphSize.toStr() << Log::endlog;
						delete gset;
						gset = 0;
						mFontCacheGlyphSetList.erase(iter);
						iter = mFontCacheGlyphSetList.begin();
						continue;
					}
				}
			}
			iter++;
		}
	}
	//############################################################################
	void FontCache::_DestroyAllGlyphSets()
	{
		LogManager::SlogMsg("FontCache", OGLL_INFO3) << "Destroy All Glyph Sets..." << Log::endlog;

		FontCacheGlyphSetList::iterator iter = mFontCacheGlyphSetList.begin();
		while(iter != mFontCacheGlyphSetList.end()){
			FontCacheGlyphSet* gset = (*iter);
			if(gset){
				delete gset;
			}
			iter++;
		}
		mFontCacheGlyphSetList.clear();
	}
	//############################################################################
	void FontCache::_DestroyAllFontAtlas()
	{
		LogManager::SlogMsg("FontCache", OGLL_INFO3) << "Destroy All FontAtlas..." << Log::endlog;

		FontAtlasList::iterator iter = mFontAtlasList.begin();
		while(iter != mFontAtlasList.end()){
			FontAtlas* atlas = (*iter);
			if(atlas) delete atlas;
			iter++;
		}
		mFontAtlasList.clear();
	}
	//############################################################################
};//namespace OpenGUI{
