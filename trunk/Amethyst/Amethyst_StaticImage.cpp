#include "Amethyst_StaticImage.h"

namespace OpenGUI {
	namespace Amethyst {

		class StaticImage_Image_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Image";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					StaticImage& b = dynamic_cast<StaticImage&>( objectRef );
					valueOut.setValue( b.getImagery() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					StaticImage& b = dynamic_cast<StaticImage&>( objectRef );
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
		gStaticImage_Image_ObjectProperty;
		//############################################################################
		class StaticImage_ObjectAccessorList : public ObjectAccessorList {
		public:
			StaticImage_ObjectAccessorList() {
				addAccessor( &gStaticImage_Image_ObjectProperty );
			}
			~StaticImage_ObjectAccessorList() {}
		}
		gStaticImage_ObjectAccessorList;



		StaticImage::StaticImage()
		{
			if(gStaticImage_ObjectAccessorList.getParent() == NULL)
				gStaticImage_ObjectAccessorList.setParent(Widget::getAccessors());

			mImageryPtr = NULL;
		}

		StaticImage::~StaticImage()
		{
		}


		void StaticImage::setImagery( std::string imageryName ) {
			invalidate();
			mImageryPtr = ImageryManager::getSingleton().getImagery( imageryName );
		}

		std::string StaticImage::getImagery() {
			if ( mImageryPtr )
				return mImageryPtr->getName();

			return "";
		}

		Widget* StaticImage::CreateStaticImageFactory()
		{
			return new StaticImage;
		}

		void StaticImage::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			if ( mImageryPtr ) {
				Brush& b = evtArgs.brush;
				const FVector2& PPU = b.getPPU();
				const float scaleX = getRect().getWidth() / (( float )mImageryPtr->getImagesetRect().getWidth() ) ;
				const float scaleY = getRect().getWidth()  / (( float )mImageryPtr->getImagesetRect().getHeight() );
				b.Image.drawImage( mImageryPtr, getRect() );
			}

			Control::onDraw( sender, evtArgs );
		}


	}
}
