#ifndef E3B7005D_9A7A_4bd1_B9DF_8C50A140033E
#define E3B7005D_9A7A_4bd1_B9DF_8C50A140033E
#include "OpenGUI_BaseWidgets.h"


namespace OpenGUI {
	namespace Widgets {

		//! Built in Widget that displays a text label
		/*!
		\see \ref BW_TextLabel "TextLabel widget documentation", and OpenGUI::TextAlignment
		*/
		class OPENGUI_API TextLabel : public Widget {
		public:
			//! Constructor
			TextLabel();
			//! virtual Destructor
			virtual ~TextLabel();

			//! Sets the text that the label will write to the screen
			void setText( const std::string& newText );
			//! Returns the current text in the label
			std::string getText();

			//! Sets the Font that will be used by name
			void setFont( const std::string& fontName );
			//! Returns the name of the Font currently used
			std::string getFont();

			//! Sets the size of the text in points. (Will be automatically adjusted if the Font was set to autoscale and the current viewport resolution is not the native resolution)
			void setFontSize( unsigned int fontSize_points );
			//! Returns the current size of the font
			unsigned int getFontSize();

			//! Sets the type of horizontal alignment to use
			void setAlignment_Horiz( TextAlignment alignment );
			//! Returns the current type of horizontal alignment
			TextAlignment getAlignment_Horiz();

			//! Sets the type of vertical alignment to use
			void setAlignment_Vert( TextAlignment alignment );
			//! Returns the current type of horizontal alignment
			TextAlignment getAlignment_Vert();

			//! Toggles the use of automatic word wrapping
			void setAutoWrap( bool wrap );
			//! Returns the current state of automatic word wrapping
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
			static bool _prop_SetText( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetText( PropertySet* widget, const std::string& propertyName, std::string& curValue );

			static bool _prop_SetFont( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetFont( PropertySet* widget, const std::string& propertyName, std::string& curValue );
			static bool _prop_SetFontSize( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetFontSize( PropertySet* widget, const std::string& propertyName, std::string& curValue );

			static bool _prop_SetHAlign( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetHAlign( PropertySet* widget, const std::string& propertyName, std::string& curValue );
			static bool _prop_SetVAlign( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetVAlign( PropertySet* widget, const std::string& propertyName, std::string& curValue );

			static bool _prop_SetWrap( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr );
			static bool _prop_GetWrap( PropertySet* widget, const std::string& propertyName, std::string& curValue );

			PT_Enum_TextAlignment_H m_hAlignEnum;
			PT_Enum_TextAlignment_V m_vAlignEnum;
		};
	}
	;//namespace Widgets{
}
;//namespace OpenGUI{
#endif
