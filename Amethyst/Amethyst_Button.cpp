#include "Amethyst_Button.h"

namespace OpenGUI {
	namespace Amethyst {

		class SimpleButton_BaseImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Imagery";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
					valueOut.setValue( b.getImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
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
		gSimpleButton_BaseImage_ObjectProperty;
		//############################################################################
		class SimpleButton_HoverImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ImageryMouseOver";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
					valueOut.setValue( b.getImageryMouseOver() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
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
		gSimpleButton_HoverImage_ObjectProperty;
		//############################################################################
		class SimpleButton_PressedImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ImageryPressed";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
					valueOut.setValue( b.getImageryPressed() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
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
		gSimpleButton_PressedImage_ObjectProperty;
		//############################################################################
		class SimpleButton_DisabledImage_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "ImageryDisabled";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
					valueOut.setValue( b.getImageryDisabled() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					SimpleButton& b = dynamic_cast<SimpleButton&>( objectRef );
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
		gSimpleButton_DisabledImage_ObjectProperty;
		//############################################################################
		class SimpleButton_ObjectAccessorList : public ObjectAccessorList {
		public:
			SimpleButton_ObjectAccessorList() {
				addAccessor( &gSimpleButton_BaseImage_ObjectProperty );
				addAccessor( &gSimpleButton_HoverImage_ObjectProperty );
				addAccessor( &gSimpleButton_PressedImage_ObjectProperty );
				addAccessor( &gSimpleButton_DisabledImage_ObjectProperty );
			}
			~SimpleButton_ObjectAccessorList() {}
		}
		gSimpleButton_ObjectAccessorList;


		Widget* SimpleButton::createSimpleButtonFactory() {
			return new SimpleButton;
		}

		//! Constructor
		SimpleButton::SimpleButton() {
			m_MouseOver = false;
			m_ButtonDown = false;
		}

		//! virtual Destructor
		SimpleButton::~SimpleButton() {
			/**/
		}

		//! Sets the normal button imagery.
		void SimpleButton::setImagery( std::string imageryName ) {
			invalidate();
			mImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}

		//! Sets the pressed button imagery. If none specified, uses the Normal imagery.
		void SimpleButton::setImageryPressed( std::string imageryName ) {
			invalidate();
			mImageryPtrPressed = ImageryManager::getSingleton().getImagery( imageryName );
		}

		//! Sets the mouse over button imagery. If none specified, uses the Normal imagery.
		void SimpleButton::setImageryMouseOver( std::string imageryName ) {
			invalidate();
			mImageryPtrMouseOver = ImageryManager::getSingleton().getImagery( imageryName );
		}
		//! Sets the disabled button imagery. If none specified, uses the Normal imagery.
		void SimpleButton::setImageryDisabled( std::string imageryName ) {
			invalidate();
			mImageryPtrDisabled = ImageryManager::getSingleton().getImagery( imageryName );
		}

		//! Gets the normal button imagery.
		std::string SimpleButton::getImagery() {
			if ( mImageryPtrDisabled )
				return mImageryPtr->getName();

			return "";
		}

		//! Gets the pressed button imagery.
		std::string SimpleButton::getImageryPressed() {
			if ( mImageryPtrPressed )
				return mImageryPtrPressed->getName();

			return getImagery();
		}
		//! Gets the mouse over button imagery.
		std::string SimpleButton::getImageryMouseOver() {
			if ( mImageryPtrMouseOver )
				return mImageryPtrMouseOver->getName();
			return getImagery();
		}
		//! Gets the disabled button imagery.
		std::string SimpleButton::getImageryDisabled() {
			if ( mImageryPtrDisabled )
				return mImageryPtrDisabled->getName();
			return getImagery();
		}

		void SimpleButton::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			/**/
		}


		void SimpleButton::onResized( Object* sender, Resized_EventArgs& evtArgs ) {
			/**/
		}


	} // namespace Amethyst{
} // namespace OpenGUI{
