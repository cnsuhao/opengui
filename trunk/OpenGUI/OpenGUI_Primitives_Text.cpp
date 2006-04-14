
#include "OpenGUI_Primitives_Text.h"
#include "OpenGUI_System.h"
#include "OpenGUI_Element.h"
#include "OpenGUI_Font.h"
#include "OpenGUI_FontManager.h"

#include "OpenGUI_Primitives_Geometric.h" //needed for usage of PrimitiveBox

namespace OpenGUI{
	namespace Render{

		//############################################################################
		PrimitiveText::PrimitiveText()
		{
			mTextContents = "";
			mPosition = FVector2(0.0f, 0.0f);
			mPenPosition = FVector2(0.0f, 0.0f);
			mContext = 0;
			mFontName = "";
			mFontSize = 0;
			mAdvTextSpacing = 0.0f;
			mAdvLineSpacing = 0.0f;
			mLineCount = 0;
			mAutoLineFeed = false;
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
			//FVector2 curPosition = mPosition.pixelAligned(mContext->getParentPixelRect().getSize());

			FVector2 pixelScale = PrimitiveText::_getPixelScale();

			unsigned int xPos = 0, yPos = 0;

			for( unsigned int strLoc = 0; stringContents[strLoc] != 0; strLoc++){
				char theChar = stringContents[strLoc];
				if(mAutoLineFeed && theChar == '\n'){
					//catch newlines and handle them without loading a pointless 'newline' glyph
					yPos++;
					advanceLine(true);
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

					//there's no way around it, we need to pixel align each quad we draw
					boxRect.setPosition( (mPosition+mPenPosition).pixelAligned(mContext->getParentPixelRect().getSize()) );
					//boxRect.setPosition( curPosition.pixelAligned(mContext->getParentPixelRect().getSize()) );

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

				mPenPosition.x += ((float)(glyph.metrics.horiAdvance + tmpXAdv)) * pixelScale.x;
				//curPosition.x += ((float)(glyph.metrics.horiAdvance + tmpXAdv)) * pixelScale.x;
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

			unsigned int tmpLineCount = 0;

			//add 1 line immediately for the first line
			curPosition.y += ( (((int)(++tmpLineCount * mAdvLineSpacing)) - ((int)((tmpLineCount -1) * mAdvLineSpacing)))
				+ PrimitiveText::getLinePixelHeight() ) * pixelScale.y;

			float tmp;

			for( unsigned int strLoc = 0; stringContents[strLoc] != 0; strLoc++){
				char theChar = stringContents[strLoc];
				if(mAutoLineFeed && theChar == '\n'){
					//catch newlines and handle them without loading a pointless 'newline' glyph
					if( (tmp = (curPosition.x - mPosition.x)) > retval.x ) retval.x = tmp;

					curPosition.x = mPosition.x;
					curPosition.y += ( (((int)(++tmpLineCount * mAdvLineSpacing)) - ((int)((tmpLineCount -1) * mAdvLineSpacing)))
						+ PrimitiveText::getLinePixelHeight() ) * pixelScale.y;
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

			unsigned int tmpLineCount = 0;

			//add 1 line immediately for the first line
			retval.y += (((int)(++tmpLineCount * mAdvLineSpacing)) - ((int)((tmpLineCount -1) * mAdvLineSpacing)))
				+ PrimitiveText::getLinePixelHeight();

			for( unsigned int strLoc = 0; stringContents[strLoc] != 0; strLoc++){
				char theChar = stringContents[strLoc];
				if(mAutoLineFeed && theChar == '\n'){
					//catch newlines and handle them without loading a pointless 'newline' glyph
					if( curWidth > retval.x ) retval.x = curWidth;
					curWidth = 0;
					retval.y += (((int)(++tmpLineCount * mAdvLineSpacing)) - ((int)((tmpLineCount -1) * mAdvLineSpacing)))
						+ PrimitiveText::getLinePixelHeight();
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
		FVector2 PrimitiveText::getPosition()
		{
			return mPosition;
		}
		//############################################################################
		FVector2 PrimitiveText::reset()
		{
			mPenPosition = FVector2(0.0f, 0.0f);
			mLineCount = 0;
			return mPenPosition;
		}
		//############################################################################
		FVector2 PrimitiveText::advanceLine(bool carriageReturn)
		{
			mLineCount++;

			int tmpYAdv =
				( ((int)(mLineCount * mAdvLineSpacing)) - ((int)((mLineCount-1) * mAdvLineSpacing)) );

			int pixelHeight = PrimitiveText::getLinePixelHeight();

			mPenPosition.y += ( (pixelHeight + tmpYAdv) * PrimitiveText::_getPixelScale().y );

			if(carriageReturn) mPenPosition.x = 0.0f;

			return mPenPosition;
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
			
			}else if(mAlignVert == TextAlignment::ALIGN_JUSTIFIED){
				if(strList.size()>0){
					int curHeight = text.getLinePixelHeight() * strList.size();
					int fullHeight = (int)(mRect.getHeight() / PrimitiveTextBox::_getPixelScale().y);
					if(fullHeight > curHeight){
						textPos.y = getRect().min.y + text.getLineHeight();
						float lineAdjust = (float)(fullHeight - curHeight) / (float)strList.size();
						text.setLineSpacing( lineAdjust );
						//
					}else{
						//if we are too long to justify correctly, fall back to ALIGN_TOP
						textPos.y = getRect().min.y + text.getLineHeight();
					}
				}else{
					//if there are no lines to draw, then just do something logical as a fallback
					textPos.y = getRect().min.y + text.getLineHeight();
				}
			}

			//Pre setup for left aligned and justified text 
			if(mAlignHoriz == TextAlignment::ALIGN_LEFT || TextAlignment::ALIGN_JUSTIFIED){
				textPos.x = getRect().min.x;
				text.setPosition(textPos);
			}

			//for each line of text, we will render as necessary according to horizontal alignment
			StringList::iterator iter = strList.begin();
			while(iter != strList.end()){
				if(mAlignHoriz == TextAlignment::ALIGN_LEFT){
					text.setText( (*iter) );
					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());

				} else if(mAlignHoriz == TextAlignment::ALIGN_CENTER){
					text.setText( (*iter) );
					textPos.x = ((getRect().max.x + getRect().min.x)/2) - (text.getTextWidth() / 2);
					text.setPosition(textPos);
					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());
					
				} else if(mAlignHoriz == TextAlignment::ALIGN_RIGHT){
					text.setText( (*iter) );
					textPos.x = getRect().max.x - text.getTextWidth();
					text.setPosition(textPos);
					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());

				} else if(mAlignHoriz == TextAlignment::ALIGN_JUSTIFIED){
					text.setText( (*iter) );

					if( ((*iter).length() > 1) &&
						text.getTextWidth() >= (getRect().max.x - getRect().min.x) * 0.75f )
					{
						int curWidth = text.getTextPixelWidth();
						int fullWidth = (int)(mRect.getWidth() / PrimitiveTextBox::_getPixelScale().x);

						float pixelAdjust = (float)(fullWidth - curWidth) / (float)((*iter).length() - 1);
						if(pixelAdjust > 0)
							text.setTextSpacing(pixelAdjust);
					}

					AppendRenderOperationList(outRenderOpList, text.getRenderOperationList());
				}

				text.advanceLine();
				iter++;
			}

			// finally! return our output
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

	};
};