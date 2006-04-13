#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{
		//#####################################################################
		TextLabel::TextLabel()
		{
			mText = "";
			mAlignVert = TextAlignment::ALIGN_TOP;
			mAlignHoriz = TextAlignment::ALIGN_LEFT;
			mFontName = "";
			mFontSize = 0;
			mAutoWrap = false;

			PropertySet_BindProperty("Text", OpenGUI::PT_STRING, &TextLabel::_prop_SetText, &TextLabel::_prop_GetText);
			PropertySet_BindProperty("Imagery", OpenGUI::PT_STRING, &TextLabel::_prop_SetHAlign, &TextLabel::_prop_GetHAlign);
		}
		//#####################################################################
		TextLabel::~TextLabel()
		{
			
		}
		//#####################################################################
		void TextLabel::setText(const std::string& newText)
		{
			mText = newText;
		}
		//#####################################################################
		std::string TextLabel::getText()
		{
			return mText;
		}
		//#####################################################################
		void TextLabel::setFont(const std::string& fontName)
		{
			mFontName = fontName;
		}
		//#####################################################################
		std::string TextLabel::getFont()
		{
			return mFontName;
		}
		//#####################################################################
		void TextLabel::setFontSize(unsigned int fontSize_points)
		{
			mFontSize = fontSize_points;
		}
		//#####################################################################
		unsigned int TextLabel::getFontSize()
		{
			return mFontSize;
		}
		//#####################################################################
		void TextLabel::setAlignment_Horiz(Alignment alignment)
		{
			mAlignHoriz = alignment;
		}
		//#####################################################################
		TextLabel::Alignment TextLabel::getAlignment_Horiz()
		{
			return mAlignHoriz;
		}
		//#####################################################################
		void TextLabel::setAlignment_Vert(Alignment alignment)
		{
			mAlignVert = alignment;
		}
		//#####################################################################
		TextLabel::Alignment TextLabel::getAlignment_Vert()
		{
			return mAlignVert;
		}
		//#####################################################################
		void TextLabel::setAutoWrap(bool wrap)
		{
			mAutoWrap = wrap;
		}
		//#####################################################################
		bool TextLabel::getAutoWrap()
		{
			return mAutoWrap;
		}
		//#####################################################################
		Widget* TextLabel::createTextLabelFactory()
		{
			return new TextLabel;
		}
/*
		//#####################################################################
		void TextLabel::_Tokenize(const std::string& inputStr, StringList& outputStrList, char token)
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
		//#####################################################################
		void TextLabel::_WrapText(StringList& strList)
		{
			StringList tmpList;
			Render::PrimitiveText text;
			text.setContext(this);
			text.setFont(mFontName,mFontSize);
			float maxWidth = getRect().getWidth();
			float thisWidth = 0.0f;

			StringList::iterator iter = strList.begin();
			while(iter != strList.end()){
				StringList wordList;

				TextLabel::_Tokenize((*iter), wordList, ' ');

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
								tmpString = TextLabel::_SubTextByWidth(thisLine, maxWidth); //get a line sized chunk
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
		//#####################################################################
		std::string TextLabel::_SubTextByWidth(std::string input, float width)
		{
			Render::PrimitiveText text;
			text.setContext(this);
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
*/
		//#####################################################################
		Render::RenderOperationList TextLabel::buildWidgetRenderOpList()
		{
			if(mText == "") //take the quick way out if there is nothing to do
				return Render::RenderOperationList();

			Render::PrimitiveScissorRect scissor;
			scissor.setRect(getRect());
			Render::PrimitiveTextBox text;
			text.setRect(getRect());
			text.setContext(this);
			text.setFont(mFontName,mFontSize);
			text.setText(mText);
			text.setAutoWrap(mAutoWrap);
			text.setAlignment_Vert((Render::PrimitiveTextBox::Alignment)(unsigned int)mAlignVert);
			text.setAlignment_Horiz((Render::PrimitiveTextBox::Alignment)(unsigned int)mAlignHoriz);
			
			scissor.addRenderOperation(text.getRenderOperationList());
			


			//debug outline
			Render::PrimitiveBoxOutline outline;
			outline.setRect(getRect());
			scissor.addRenderOperation(outline.getRenderOperationList());

			return scissor.getRenderOperationList();
			
		}

		//#####################################################################
		//#####################################################################
		bool TextLabel::_prop_SetText(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_GetText(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_SetHAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			//
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_GetHAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			return false;
		}
		//#####################################################################
	};
};
