
#include "OpenGUI.h"

namespace OpenGUI{
	namespace Render{
		//############################################################################
		void AppendRenderOperationList(RenderOperationList& outList, RenderOperationList& inList)
		{
			RenderOperationList::iterator roli = inList.begin();
			while(roli != inList.end()){
				outList.push_back((*roli));
				roli++;
			}
		}
		//############################################################################
		void PrependRenderOperationList(RenderOperationList& outList, RenderOperationList& inList)
		{
			if(inList.size() == 0) return;			
			RenderOperationList::reverse_iterator roli = inList.rbegin();
			while(roli != inList.rend()){
				outList.push_front((*roli));
				roli++;
			}
		}
		//############################################################################
		RenderOperationList PrimitiveBox::getRenderOperationList()
		{
		/*	------
			|\  B|   0\0  2
			| \  |     \ B
			|  \ |    A \
			| A \|   1  2\1
			------
		*/
			RenderOperation ropA,ropB;
			
			ropA.vertices[0].position=mRect.min;
			ropA.vertices[1].position=FVector2(mRect.min.x,mRect.max.y);
			ropA.vertices[2].position=mRect.max;

			ropB.vertices[0].position=mRect.min;
			ropB.vertices[1].position=mRect.max;
			ropB.vertices[2].position=FVector2(mRect.max.x,mRect.min.y);
			
			if(mTextureImagery){
				FRect tRect;
				tRect = mTextureImagery->getTextureUVRect();
				ropA.texture = mTextureImagery->getTexture();
				ropB.texture = mTextureImagery->getTexture();

				ropA.vertices[0].textureUV=tRect.min;
				ropA.vertices[1].textureUV=FVector2(tRect.min.x,tRect.max.y);
				ropA.vertices[2].textureUV=tRect.max;

				ropB.vertices[0].textureUV=tRect.min;
				ropB.vertices[1].textureUV=tRect.max;
				ropB.vertices[2].textureUV=FVector2(tRect.max.x,tRect.min.y);
			}else{
				ropA.vertices[0].maskUV = ropA.vertices[0].textureUV = FVector2(0.0f, 0.0f);
				ropA.vertices[1].maskUV = ropA.vertices[1].textureUV = FVector2(0.0f, 1.0f);
				ropA.vertices[2].maskUV = ropA.vertices[2].textureUV = FVector2(1.0f, 1.0f);
				ropA.texture = 0;
				ropB.vertices[0].maskUV = ropB.vertices[0].textureUV = FVector2(0.0f, 0.0f);
				ropB.vertices[1].maskUV = ropB.vertices[1].textureUV = FVector2(1.0f, 1.0f);
				ropB.vertices[2].maskUV = ropB.vertices[2].textureUV = FVector2(1.0f, 0.0f);
				
				ropB.texture = 0;
			}

			if(mMaskImagery){
				FRect tRect;
				tRect = mMaskImagery->getTextureUVRect();
				ropA.mask = mMaskImagery->getTexture();
				ropB.mask = mMaskImagery->getTexture();

				ropA.vertices[0].maskUV=tRect.min;
				ropA.vertices[1].maskUV=FVector2(tRect.min.x,tRect.max.y);
				ropA.vertices[2].maskUV=tRect.max;

				ropB.vertices[0].maskUV=tRect.min;
				ropB.vertices[1].maskUV=tRect.max;
				ropB.vertices[2].maskUV=FVector2(tRect.max.x,tRect.min.y);
			}else{
				ropA.mask = 0;
				ropB.mask = 0;
			}

			RenderOperationList ropList;
			ropList.push_back(ropA);
			ropList.push_back(ropB);
			return ropList;
		}
		//############################################################################
		//############################################################################
		//############################################################################

