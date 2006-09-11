#include "OpenGUI_BaseWidgets.h"
#include <iostream>
namespace OpenGUI {
	namespace Widgets {
		//#####################################################################
		Widget* SimpleButton::createSimpleButtonFactory() {
			return new SimpleButton;
		}
		//#####################################################################
		SimpleButton::SimpleButton() {
			m_MouseOver = false;
			m_ButtonDown = false;
			PropertySet_BindProperty( "Imagery", OpenGUI::PT_STRING, &SimpleButton::_prop_SetImagery, &SimpleButton::_prop_GetImagery );
			PropertySet_BindProperty( "ImageryPressed", OpenGUI::PT_STRING, &SimpleButton::_prop_SetImageryPressed, &SimpleButton::_prop_GetImageryPressed );
			PropertySet_BindProperty( "ImageryMouseOver", OpenGUI::PT_STRING, &SimpleButton::_prop_SetImageryMouseOver, &SimpleButton::_prop_GetImageryMouseOver );
			PropertySet_BindProperty( "ImageryDisabled", OpenGUI::PT_STRING, &SimpleButton::_prop_SetImageryDisabled, &SimpleButton::_prop_GetImageryDisabled );
		}
		//#####################################################################
		SimpleButton::~SimpleButton() {}
		//#####################################################################
		Render::RenderOperationList SimpleButton::buildWidgetRenderOpList() {
			Render::PrimitiveBox box;
			box.setRect( this->getRect() );
			box.setTextureImagery( mImageryPtr );
			if ( isDisabled() ) {
				if ( mImageryPtrDisabled )
					box.setTextureImagery( mImageryPtrDisabled );
			} else {
				if ( m_MouseOver ) {
					if ( m_ButtonDown ) {
						if ( mImageryPtrPressed )
							box.setTextureImagery( mImageryPtrPressed );
					} else {
						if ( mImageryPtrMouseOver )
							box.setTextureImagery( mImageryPtrMouseOver );
					}
				} else {
					box.setTextureImagery( mImageryPtr );
				}
			}
			return box.getRenderOperationList();
		}
		//#####################################################################
		void SimpleButton::setImagery( std::string imageryName ) {
			dirtyCache();
			mImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//#####################################################################
		void SimpleButton::setImageryPressed( std::string imageryName ) {
			dirtyCache();
			mImageryPtrPressed = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//#####################################################################
		void SimpleButton::setImageryMouseOver( std::string imageryName ) {
			dirtyCache();
			mImageryPtrMouseOver = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//#####################################################################
		void SimpleButton::setImageryDisabled( std::string imageryName ) {
			dirtyCache();
			mImageryPtrDisabled = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//#####################################################################
		bool SimpleButton::defaultMessageHandler( const Msg::Message &message ) {
			if ( message.messageType == message.MT_EVENT ) {

				if ( message.event.destination != this )
					return true;

				//handle mouse just entered
				if ( message.event.type == message.event.ME_MouseEnter ) {
					if ( System::getSingleton().setTrackMouseLeave( this ) ) {
						dirtyCache();
						m_MouseOver = true;
					}
					return true;
				}

				if ( message.event.type == message.event.ME_MouseClick ) {
					return true;
				}
				if ( message.event.type == message.event.ME_MouseDblClick ) {
					return true;
				}

				if ( message.event.type == message.event.ME_MouseLeave ) {
					dirtyCache();
					m_MouseOver = false;
				}

				if ( message.event.type == message.event.ME_MouseButtonDown ) {
					dirtyCache();
					System::getSingleton().setCaptureMouse( this );
					m_ButtonDown = true;
				}
				if ( message.event.type == message.event.ME_MouseButtonUp ) {
					dirtyCache();
					System::getSingleton().setCaptureMouse( 0 );
					m_ButtonDown = false;
					if ( this != System::getSingleton().getElementAt( System::getSingleton().getCursorPos() ) ) {
						m_MouseOver = false; //fix the mouse over value if needed
					} else {
						//hey, we just got pressed!
						injectAlert( OpenGUI::Msg::Message_Alert::MA_Clicked );
					}
				}

				if ( message.event.type == message.event.ME_MouseMove && m_MouseOver == false ) {
					FVector2 mpos = (( Msg::EventData::MouseMoveEvent* )message.event.eventData )->mousePosition;
					mpos = convCoordWorldToLocal( mpos );
					if ( pointIsInside( mpos ) ) {
						if ( System::getSingleton().setTrackMouseLeave( this ) ) {
							dirtyCache();
							m_MouseOver = true;
						}
					}
				}
			}
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_SetImagery( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			w->setImagery( newValueStr );
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_GetImagery( PropertySet* widget, const std::string& propertyName, std::string& curValue ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			curValue = w->mImageryPtr ? w->mImageryPtr->getName() : "";
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_SetImageryPressed( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			w->setImageryPressed( newValueStr );
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_GetImageryPressed( PropertySet* widget, const std::string& propertyName, std::string& curValue ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			curValue = w->mImageryPtrPressed ? w->mImageryPtrPressed->getName() : "";
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_SetImageryMouseOver( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			w->setImageryMouseOver( newValueStr );
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_GetImageryMouseOver( PropertySet* widget, const std::string& propertyName, std::string& curValue ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			curValue = w->mImageryPtrMouseOver ? w->mImageryPtrMouseOver->getName() : "";
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_SetImageryDisabled( PropertySet* widget, const std::string& propertyName, const std::string& newValueStr, const void* newValuePtr ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			w->setImageryDisabled( newValueStr );
			return true;
		}
		//#####################################################################
		bool SimpleButton::_prop_GetImageryDisabled( PropertySet* widget, const std::string& propertyName, std::string& curValue ) {
			SimpleButton* w = static_cast<SimpleButton*>( widget );
			curValue = w->mImageryPtrDisabled ? w->mImageryPtrDisabled->getName() : "";
			return true;
		}
		//#####################################################################
	};
};

