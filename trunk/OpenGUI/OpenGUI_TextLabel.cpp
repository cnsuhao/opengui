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
			PropertySet_BindProperty("Font", OpenGUI::PT_STRING, &TextLabel::_prop_SetFont, &TextLabel::_prop_GetFont);
			PropertySet_BindProperty("FontSize", OpenGUI::PT_INTEGER, &TextLabel::_prop_SetFontSize, &TextLabel::_prop_GetFontSize);
			PropertySet_BindProperty("Alignment_H", OpenGUI::PT_STRING, &TextLabel::_prop_SetHAlign, &TextLabel::_prop_GetHAlign);
			PropertySet_BindProperty("Alignment_V", OpenGUI::PT_STRING, &TextLabel::_prop_SetVAlign, &TextLabel::_prop_GetVAlign);
			PropertySet_BindProperty("AutoWrap", OpenGUI::PT_BOOL, &TextLabel::_prop_SetWrap, &TextLabel::_prop_GetWrap);
		}
		//#####################################################################
		TextLabel::~TextLabel()
		{
			
		}
		//#####################################################################
		void TextLabel::setText(const std::string& newText)
		{
			dirtyCache();
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
			dirtyCache();
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
			dirtyCache();
			mFontSize = fontSize_points;
		}
		//#####################################################################
		unsigned int TextLabel::getFontSize()
		{
			return mFontSize;
		}
		//#####################################################################
		void TextLabel::setAlignment_Horiz(TextAlignment alignment)
		{
			dirtyCache();
			mAlignHoriz = alignment;
		}
		//#####################################################################
		TextAlignment TextLabel::getAlignment_Horiz()
		{
			return mAlignHoriz;
		}
		//#####################################################################
		void TextLabel::setAlignment_Vert(TextAlignment alignment)
		{
			dirtyCache();
			mAlignVert = alignment;
		}
		//#####################################################################
		TextAlignment TextLabel::getAlignment_Vert()
		{
			return mAlignVert;
		}
		//#####################################################################
		void TextLabel::setAutoWrap(bool wrap)
		{
			dirtyCache();
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
			text.setAlignment_Vert(mAlignVert);
			text.setAlignment_Horiz(mAlignHoriz);

			return text.getRenderOperationList();
			
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
			TextLabel* w = static_cast<TextLabel*>(widget);
			w->setText(newValueStr);
			return true;
		}
		//#####################################################################
		bool TextLabel::_prop_GetText(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			TextLabel* w = static_cast<TextLabel*>(widget);
			curValue = w->getText();
			return true;
		}
		//#####################################################################
		bool TextLabel::_prop_SetFont(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			TextLabel* w = static_cast<TextLabel*>(widget);
			w->setFont(newValueStr);
			return true;
		}
		//#####################################################################
		bool TextLabel::_prop_GetFont(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			TextLabel* w = static_cast<TextLabel*>(widget);
			curValue = w->getFont();
			return true;
		}
		//#####################################################################
		bool TextLabel::_prop_SetFontSize(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			int *t = (int*)newValuePtr;
			TextLabel* w = static_cast<TextLabel*>(widget);
			w->setFontSize((unsigned int)*t);
			return true;
		}
		//#####################################################################
		bool TextLabel::_prop_GetFontSize(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			std::string outval;
			TextLabel* w = static_cast<TextLabel*>(widget);
			return PropertyParser::toStrInt(w->getFontSize(), outval);
		}
		//#####################################################################
		bool TextLabel::_prop_SetHAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			//!\todo fixme
			//TextLabel* w = static_cast<TextLabel*>(widget);
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_GetHAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			//!\todo fixme
			//TextLabel* w = static_cast<TextLabel*>(widget);
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_SetVAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			//!\todo fixme
			//TextLabel* w = static_cast<TextLabel*>(widget);
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_GetVAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			//!\todo fixme
			//TextLabel* w = static_cast<TextLabel*>(widget);
			return false;
		}
		//#####################################################################
		bool TextLabel::_prop_SetWrap(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr)
		{
			if(!newValuePtr) return false;
			bool* t = (bool*)newValuePtr;
			TextLabel* w = static_cast<TextLabel*>(widget);
			w->setAutoWrap(*t);
			return true;
		}
		//#####################################################################
		bool TextLabel::_prop_GetWrap(PropertySet* widget, const std::string& propertyName, std::string& curValue)
		{
			std::string outval;
			TextLabel* w = static_cast<TextLabel*>(widget);
			return PropertyParser::toStrBool(w->mAutoWrap, curValue);
		}
		//#####################################################################
	};//namespace Widgets{
};//namespace OpenGUI{