		//############################################################################
		//############################################################################
		//############################################################################
		RenderOperationList PrimitiveBoxOutline::getRenderOperationList()
		{
			//this is the ultra dirty/quick implementation. The corners of the outline will overlap
			FVector2 pixelScale = PrimitiveBoxOutline::_getPixelScale();
			RenderOperationList retList;
			PrimitiveBox box;
			FRect rect;

			//Top line
			rect = mRect;
			rect.setHeight( pixelScale.y * mThickness );
			box.setRect(rect);
			AppendRenderOperationList(retList, box.getRenderOperationList());

			//Bottom line
			rect.offset( FVector2(0.0f, mRect.getHeight() - rect.getHeight()) );
			box.setRect(rect);
			AppendRenderOperationList(retList, box.getRenderOperationList());

			//Left line
			rect = mRect;
			rect.setWidth( pixelScale.x * mThickness );
			box.setRect(rect);
			AppendRenderOperationList(retList, box.getRenderOperationList());

			//Right line
			rect.offset( FVector2(mRect.getWidth() - rect.getWidth(), 0.0f) );
			box.setRect(rect);
			AppendRenderOperationList(retList, box.getRenderOperationList());

			return retList;
		}
		//############################################################################
		FVector2 PrimitiveBoxOutline::_getPixelScale()
		{
			FVector2 floatDims;
			IRect pixelRect;
			if(mContext){
				//get the pixel space available as this level
				pixelRect = mContext->getPixelRect();
				floatDims = mContext->getRect().getSize();
			}else{
				//best we can do here is assume that we are drawing directly to the viewport
				pixelRect.setSize(System::getSingleton().getViewportResolution());
				floatDims = FVector2(1.0f,1.0f);
			}

			FVector2 pixelScale = FVector2( floatDims.x / pixelRect.getWidth(), floatDims.y / pixelRect.getHeight() ); 
			return pixelScale;
		}
		//############################################################################
		//############################################################################
		//############################################################################



