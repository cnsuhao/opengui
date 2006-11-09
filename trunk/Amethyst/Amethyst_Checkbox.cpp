#include "Amethyst_Checkbox.h"

namespace OpenGUI {
	namespace Amethyst {
		class CheckBox_SBaseImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Sel Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getSelImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setSelImagery( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_SBaseImage_ObjectProperty;
		//############################################################################
		class CheckBox_SHoverImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Sel ImageryMouseOver";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getSelImageryMouseOver() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setSelImageryMouseOver( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_SHoverImage_ObjectProperty;
		//############################################################################
		class CheckBox_SPressedImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Sel ImageryPressed";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getSelImageryPressed() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setSelImageryPressed( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_SPressedImage_ObjectProperty;
		//############################################################################
		class CheckBox_SDisabledImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Sel ImageryDisabled";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getSelImageryDisabled() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setSelImageryDisabled( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_SDisabledImage_ObjectProperty;
		//############################################################################









		class CheckBox_BaseImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setImagery( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_BaseImage_ObjectProperty;
		//############################################################################
		class CheckBox_HoverImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ImageryMouseOver";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getImageryMouseOver() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setImageryMouseOver( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_HoverImage_ObjectProperty;
		//############################################################################
		class CheckBox_PressedImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ImageryPressed";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getImageryPressed() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setImageryPressed( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_PressedImage_ObjectProperty;
		//############################################################################
		class CheckBox_DisabledImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ImageryDisabled";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getImageryDisabled() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setImageryDisabled( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gCheckBox_DisabledImage_ObjectProperty;
		//############################################################################
		class CheckBox_CurrentState_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Current State";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					valueOut.setValue( b.getCurrentState() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					CheckBox& b = dynamic_cast<CheckBox&>( objectRef );
					b.setCurrentState( valueIn.getValueAsBool() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_BOOL;
			}
		}
		gCheckBox_CurrentState_ObjectProperty;
		//############################################################################

		class CheckBox_ObjectAccessorList : public ObjectAccessorList {
		public:
			CheckBox_ObjectAccessorList() {
				addAccessor( &gCheckBox_BaseImage_ObjectProperty );
				addAccessor( &gCheckBox_HoverImage_ObjectProperty );
				addAccessor( &gCheckBox_PressedImage_ObjectProperty );
				addAccessor( &gCheckBox_DisabledImage_ObjectProperty );
				addAccessor( &gCheckBox_SBaseImage_ObjectProperty );
				addAccessor( &gCheckBox_SHoverImage_ObjectProperty );
				addAccessor( &gCheckBox_SPressedImage_ObjectProperty );
				addAccessor( &gCheckBox_SDisabledImage_ObjectProperty );
				addAccessor( &gCheckBox_CurrentState_ObjectProperty );
			}
			~CheckBox_ObjectAccessorList() {}
		}
		gCheckBox_ObjectAccessorList;


Widget* CheckBox::createCheckBoxFactory() {
	return new CheckBox;
}

//! Constructor
CheckBox::CheckBox() {
	mImageryPtr = NULL;
	mImageryPtrPressed = NULL;
	mImageryPtrMouseOver = NULL;
	mImageryPtrDisabled = NULL;

	mSelImageryPtr = NULL;
	mSelImageryPtrPressed = NULL;
	mSelImageryPtrMouseOver = NULL;
	mSelImageryPtrDisabled = NULL;

	mSelected = false;
}

//! virtual Destructor
CheckBox::~CheckBox() {
	/**/
}

void CheckBox::preActivate()
{
	mSelected = !mSelected;
}

//! Sets the normal button imagery.
void CheckBox::setSelImagery( std::string selImageryName ) {
	invalidate();
	mSelImageryPtr = ImageryManager::getSingleton().getImagery( selImageryName );
}

//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
void CheckBox::setSelImageryPressed( std::string selImageryName ) {
	invalidate();
	mSelImageryPtrPressed = ImageryManager::getSingleton().getImagery( selImageryName );
}

//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
void CheckBox::setSelImageryMouseOver( std::string selImageryName ) {
	invalidate();
	mSelImageryPtrMouseOver = ImageryManager::getSingleton().getImagery( selImageryName );
}
//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
void CheckBox::setSelImageryDisabled( std::string selImageryName ) {
	invalidate();
	mSelImageryPtrDisabled = ImageryManager::getSingleton().getImagery( selImageryName );
}

//! Gets the normal button imagery.
std::string CheckBox::getImagery() {
	if ( mImageryPtr )
		return  mImageryPtr->getName();
	return "";
}
//! Gets the pressed button imagery.
std::string CheckBox::getImageryPressed() {
	if ( mImageryPtrPressed )
		return mImageryPtrPressed->getName();
	return getImagery();
}
//! Gets the mouse over button imagery.
std::string CheckBox::getImageryMouseOver() {
	if ( mImageryPtrMouseOver )
		return mImageryPtrMouseOver->getName();
	return getImagery();
}
//! Gets the disabled button imagery.
std::string CheckBox::getImageryDisabled() {
	if ( mImageryPtrDisabled )
		return mImageryPtrDisabled->getName();
	return getImagery();
}


//8******************************************

//! Sets the normal button imagery.
void CheckBox::setImagery( std::string imageryName) {
	invalidate();
	mImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
}

//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
void CheckBox::setImageryPressed( std::string imageryName ) {
	invalidate();
	mImageryPtrPressed = ImageryManager::getSingleton().getImagery( imageryName );
}

//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
void CheckBox::setImageryMouseOver( std::string imageryName ) {
	invalidate();
	mImageryPtrMouseOver = ImageryManager::getSingleton().getImagery( imageryName );
}
//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
void CheckBox::setImageryDisabled( std::string imageryName ) {
	invalidate();
	mImageryPtrDisabled = ImageryManager::getSingleton().getImagery( imageryName );
}

//! Gets the normal button imagery.
std::string CheckBox::getSelImagery() {
	if ( mSelImageryPtr )
		return mSelImageryPtr->getName();
	return "";
}
//! Gets the pressed button imagery.
std::string CheckBox::getSelImageryPressed() {
	if ( mSelImageryPtrPressed )
		return mSelImageryPtrPressed->getName();
	return getSelImagery();
}
//! Gets the mouse over button imagery.
std::string CheckBox::getSelImageryMouseOver() {
	if ( mSelImageryPtrMouseOver )
		return mSelImageryPtrMouseOver->getName();
	return getSelImagery();
}
//! Gets the disabled button imagery.
std::string CheckBox::getSelImageryDisabled() {
	if ( mSelImageryPtrDisabled )
		return mSelImageryPtrDisabled->getName();
	return getSelImagery();
}



void CheckBox::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
	ImageryPtr pCurrentImage = NULL;
	if(mSelected)
	{
		pCurrentImage = mSelImageryPtr;
		switch ( mButtonState ) {
				case BS_NORMAL:
					break;
				case BS_PRESSED:
					if ( mSelImageryPtrPressed )
						pCurrentImage = mSelImageryPtrPressed;
					break;
				case BS_HOVER:
					if ( mSelImageryPtrMouseOver )
						pCurrentImage = mSelImageryPtrMouseOver;

					if ( m_bMouseButtonState && mSelImageryPtrPressed)
						pCurrentImage = mSelImageryPtrPressed;
					break;
				case BS_DISABLED:
					if ( mSelImageryPtrDisabled )
						pCurrentImage = mSelImageryPtrDisabled;
					break;

				default:
					//todo:: throw exception
					break;
		}
	}
	else
	{
		pCurrentImage = mImageryPtr;
		switch ( mButtonState ) {
				case BS_NORMAL:
					break;
				case BS_PRESSED:
					if ( mImageryPtrPressed )
						pCurrentImage = mImageryPtrPressed;
					break;
				case BS_HOVER:
					if ( mImageryPtrMouseOver )
						pCurrentImage = mImageryPtrMouseOver;

					if ( m_bMouseButtonState )
						pCurrentImage = mImageryPtrPressed;
					break;
				case BS_DISABLED:
					if ( mImageryPtrDisabled )
						pCurrentImage = mImageryPtrDisabled;
					break;

				default:
					//todo:: throw exception
					break;
		}
	}

	if ( pCurrentImage ) {
		Brush& b = evtArgs.brush;
		const FVector2& PPU = b.getPPU();
		const float scaleX = getRect().getWidth() / (( float )pCurrentImage->getImagesetRect().getWidth() ) ;
		const float scaleY = getRect().getWidth()  / (( float )pCurrentImage->getImagesetRect().getHeight() );
		b.Image.drawImage( pCurrentImage, getRect() );
	}
}



void CheckBox::onResized( Object* sender, Resized_EventArgs& evtArgs ) {
	/**/
}


// close the namespace stuff
	}
}
