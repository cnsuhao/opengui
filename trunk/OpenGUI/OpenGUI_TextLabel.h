#ifndef E3B7005D_9A7A_4bd1_B9DF_8C50A140033E
#define E3B7005D_9A7A_4bd1_B9DF_8C50A140033E
#include "OpenGUI_BaseWidgets.h"

/*
Horizontal Alignments
	left
	right
	center
	justified

Vertical Alignments
	top
	bottom
	center
	justified?
*/
namespace OpenGUI{
	namespace Widgets{

		//! Built in Widget that displays a text label
		class OPENGUI_API TextLabel : public Widget
		{
		public:
			TextLabel();
			~TextLabel();

			void setText(const std::string& newText);
			std::string getText();

			void setFont(const std::string& fontName);
			std::string getFont();

			void setFontSize(unsigned int fontSize_points);
			unsigned int getFontSize();

			void setAlignment_Horiz(TextAlignment alignment);
			TextAlignment getAlignment_Horiz();

			void setAlignment_Vert(TextAlignment alignment);
			TextAlignment getAlignment_Vert();

			void setAutoWrap(bool wrap);
			bool getAutoWrap();

			//! This is just a factory interface.
			static Widget* createTextLabelFactory();

		protected:
			virtual Render::RenderOperationList buildWidgetRenderOpList();
			std::string mText;
			TextAlignment mAlignVert;
			TextAlignment mAlignHoriz;
			std::string mFontName;
			unsigned int mFontSize;
			bool mAutoWrap;

		private:
			static bool _prop_SetText(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetText(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			static bool _prop_SetFont(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetFont(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetFontSize(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetFontSize(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			static bool _prop_SetHAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetHAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue);
			static bool _prop_SetVAlign(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetVAlign(PropertySet* widget, const std::string& propertyName, std::string& curValue);
		};
	};//namespace Widgets{
};//namespace OpenGUI{
#endif