		//############################################################################
		//############################################################################
		//############################################################################
		PrimitiveText::PrimitiveText()
		{
			mTextContents = "";
			mPosition = FVector2(0.0f, 0.0f);
			mContext = 0;
			mFontName = "";
			mFontSize = 0;
			mAdvTextSpacing = 0.0f;
			mAdvLineSpacing = 0.0f;
		}
		//############################################################################
		PrimitiveText::~PrimitiveText()
		{
			//
		}
		//############################################################################
		FVector2 PrimitiveText::_getPixelScale()
		{
			FVector2 floatDims;
			IRect pixelRect;
			if(mContext){
				//get the pixel space available as this level
				pixelRect = mContext->getPixelRect();
				floatDims = mContext->getRect().getSize();
			}else{
				//best we can do here is assume that we are drawing directly to the viewport
				pixelRect.setSize(System::getSingleton().getViewportResolution());
				floatDims = FVector2(1.0f,1.0f);
			}

			FVector2 pixelScale = FVector2( floatDims.x / pixelRect.getWidth(), floatDims.y / pixelRect.getHeight() ); 
			return pixelScale;
		}
		//############################################################################
		RenderOperationList PrimitiveText::getRenderOperationList()
		{
			FontManager* fntMgr = FontManager::getSingletonPtr();
			RenderOperationList retval;
			if(!fntMgr) return retval;

			const char* stringContents = mTextContents.c_str();

			//Start with curPosition already pixel aligned (this way we don't have to align each quad we create later)
			FVector2 curPosition = mPosition.pixelAligned(mContext->getParentPixelRect().getSize());

			FVector2 pixelScale = PrimitiveText::_getPixelScale();

			unsigned int lineSpacing = fntMgr->getLineSpacing(mFontName, mFontSize);

			unsigned int xPos = 0, yPos = 0;

			for( unsigned int strLoc = 0; stringContents[strLoc] != 0; strLoc++){
				char theChar = stringContents[strLoc];
				if(theChar == '\n'){
					//catch newlines and handle them without loading a pointless 'newline' glyph
					curPosition.x = mPosition.x;
					yPos++;
					int tmpYAdv =
						( ((int)(yPos * mAdvLineSpacing)) - ((int)((yPos-1) * mAdvLineSpacing)) );
					xPos = 0;
					curPosition.y += (tmpYAdv + lineSpacing) * pixelScale.y;
					
					continue;
				}
				//
				RenderOperationList boxOutput;
				PrimitiveBox box;
				FRect boxRect;
				IRect glyphRect;
				FontGlyph glyph;
				fntMgr->getGlyph(glyphRect, glyph, theChar, mFontName, mFontSize);
				
				if(glyph.metrics.height>0 && glyph.metrics.width>0){
					box.setTextureImagery(glyph.imageryPtr);
					boxRect.setHeight( ((float)glyph.metrics.height) * pixelScale.y );
					boxRect.setWidth( ((float)glyph.metrics.width) * pixelScale.x );
					boxRect.setPosition( curPosition.pixelAligned(mContext->getParentPixelRect().getSize()) );
					
					FVector2 tmpV; //adjust for bearing
					tmpV.x = glyph.metrics.horiBearingX * pixelScale.x;
					tmpV.y = -glyph.metrics.horiBearingY * pixelScale.y;
					boxRect.offset(tmpV);

					box.setRect( boxRect );
					boxOutput = box.getRenderOperationList();
					AppendRenderOperationList(retval, boxOutput);
				}
				
				xPos++;
				int tmpXAdv =
					( ((int)(xPos * mAdvTextSpacing)) - ((int)((xPos-1) * mAdvTextSpacing)) );

				curPosition.x += ((float)(glyph.metrics.horiAdvance + tmpXAdv)) * pixelScale.x;
			}

			return retval;
		}
		//############################################################################
		float PrimitiveText::getLineHeight()
		{
			FontManager* fntMgr = FontManager::getSingletonPtr();
			float retval;
			if(!fntMgr){
				return 0;
			}

			FVector2 pixelScale = PrimitiveText::_getPixelScale();
			unsigned int lineSpacing = fntMgr->getLineSpacing(mFontName, mFontSize);

			retval = lineSpacing * pixelScale.y;

			return retval;
		}
		//############################################################################
		int PrimitiveText::getLinePixelHeight()
		{
			FontManager* fntMgr = FontManager::getSingletonPtr();
			int retval;
			if(!fntMgr){
				return 0;
			}
			retval = (int) fntMgr->getLineSpacing(mFontName, mFontSize);
			return retval;
		}
		//############################################################################
		float PrimitiveText::getTextWidth()
		{
			return PrimitiveText::getTextSize().x;
		}
		//############################################################################
		float PrimitiveText::getTextHeight()
		{
			return PrimitiveText::getTextSize().y;
		}
		//############################################################################
		FVector2 PrimitiveText::getTextSize()
		{
			// This process works much like rendering the text, only we don't bother to do the actual rendering

			FontManager* fntMgr = FontManager::getSingletonPtr();
			FVector2 retval;
			if(!fntMgr) return retval;

			const char* stringContents = mTextContents.c_str();

			FVector2 curPosition = mPosition;

			FVector2 pixelScale = PrimitiveText::_getPixelScale();

			unsigned int lineSpacing = fntMgr->getLineSpacing(mFontName, mFontSize);

			curPosition.y += lineSpacing * pixelScale.y; //add 1 line immediately for the first line
			
			float tmp;

			for( unsigned int strLoc = 0; stringContents[strLoc] != 0; strLoc++){
				char theChar = stringContents[strLoc];
				if(theChar == '\n'){
					//catch newlines and handle them without loading a pointless 'newline' glyph
					if( (tmp = (curPosition.x - mPosition.x)) > retval.x ) retval.x = tmp;

					curPosition.x = mPosition.x;
					curPosition.y += lineSpacing * pixelScale.y;
					continue;
				}

				IRect glyphRect;
				FontGlyph glyph;
				fntMgr->getGlyph(glyphRect, glyph, theChar, mFontName, mFontSize);

				curPosition.x += ((float)glyph.metrics.horiAdvance) * pixelScale.x;
			}

			if( (tmp = (curPosition.x - mPosition.x)) > retval.x ) retval.x = tmp;
			retval.y = curPosition.y - mPosition.y;

			return retval;
		}
		//############################################################################
		int PrimitiveText::getTextPixelWidth()
		{
			return getTextPixelSize().x;
		}
		//############################################################################
		int PrimitiveText::getTextPixelHeight()
		{
			return getTextPixelSize().y;
		}
		//############################################################################
		IVector2 PrimitiveText::getTextPixelSize()
		{
			// This process works much like rendering the text, only we don't bother to do the actual rendering

			FontManager* fntMgr = FontManager::getSingletonPtr();
			IVector2 retval(0,0);
			if(!fntMgr) return retval;

			const char* stringContents = mTextContents.c_str();
			int curWidth = 0;
			unsigned int lineSpacing = fntMgr->getLineSpacing(mFontName, mFontSize);

			retval.y += lineSpacing; //add 1 line immediately for the first line

			for( unsigned int strLoc = 0; stringContents[strLoc] != 0; strLoc++){
				char theChar = stringContents[strLoc];
				if(theChar == '\n'){
					//catch newlines and handle them without loading a pointless 'newline' glyph
					if( curWidth > retval.x ) retval.x = curWidth;
					curWidth = 0;
					retval.y += lineSpacing;
					continue;
				}

				IRect glyphRect;
				FontGlyph glyph;
				fntMgr->getGlyph(glyphRect, glyph, theChar, mFontName, mFontSize);
				curWidth += glyph.metrics.horiAdvance;
			}

			if( curWidth > retval.x ) retval.x = curWidth;

			return retval;
		}
		//############################################################################
		void PrimitiveText::setContext(Element* contextElement)
		{
			mContext = contextElement;
		}
		//############################################################################
		void PrimitiveText::setText(std::string textString)
		{
			mTextContents = textString;
		}
		//############################################################################
		void PrimitiveText::setFont(std::string fontName, unsigned int fontSize_points)
		{
			mFontName = fontName;
			mFontSize = fontSize_points;
		}
		//############################################################################
		void PrimitiveText::setPosition(const FVector2& baselinePosition)
		{
			mPosition = baselinePosition;
		}
		//############################################################################
		//############################################################################
		//############################################################################
	








