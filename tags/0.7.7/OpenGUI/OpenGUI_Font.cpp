
#include "ft2build.h"
#include FT_FREETYPE_H

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontCache.h"
#include "OpenGUI_TextureDataRect.h"
#include "OpenGUI_System.h"
#include "OpenGUI_ResourceProvider.h"

namespace OpenGUI{
	//############################################################################
	Font::Font(std::string sourceFilename, unsigned int nativeXres, unsigned int nativeYres, bool autoscale)
	{
		LogManager::SlogMsg("Font", OGLL_INFO) << "(" << sourceFilename << ") " << "Creation:"
			<< " Native Resolution [" << nativeXres << "x" << nativeYres << "]"
			<< " Autoscale=" << (autoscale?"true":"false")  << Log::endlog;
		
		mFilename = sourceFilename;
		mAutoscale = autoscale;
		mNativeXres = nativeXres;
		mNativeYres = nativeYres;
		mFT_Face = 0;
		mFontResource = new Resource;

		ResourceProvider* resProvider = System::getSingleton()._getResourceProvider();
		resProvider->loadResource(sourceFilename, *mFontResource);

		FT_Library* library = (FT_Library*) FontManager::getSingleton().mFTLibrary;
		FT_Face* tFace = new FT_Face;

		FT_Open_Args ftOpenArgs;
		ftOpenArgs.flags = FT_OPEN_MEMORY;
		ftOpenArgs.memory_base = mFontResource->getData();
		ftOpenArgs.memory_size = mFontResource->getSize();
		FT_Error error = FT_Open_Face(*library, &ftOpenArgs, 0, tFace);
		if(error){
			LogManager::SlogMsg("Font", OGLL_ERR) 
				<< "FreeType 2 Error: (" << ((int)error) << ") "
				<< FontManager::getSingleton()._GetFTErrorString(error)
				<< Log::endlog;
			delete tFace; tFace = 0;
			delete mFontResource; mFontResource = 0;
			OG_THROW(Exception::ERR_INTERNAL_ERROR, "Fatal Error loading Font. Freetype error occurred during Font creation.","Font::Font");
		}
		mFT_Face = tFace;
	}
	//############################################################################
	Font::~Font()
	{
		LogManager::SlogMsg("Font", OGLL_INFO) << "(" << mFilename << ") " << "Destruction" << Log::endlog;
		if(FontManager::getSingleton().mFontCache)
			FontManager::getSingleton().mFontCache->FlushFont(this);

		FT_Face* tFace = (FT_Face*) mFT_Face;
		if(tFace){
			FT_Error error = FT_Done_Face( *tFace );
			if(error){
				LogManager::SlogMsg("Font", OGLL_ERR) 
					<< "Error unloading Font - "
					<< "FreeType 2 Error: (" << ((int)error) << ") "
					<< FontManager::getSingleton()._GetFTErrorString(error)
					<< Log::endlog;
			}
			delete tFace;
		}
		mFT_Face = 0;
		if(mFontResource)
			delete mFontResource;
		mFontResource = 0;
	}
	//############################################################################
	void Font::renderGlyph( char glyph_charCode, const IVector2& pixelSize,
		TextureDataRect* destTDR, FontGlyphMetrics& destGlyphMetrics )
	{
		FT_Error error;
		FT_Face* tFace = (FT_Face*) mFT_Face;

		//set the glyph size requested
		error = FT_Set_Pixel_Sizes( *tFace, pixelSize.x, pixelSize.y );
		if(error){
			LogManager::SlogMsg("Font", OGLL_ERR) << "[renderGlyph] "
				<< "FreeType 2 Error: (" << ((int)error) << ") "
				<< FontManager::getSingleton()._GetFTErrorString(error)
				<< Log::endlog;
			return;
		}
		error = FT_Load_Char( *tFace, glyph_charCode, FT_LOAD_RENDER );
		if(error){
			LogManager::SlogMsg("Font", OGLL_ERR) << "[renderGlyph] "
				<< "FreeType 2 Error: (" << ((int)error) << ") "
				<< FontManager::getSingleton()._GetFTErrorString(error)
				<< Log::endlog;
			return;
		}

		FT_Size_Metrics* sMetrics = &((*tFace)->size->metrics);
		FT_Glyph_Metrics* metrics = &((*tFace)->glyph->metrics);
		destGlyphMetrics.width = metrics->width / 64;
		destGlyphMetrics.height = metrics->height / 64;
		destGlyphMetrics.horiBearingX = metrics->horiBearingX /64;
		destGlyphMetrics.horiBearingY = metrics->horiBearingY /64;
		destGlyphMetrics.horiAdvance = metrics->horiAdvance /64;
		destGlyphMetrics.vertBearingX = metrics->vertBearingX /64;
		destGlyphMetrics.vertBearingY = metrics->vertBearingY /64;
		destGlyphMetrics.vertAdvance = metrics->vertAdvance /64;
		destGlyphMetrics.horizLineSpacing = sMetrics->height / 64;


		FT_Bitmap* bitmap = &((*tFace)->glyph->bitmap); //easier pointer

		//Resize the destTDR to perfectly hold the output
		destTDR->setSize( IVector2(bitmap->width, bitmap->rows), TDRColor() );

		//Copy the rendered bitmap to the TDR buffer
		IVector2 writeLoc;
		TDRColor writeColor;
		for(int y = 0; y < bitmap->rows; y++){
			writeLoc.y = y;
			for(int x = 0; x < bitmap->width; x++){
				writeLoc.x = x;
				unsigned char* data_slot=
					&(bitmap->buffer[(y * bitmap->width) + x]);
				writeColor.Alpha = *data_slot;
				destTDR->write(writeLoc, writeColor);
			}
		}
	}
	//############################################################################
	void Font::calcPixelSizeFromPoints(unsigned int pointSize, IVector2& pixelSize)
	{
		/*
			Average point size -> pixel size calculation
			pixel_size = point_size * resolution / 72
			where resolution is the dpi (dots per inch)
		*/

		/*
			Since we can't possibly determine the true dpi of the user's screen, we assume 72 dpi
			and instead provide the option for an automatic scaling system to ensure consistent
			glyph sizes despite changes in screen resolution.
		*/

		//if they didn't want auto scaling, this is really easy
		if(!mAutoscale){
			pixelSize.x = pointSize;
			pixelSize.y = pointSize;
			return;
		}

		// otherwise, we need to scale our results according to the scale differences of
		// the native res vs the current res
		IVector2 screenRes = System::getSingleton().getScreenResolution();
		FVector2 scaleFactor;
		scaleFactor.x = screenRes.x / (float) mNativeXres;
		scaleFactor.y = screenRes.y / (float) mNativeYres;
		pixelSize.x = (int)(pointSize * scaleFactor.x);
		pixelSize.y = (int)(pointSize * scaleFactor.y);
	}
	//############################################################################
	//! Returns the line height in pixels for a given pixelSizeY
	unsigned int Font::getLineSpacing(unsigned int pointSize)
	{
		IVector2 pixelRes;
		calcPixelSizeFromPoints(pointSize, pixelRes);

		FT_Error error;
		FT_Face* tFace = (FT_Face*) mFT_Face;

		//set the glyph size requested
		error = FT_Set_Pixel_Sizes( *tFace, pixelRes.x, pixelRes.y );
		if(error){
			LogManager::SlogMsg("Font", OGLL_ERR) << "[getLineSpacing] "
				<< "FreeType 2 Error: (" << ((int)error) << ") "
				<< FontManager::getSingleton()._GetFTErrorString(error)
				<< Log::endlog;
			return pixelRes.y; //fugly fallback value
		}
		FT_Size_Metrics* sMetrics = &((*tFace)->size->metrics);
		return sMetrics->height / 64;
	}
	//############################################################################
	bool Font::getGlyph(char glyph_charCode, unsigned int pointSize, IRect& outPixelRect, FontGlyph& outFontGlyph)
	{
		ImageryPtr imgPtr;
		IVector2 pixelRes;
		calcPixelSizeFromPoints(pointSize, pixelRes);

		if(!FontManager::getSingletonPtr()){
			//err msg
			return false;
		}
		
		
		FontManager::getSingletonPtr()->mFontCache
			->GetGlyph(this, glyph_charCode, pixelRes, outFontGlyph);

		return true;
	}
	//############################################################################
};
