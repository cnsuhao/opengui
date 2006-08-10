#ifndef B0E8B38D_C19D_4167_816A_E461CD365B52
#define B0E8B38D_C19D_4167_816A_E461CD365B52

#include "OpenGUI_BaseWidgets.h"

namespace OpenGUI{
	namespace Widgets{
		/*! \brief This widget, based on the FrameImage and SimpleButton code, provides
		a button functionality with overlayed text.
		
		Button imagery is to be provided for each of the 4 states (normal, selected, pressed, and disabled).
		Each state imagery is divided into 9 zones, just like FrameImage.
		If any state imagery is not provided, that state will fall back on the imagery for the
		'normal' state.


		\see \ref BW_FrameButton "FrameButton widget documentation"
		*/
		class OPENGUI_API FrameButton : public Widget
		{
		public:
			//! Constructor
			FrameButton();
			//! virtual Destructor
			virtual ~FrameButton();
			//! This is just a factory interface.
			static Widget* createFrameButtonFactory();


			//! Sets the text that will be in the button
			void setText(const std::string& newText);
			//! Returns the current text in the button
			std::string getText();

			//! Sets the Font that will be used by name
			void setFont(const std::string& fontName);
			//! Returns the name of the Font currently used
			std::string getFont();

			//! Sets the size of the text in points. (Will be automatically adjusted if the Font was set to autoscale and the current viewport resolution is not the native resolution)
			void setFontSize(unsigned int fontSize_points);
			//! Returns the current size of the font
			unsigned int getFontSize();

			//! Sets the type of horizontal alignment to use
			void setAlignment_Horiz(TextAlignment alignment);
			//! Returns the current type of horizontal alignment
			TextAlignment getAlignment_Horiz();

			//! Sets the type of vertical alignment to use
			void setAlignment_Vert(TextAlignment alignment);
			//! Returns the current type of horizontal alignment
			TextAlignment getAlignment_Vert();

			//! Toggles the use of automatic word wrapping
			void setAutoWrap(bool wrap);
			//! Returns the current state of automatic word wrapping
			bool getAutoWrap();


		//Normal Imagery
			//! Sets Normal state imagery for the Upper Left zone
			void setImageryNormal_UL(std::string imageryName);
			//! Sets Normal state imagery for the Upper Middle zone
			void setImageryNormal_UM(std::string imageryName);
			//! Sets Normal state imagery for the Upper Right zone
			void setImageryNormal_UR(std::string imageryName);
			//! Sets Normal state imagery for the Middle Left zone
			void setImageryNormal_ML(std::string imageryName);
			//! Sets Normal state imagery for the Middle Middle zone
			void setImageryNormal_MM(std::string imageryName);
			//! Sets Normal state imagery for the Middle Right zone
			void setImageryNormal_MR(std::string imageryName);
			//! Sets Normal state imagery for the Lower Left zone
			void setImageryNormal_LL(std::string imageryName);
			//! Sets Normal state imagery for the Lower Middle zone
			void setImageryNormal_LM(std::string imageryName);
			//! Sets Normal state imagery for the Lower Right zone
			void setImageryNormal_LR(std::string imageryName);

		//Over Imagery
			//! Sets Over state imagery for the Upper Left zone
			void setImageryOver_UL(std::string imageryName);
			//! Sets Over state imagery for the Upper Middle zone
			void setImageryOver_UM(std::string imageryName);
			//! Sets Over state imagery for the Upper Right zone
			void setImageryOver_UR(std::string imageryName);
			//! Sets Over state imagery for the Middle Left zone
			void setImageryOver_ML(std::string imageryName);
			//! Sets Over state imagery for the Middle Middle zone
			void setImageryOver_MM(std::string imageryName);
			//! Sets Over state imagery for the Middle Right zone
			void setImageryOver_MR(std::string imageryName);
			//! Sets Over state imagery for the Lower Left zone
			void setImageryOver_LL(std::string imageryName);
			//! Sets Over state imagery for the Lower Middle zone
			void setImageryOver_LM(std::string imageryName);
			//! Sets Over state imagery for the Lower Right zone
			void setImageryOver_LR(std::string imageryName);

		//Press Imagery
			//! Sets Press state imagery for the Upper Left zone
			void setImageryPress_UL(std::string imageryName);
			//! Sets Press state imagery for the Upper Middle zone
			void setImageryPress_UM(std::string imageryName);
			//! Sets Press state imagery for the Upper Right zone
			void setImageryPress_UR(std::string imageryName);
			//! Sets Press state imagery for the Middle Left zone
			void setImageryPress_ML(std::string imageryName);
			//! Sets Press state imagery for the Middle Middle zone
			void setImageryPress_MM(std::string imageryName);
			//! Sets Press state imagery for the Middle Right zone
			void setImageryPress_MR(std::string imageryName);
			//! Sets Press state imagery for the Lower Left zone
			void setImageryPress_LL(std::string imageryName);
			//! Sets Press state imagery for the Lower Middle zone
			void setImageryPress_LM(std::string imageryName);
			//! Sets Press state imagery for the Lower Right zone
			void setImageryPress_LR(std::string imageryName);