		//############################################################################
		//############################################################################
		//############################################################################
		PrimitiveTextBox::PrimitiveTextBox()
		{
			mTextContents = "";
			mRect = FRect(0.0f, 0.0f, 1.0f, 1.0f);
			mContext = 0;
			mFontName = "";
			mFontSize = 0;
			mAdvTextSpacing = 0.0f;
			mAdvLineSpacing = 0.0f;
			mAlignVert = TextAlignment::ALIGN_TOP;
			mAlignHoriz = TextAlignment::ALIGN_LEFT;
			mAutoWrap = false;
		}
		//############################################################################
		PrimitiveTextBox::~PrimitiveTextBox()
		{
			//
		}
		//############################################################################
		void PrimitiveTextBox::setText(std::string textString)
		{
			mTextContents = textString;
		}
		//############################################################################
		void PrimitiveTextBox::setFont(std::string fontName, unsigned int fontSize_points)
		{
			mFontName = fontName;
			mFontSize = fontSize_points;
		}
		//############################################################################
		void PrimitiveTextBox::_Tokenize(const std::string& inputStr, StringList& outputStrList, char token)
		{
			std::string tmpStr;
			const char* cstr = inputStr.c_str();
			unsigned int epos, spos;
			spos = epos = 0;
			while(cstr[epos] != 0){
				if(cstr[epos] == token){
					tmpStr = inputStr.substr(spos, epos - spos);
					outputStrList.push_back(tmpStr);
					spos = epos + 1;
				}
				epos++;
			}
			if(spos != epos){
				tmpStr = inputStr.substr(spos, epos - spos);
				outputStrList.push_back(tmpStr);
			}
		}
		//############################################################################
		void PrimitiveTextBox::_WrapText(StringList& strList)
		{
			StringList tmpList;
			Render::PrimitiveText text;
			text.setContext(mContext);
			text.setFont(mFontName,mFontSize);
			float maxWidth = getRect().getWidth();
			float thisWidth = 0.0f;

			StringList::iterator iter = strList.begin();
			while(iter != strList.end()){
				StringList wordList;

				PrimitiveTextBox::_Tokenize((*iter), wordList, ' ');

				std::string thisLine = "";
				bool lastPassAddedWord = false;

				StringList::iterator iterWord = wordList.begin();
				while(iterWord != wordList.end()){

					std::stringstream tmpSS;
					if(thisLine.length() > 0){
						tmpSS << thisLine << " " << (*iterWord);
					}else{
						tmpSS << (*iterWord);
					}

					text.setText(tmpSS.str());
					if(text.getTextWidth() < maxWidth){
						//if the new word fits into the existing line, then keep it
						thisLine = tmpSS.str();
						lastPassAddedWord = true;
					}else{
						//if the new word does NOT fit into the existing line...

						//is this the first word we've added?
						if( lastPassAddedWord ){
							//it is not, so store what we already have
							tmpList.push_back(thisLine);
						}

						thisLine = (*iterWord);

						//now we need to test the new word to see if it even fits on one line by itself
						text.setText(thisLine);
						if(text.getTextWidth() < maxWidth){
							//it does fit, so keep it on the line and do nothing else
							lastPassAddedWord = true;
						}else{
							//it does NOT fit, so break it up into it's own lines until we find a remainder that fits

							std::string tmpString;
							do{
								tmpString = PrimitiveTextBox::_SubTextByWidth(thisLine, maxWidth); //get a line sized chunk
								thisLine = thisLine.substr(tmpString.length()); //update thisLine to == word - line_sized_chunk
								if(thisLine.length() > 0){
									//if there is more left to the word, store the chunk
									tmpList.push_back(tmpString);
								}
							}
							while(thisLine.length() > 0);

							//at this point, thisLine WILL be empty, and tmpString holds the final chunk
							if(tmpString.length() > 0){
								thisLine = tmpString;
								lastPassAddedWord = true;
							}
						}

					}

					iterWord++;
				}//while(iterWord != wordList.end()){

				tmpList.push_back(thisLine); //store the final line of this line pass
				iter++;
			}//while(iter != strList.end()){

			strList = tmpList;
		}
		//############################################################################
		std::string PrimitiveTextBox::_SubTextByWidth(std::string input, float width)
		{
			Render::PrimitiveText text;
			text.setContext(mContext);
			text.setFont(mFontName,mFontSize);

			std::string outstr = input;
			unsigned int len = input.length();

			while(len > 0){
				outstr = input.substr(0, len);
				text.setText(outstr);
				if(text.getTextWidth() < width){
					return outstr;
				}
				len--;
			}

			return outstr; //at the minimum, we return 1 character
		}
		//############################################################################
		RenderOperationList PrimitiveTextBox::getRenderOperationList()
		{
			if(mTextContents == "") //take the quick way out if there is nothing to do
				return Render::RenderOperationList();

			FVector2 textPos;
			Render::RenderOperationList outRenderOpList;
			Render::PrimitiveText text;
			text.setContext(mContext);
			text.setFont(mFontName,mFontSize);



			StringList strList;
			PrimitiveTextBox::_Tokenize(mTextContents, strList, '\n');

			//if we are supposed to auto wrap this text, now is when we'll want to do it
			if(mAutoWrap)
				_WrapText(strList);


			//set up vertical alignment
			if(mAlignVert == TextAlignment::ALIGN_TOP){
				textPos.y = getRect().min.y + text.getLineHeight();
			}else if(mAlignVert == TextAlignment::ALIGN_BOTTOM){
				//calculate start position as bottom minus total height
				textPos.y = getRect().max.y - ( text.getLineHeight() * strList.size() );
				textPos.y += text.getLineHeight(); //plus 1
			}else if(mAlignVert == TextAlignment::ALIGN_CENTER){
				textPos.y = 
					((getRect().min.y + getRect().max.y)/2) // the mid point
					- ( ( text.getLineHeight() * strList.size() ) / 2 ); // minus half the total size
				textPos.y += (text.getLineHeight() / 2); //plus 1/2
			}


			//for each line of text, we will render as necessary according to horizontal alignment
			StringList::iterator iter = strList.begin();
			while(iter != strList.end()){
				if(mAlignHoriz == TextAlignment::ALIGN_LEFT){
					text.setText( (*iter) );
					textPos.x = getRect().min.x;
					text.setPosition(textPos);
					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());
					textPos.y += text.getLineHeight();

				} else if(mAlignHoriz == TextAlignment::ALIGN_CENTER){
					text.setText( (*iter) );
					textPos.x = ((getRect().max.x + getRect().min.x)/2) - (text.getTextWidth() / 2);
					text.setPosition(textPos);
					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());
					textPos.y += text.getLineHeight();

				} else if(mAlignHoriz == TextAlignment::ALIGN_RIGHT){
					text.setText( (*iter) );
					textPos.x = getRect().max.x - text.getTextWidth();
					text.setPosition(textPos);
					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());
					textPos.y += text.getLineHeight();

				} else if(mAlignHoriz == TextAlignment::ALIGN_JUSTIFIED){
					text.setText( (*iter) );

					if( ((*iter).length() > 1) &&
						text.getTextWidth() >= (getRect().max.x - getRect().min.x) * 0.75f )
					{
						int curWidth = text.getTextPixelWidth();
						int fullWidth = (int)(mRect.getWidth() / PrimitiveTextBox::_getPixelScale().x);
						
						//if(mContext) fullWidth = mContext->getPixelRect().getWidth();
						//else System::getViewportResolution();

						float pixelAdjust = (float)(fullWidth - curWidth) / (float)((*iter).length() - 1);
						textPos.x = getRect().min.x;
						if(pixelAdjust > 0)
							text.setTextSpacing(pixelAdjust);
					}else{
						textPos.x = getRect().min.x;
					}
					text.setPosition(textPos);

					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());

