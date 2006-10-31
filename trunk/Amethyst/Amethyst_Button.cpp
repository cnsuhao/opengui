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
			m_bMouseButtonState = false;
			mButtonState = BS_NORMAL;
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
			/*For now, just draw a pretty picture*/
			ImageryPtr pCurrentImage = mImageryPtr;
			switch(mButtonState)
			{
			case BS_NORMAL:
				break;
			case BS_PRESSED:
				if(mImageryPtrPressed)
					pCurrentImage = mImageryPtrPressed;
				break;
			case BS_HOVER:
				if(mImageryPtrMouseOver)
					pCurrentImage = mImageryPtrMouseOver;

				if(m_bMouseButtonState)
					pCurrentImage = mImageryPtrPressed;
				break;
			case BS_DISABLED:
				if(mImageryPtrDisabled)
					pCurrentImage = mImageryPtrDisabled;
				break;

			default:
				//todo:: throw exception
				break;
			}

			if(pCurrentImage)
			{
				Brush& b = evtArgs.brush;
				const FVector2& PPU = b.getPPU();
				const float scaleX = getRect().getWidth() / (( float )pCurrentImage->getImagesetRect().getWidth() ) ;
				const float scaleY = getRect().getWidth()  / (( float )pCurrentImage->getImagesetRect().getHeight() );
				b.Image.drawImage( pCurrentImage, getRect() );
			}
		}



		void SimpleButton::onResized( Object* sender, Resized_EventArgs& evtArgs ) {
			/**/
		}

		//! Called when cursor was pressed and released within this Control
		void SimpleButton::onCursor_Click( Object* sender, Cursor_EventArgs& evtArgs )
		{
			OpenGUI::Control::onCursor_Click( sender, evtArgs );
		}
		//! Called when the cursor enters this Control
		void SimpleButton::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs )
		{
			mButtonState = BS_HOVER;
			if(0)
			{
			}

			OpenGUI::Control::onCursor_Enter( sender, evtArgs );
		}
		//! Called when the cursor leaves this Control
		void SimpleButton::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs )
		{
			mButtonState = BS_NORMAL;

			OpenGUI::Control::onCursor_Leave( sender, evtArgs );
		}

		//! "Cursor_Press" event
		void SimpleButton::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs )
		{
			if(_isInside( evtArgs.Position))
				m_bMouseButtonState = true;
		}
		//! "Cursor_Release" event
		void SimpleButton::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs )
		{
	
			if(_isInside( evtArgs.Position) && m_bMouseButtonState)
			{
				// send some notification event or somesuch
			}

			m_bMouseButtonState = false;
		}

	} // namespace Amethyst{
} // namespace OpenGUI{