			//Disabled Imagery
			//! Sets Disabled state imagery for the Upper Left zone
			void setImageryDisabled_UL(std::string imageryName);
			//! Sets Disabled state imagery for the Upper Middle zone
			void setImageryDisabled_UM(std::string imageryName);
			//! Sets Disabled state imagery for the Upper Right zone
			void setImageryDisabled_UR(std::string imageryName);
			//! Sets Disabled state imagery for the Middle Left zone
			void setImageryDisabled_ML(std::string imageryName);
			//! Sets Disabled state imagery for the Middle Middle zone
			void setImageryDisabled_MM(std::string imageryName);
			//! Sets Disabled state imagery for the Middle Right zone
			void setImageryDisabled_MR(std::string imageryName);
			//! Sets Disabled state imagery for the Lower Left zone
			void setImageryDisabled_LL(std::string imageryName);
			//! Sets Disabled state imagery for the Lower Middle zone
			void setImageryDisabled_LM(std::string imageryName);
			//! Sets Disabled state imagery for the Lower Right zone
			void setImageryDisabled_LR(std::string imageryName);
		protected:
			Render::RenderOperationList buildWidgetRenderOpList();
			virtual bool defaultMessageHandler(const Msg::Message &message);

		// Variables for maintaining text settings
			std::string mText;
			TextAlignment mAlignVert;
			TextAlignment mAlignHoriz;
			std::string mFontName;
			unsigned int mFontSize;
			bool mAutoWrap;

		// Current state variables
			bool m_MouseOver; //true if mouse is currently over this object
			bool m_ButtonDown; //true if mouse button is depressed on this object

		//Normal Imagery
			ImageryPtr mImageryNormalPtr_UL;
			ImageryPtr mImageryNormalPtr_UM;
			ImageryPtr mImageryNormalPtr_UR;
			ImageryPtr mImageryNormalPtr_ML;
			ImageryPtr mImageryNormalPtr_MM;
			ImageryPtr mImageryNormalPtr_MR;
			ImageryPtr mImageryNormalPtr_LL;
			ImageryPtr mImageryNormalPtr_LM;
			ImageryPtr mImageryNormalPtr_LR;
		//Over Imagery
			ImageryPtr mImageryOverPtr_UL;
			ImageryPtr mImageryOverPtr_UM;
			ImageryPtr mImageryOverPtr_UR;
			ImageryPtr mImageryOverPtr_ML;
			ImageryPtr mImageryOverPtr_MM;
			ImageryPtr mImageryOverPtr_MR;
			ImageryPtr mImageryOverPtr_LL;
			ImageryPtr mImageryOverPtr_LM;
			ImageryPtr mImageryOverPtr_LR;
		//Press Imagery
			ImageryPtr mImageryPressPtr_UL;
			ImageryPtr mImageryPressPtr_UM;
			ImageryPtr mImageryPressPtr_UR;
			ImageryPtr mImageryPressPtr_ML;
			ImageryPtr mImageryPressPtr_MM;
			ImageryPtr mImageryPressPtr_MR;
			ImageryPtr mImageryPressPtr_LL;
			ImageryPtr mImageryPressPtr_LM;
			ImageryPtr mImageryPressPtr_LR;

		//Disabled Imagery
			ImageryPtr mImageryDisabledPtr_UL;
			ImageryPtr mImageryDisabledPtr_UM;
			ImageryPtr mImageryDisabledPtr_UR;
			ImageryPtr mImageryDisabledPtr_ML;
			ImageryPtr mImageryDisabledPtr_MM;
			ImageryPtr mImageryDisabledPtr_MR;
			ImageryPtr mImageryDisabledPtr_LL;
			ImageryPtr mImageryDisabledPtr_LM;
			ImageryPtr mImageryDisabledPtr_LR;

		private:
			//Imagery property handlers
			static bool _prop_SetImagery(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetImagery(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			//Text property handlers
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
			static bool _prop_SetWrap(PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr);
			static bool _prop_GetWrap(PropertySet* widget, const std::string& propertyName, std::string& curValue);

			//text alignment enums for property system
			PT_Enum_TextAlignment_H m_hAlignEnum;
			PT_Enum_TextAlignment_V m_vAlignEnum;
		};
	}//namespace Widgets{
}//namespace OpenGUI{


#endif