					textPos.y += text.getLineHeight();
					text.setTextSpacing(0.0f);
				}
				iter++;
			}


			//debug outline
			return outRenderOpList;

		}
		//############################################################################
		FVector2 PrimitiveTextBox::_getPixelScale()
		{
			FVector2 floatDims;
			IRect pixelRect;
			if(mContext){
				//get the pixel space available as this level
				pixelRect = mContext->getPixelRect();
				floatDims = mContext->getRect().getSize();
			}else{
				//best we can do here is assume that we are drawing directly to the viewport
				pixelRect.setSize(System::getSingleton().getViewportResolution());
				floatDims = FVector2(1.0f,1.0f);
			}

			FVector2 pixelScale = FVector2( floatDims.x / pixelRect.getWidth(), floatDims.y / pixelRect.getHeight() ); 
			return pixelScale;
		}
		//############################################################################
		//############################################################################
		//############################################################################










		//############################################################################
		//############################################################################
		//############################################################################
		RenderOperationList PrimitiveScissorRect::getRenderOperationList()
		{
			RenderOperationList tmpList1,tmpList2;
			RenderOperationList::iterator iter;
			
			//clip right side
			iter = mInputRenderOps.begin();
			while(iter != mInputRenderOps.end()){
				_SliceRenderOp_Vert_SaveLeft((*iter),tmpList1,mRect.max.x);
				iter++;
			}

			//clip left side
			iter = tmpList1.begin();
			while(iter != tmpList1.end()){
				_SliceRenderOp_Vert_SaveRight((*iter),tmpList2,mRect.min.x);
				iter++;
			} tmpList1.clear();

			//clip bottom side
			iter = tmpList2.begin();
			while(iter != tmpList2.end()){
				_SliceRenderOp_Horiz_SaveTop((*iter),tmpList1,mRect.max.y);
				iter++;
			} tmpList2.clear();

			//clip top side
			iter = tmpList1.begin();
			while(iter != tmpList1.end()){
				_SliceRenderOp_Horiz_SaveBottom((*iter),tmpList2,mRect.min.y);
				iter++;
			}
			return tmpList2;
		}
		//############################################################################
		void PrimitiveScissorRect::addRenderOperation(RenderOperation& renderOp)
		{
			mInputRenderOps.push_back(renderOp);
		}
		//############################################################################
		void PrimitiveScissorRect::addRenderOperation(RenderOperationList& renderOpList)
		{
			AppendRenderOperationList(mInputRenderOps,renderOpList);
		}
		//############################################################################
		void PrimitiveScissorRect::clear()
		{
			mInputRenderOps.clear();
		}
		//############################################################################
		void PrimitiveScissorRect::sliceLineSegment(Vertex& vert1, Vertex& vert2, Vertex& resultVert, float cutPosition, bool cutHorizontal){
			Vertex* higher;
			Vertex* lower;
			if(!cutHorizontal){
				if(vert1.position.x < vert2.position.x){
					lower = &vert1; higher = &vert2;
				}else{
					lower = &vert2; higher = &vert1;
				}
			}else{
				if(vert1.position.y < vert2.position.y){
					lower = &vert1; higher = &vert2;
				}else{
					lower = &vert2; higher = &vert1;
				}
			}

			float cutPercent;
			if(!cutHorizontal){
				cutPercent = (cutPosition - lower->position.x) / (higher->position.x - lower->position.x);
			}else{
				cutPercent = (cutPosition - lower->position.y) / (higher->position.y - lower->position.y);
			}

			//calculate new position
			resultVert.position.x = ((higher->position.x - lower->position.x) * cutPercent) + lower->position.x;
			resultVert.position.y = ((higher->position.y - lower->position.y) * cutPercent) + lower->position.y;

			//calculate new UVs
			resultVert.textureUV.x = ((higher->textureUV.x - lower->textureUV.x) * cutPercent) + lower->textureUV.x;
			resultVert.textureUV.y =((higher->textureUV.y - lower->textureUV.y) * cutPercent) + lower->textureUV.y;
			resultVert.maskUV.x = ((higher->maskUV.x - lower->maskUV.x) * cutPercent) + lower->maskUV.x;
			resultVert.maskUV.y =((higher->maskUV.y - lower->maskUV.y) * cutPercent) + lower->maskUV.y;

			//calculate new colors
			resultVert.color.Red = ((higher->color.Red - lower->color.Red) * cutPercent) + lower->color.Red;
			resultVert.color.Green = ((higher->color.Green - lower->color.Green) * cutPercent) + lower->color.Green;
			resultVert.color.Blue = ((higher->color.Blue - lower->color.Blue) * cutPercent) + lower->color.Blue;
			resultVert.color.Alpha = ((higher->color.Alpha - lower->color.Alpha) * cutPercent) + lower->color.Alpha;

			//done
		}
		//############################################################################
		void PrimitiveScissorRect::_SliceRenderOp_Vert_SaveLeft(RenderOperation& input, RenderOperationList& output, float cutPosition)
		{
			int toKeepCount=0;
			int toKeep[3];
			int toDropCount=0;
			int toDrop[3];
			for(unsigned int i = 0; i<3; i++){
				if(input.vertices[i].position.x > cutPosition)
					toDrop[toDropCount++] = i;
				else
					toKeep[toKeepCount++] = i;
			}

			if(toKeepCount == 0){
				return;
			}

			if(toKeepCount == 1){
				//only one render operation as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toKeep[0]],input.vertices[toDrop[0]],tmp1,cutPosition,false);
				sliceLineSegment(input.vertices[toKeep[0]],input.vertices[toDrop[1]],tmp2,cutPosition,false);
				RenderOperation singleRenderOp;
				singleRenderOp.texture = input.texture;
				singleRenderOp.mask = input.mask;
				singleRenderOp.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp.vertices[toDrop[0]] = tmp1;
				singleRenderOp.vertices[toDrop[1]] = tmp2;
				output.push_back(singleRenderOp);
				return;
			}
			
			if(toKeepCount == 2){
				//two render operations as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toKeep[0]],input.vertices[toDrop[0]],tmp1,cutPosition,false);
				sliceLineSegment(input.vertices[toKeep[1]],input.vertices[toDrop[0]],tmp2,cutPosition,false);
				RenderOperation singleRenderOp1,singleRenderOp2;
				singleRenderOp1.texture = singleRenderOp2.texture = input.texture;
				singleRenderOp1.mask = singleRenderOp2.mask = input.mask;

				singleRenderOp1.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp1.vertices[toKeep[1]] = tmp2;
				singleRenderOp1.vertices[toDrop[0]] = tmp1;

				singleRenderOp2.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp2.vertices[toKeep[1]] = input.vertices[toKeep[1]];
				singleRenderOp2.vertices[toDrop[0]] = tmp2;
			
				output.push_back(singleRenderOp1);
				output.push_back(singleRenderOp2);
				return;
			}

			//if we get here, then we need to keep the whole thing
			output.push_back(input);
		}
		//############################################################################
		void PrimitiveScissorRect::_SliceRenderOp_Vert_SaveRight(RenderOperation& input, RenderOperationList& output, float cutPosition)
		{
			int toKeepCount=0;
			int toKeep[3];
			int toDropCount=0;
			int toDrop[3];
			for(unsigned int i = 0; i<3; i++){
				if(input.vertices[i].position.x < cutPosition)
					toDrop[toDropCount++] = i;
				else
					toKeep[toKeepCount++] = i;
			}

			if(toKeepCount == 0){
				return;
			}

			if(toKeepCount == 1){
				//only one render operation as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toDrop[0]],input.vertices[toKeep[0]],tmp1,cutPosition,false);
				sliceLineSegment(input.vertices[toDrop[1]],input.vertices[toKeep[0]],tmp2,cutPosition,false);
				RenderOperation singleRenderOp;
				singleRenderOp.texture = input.texture;
				singleRenderOp.mask = input.mask;
				singleRenderOp.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp.vertices[toDrop[0]] = tmp1;
				singleRenderOp.vertices[toDrop[1]] = tmp2;
				output.push_back(singleRenderOp);
				return;
			}

			if(toKeepCount == 2){
				//two render operations as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toDrop[0]],input.vertices[toKeep[0]],tmp1,cutPosition,false);
				sliceLineSegment(input.vertices[toDrop[0]],input.vertices[toKeep[1]],tmp2,cutPosition,false);
				RenderOperation singleRenderOp1,singleRenderOp2;
				singleRenderOp1.texture = singleRenderOp2.texture = input.texture;
				singleRenderOp1.mask = singleRenderOp2.mask = input.mask;

				singleRenderOp1.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp1.vertices[toKeep[1]] = tmp2;
				singleRenderOp1.vertices[toDrop[0]] = tmp1;

				singleRenderOp2.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp2.vertices[toKeep[1]] = input.vertices[toKeep[1]];
				singleRenderOp2.vertices[toDrop[0]] = tmp2;

				output.push_back(singleRenderOp1);
				output.push_back(singleRenderOp2);
				return;
			}

			//if we get here, then we need to keep the whole thing
			output.push_back(input);
		}
		//############################################################################
		void PrimitiveScissorRect::_SliceRenderOp_Horiz_SaveTop(RenderOperation& input, RenderOperationList& output, float cutPosition)
		{
			int toKeepCount=0;
			int toKeep[3];
			int toDropCount=0;
			int toDrop[3];
			for(unsigned int i = 0; i<3; i++){
				if(input.vertices[i].position.y > cutPosition)
					toDrop[toDropCount++] = i;
				else
					toKeep[toKeepCount++] = i;
			}

			if(toKeepCount == 0){
				return;
			}

			if(toKeepCount == 1){
				//only one render operation as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toKeep[0]],input.vertices[toDrop[0]],tmp1,cutPosition,true);
				sliceLineSegment(input.vertices[toKeep[0]],input.vertices[toDrop[1]],tmp2,cutPosition,true);
				RenderOperation singleRenderOp;
				singleRenderOp.texture = input.texture;
				singleRenderOp.mask = input.mask;
				singleRenderOp.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp.vertices[toDrop[0]] = tmp1;
				singleRenderOp.vertices[toDrop[1]] = tmp2;
				output.push_back(singleRenderOp);
				return;
			}

			if(toKeepCount == 2){
				//two render operations as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toKeep[0]],input.vertices[toDrop[0]],tmp1,cutPosition,true);
				sliceLineSegment(input.vertices[toKeep[1]],input.vertices[toDrop[0]],tmp2,cutPosition,true);
				RenderOperation singleRenderOp1,singleRenderOp2;
				singleRenderOp1.texture = singleRenderOp2.texture = input.texture;
				singleRenderOp1.mask = singleRenderOp2.mask = input.mask;

				singleRenderOp1.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp1.vertices[toKeep[1]] = tmp2;
				singleRenderOp1.vertices[toDrop[0]] = tmp1;

				singleRenderOp2.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp2.vertices[toKeep[1]] = input.vertices[toKeep[1]];
				singleRenderOp2.vertices[toDrop[0]] = tmp2;

				output.push_back(singleRenderOp1);
				output.push_back(singleRenderOp2);
				return;
			}

			//if we get here, then we need to keep the whole thing
			output.push_back(input);
		}
		//############################################################################
		void PrimitiveScissorRect::_SliceRenderOp_Horiz_SaveBottom(RenderOperation& input, RenderOperationList& output, float cutPosition)
		{			
			int toKeepCount=0;
			int toKeep[3];
			int toDropCount=0;
			int toDrop[3];
			for(unsigned int i = 0; i<3; i++){
				if(input.vertices[i].position.y < cutPosition)
					toDrop[toDropCount++] = i;
				else
					toKeep[toKeepCount++] = i;
			}

			if(toKeepCount == 0){
				return;
			}

			if(toKeepCount == 1){
				//only one render operation as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toDrop[0]],input.vertices[toKeep[0]],tmp1,cutPosition,true);
				sliceLineSegment(input.vertices[toDrop[1]],input.vertices[toKeep[0]],tmp2,cutPosition,true);
				RenderOperation singleRenderOp;
				singleRenderOp.texture = input.texture;
				singleRenderOp.mask = input.mask;
				singleRenderOp.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp.vertices[toDrop[0]] = tmp1;
				singleRenderOp.vertices[toDrop[1]] = tmp2;
				output.push_back(singleRenderOp);
				return;
			}

			if(toKeepCount == 2){
				//two render operations as output
				Vertex tmp1,tmp2;
				sliceLineSegment(input.vertices[toDrop[0]],input.vertices[toKeep[0]],tmp1,cutPosition,true);
				sliceLineSegment(input.vertices[toDrop[0]],input.vertices[toKeep[1]],tmp2,cutPosition,true);
				RenderOperation singleRenderOp1,singleRenderOp2;
				singleRenderOp1.texture = singleRenderOp2.texture = input.texture;
				singleRenderOp1.mask = singleRenderOp2.mask = input.mask;

				singleRenderOp1.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp1.vertices[toKeep[1]] = tmp2;
				singleRenderOp1.vertices[toDrop[0]] = tmp1;

				singleRenderOp2.vertices[toKeep[0]] = input.vertices[toKeep[0]];
				singleRenderOp2.vertices[toKeep[1]] = input.vertices[toKeep[1]];
				singleRenderOp2.vertices[toDrop[0]] = tmp2;

				output.push_back(singleRenderOp1);
				output.push_back(singleRenderOp2);
				return;
			}

			//if we get here, then we need to keep the whole thing
			output.push_back(input);
		}
		//############################################################################
	};//namespace Render{
};





