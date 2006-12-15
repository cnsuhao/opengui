// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Amethyst_StaticImage.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		SimpleProperty_Imagery( SIProp_Imagery, "Imagery", StaticImage, getImagery, setImagery );
		SimpleProperty_Bool( SIProp_NativeScale, "Native_Scale", StaticImage, getNativeScale, setNativeScale );
		SimpleProperty_Bool( SIProp_NativeFill, "Native_Fill", StaticImage, getNativeFill, setNativeFill );
		SimpleProperty_Float( SIProp_TilingX, "TilingX", StaticImage, getTilingX, setTilingX );
		SimpleProperty_Float( SIProp_TilingY, "TilingY", StaticImage, getTilingY, setTilingY );
		//############################################################################
		class StaticImage_ObjectAccessorList : public ObjectAccessorList {
		public:
			StaticImage_ObjectAccessorList() {
				addAccessor( &SIProp_Imagery );
				addAccessor( &SIProp_NativeScale );
				addAccessor( &SIProp_NativeFill );
				addAccessor( &SIProp_TilingX );
				addAccessor( &SIProp_TilingY );
			}
			~StaticImage_ObjectAccessorList() {}
		}
		gStaticImage_ObjectAccessorList;
		//############################################################################
		//############################################################################
		ObjectAccessorList* StaticImage::getAccessors() {
			return &gStaticImage_ObjectAccessorList;
		}
		//############################################################################
		StaticImage::StaticImage() {
			if ( gStaticImage_ObjectAccessorList.getParent() == NULL )
				gStaticImage_ObjectAccessorList.setParent( Control::getAccessors() );

			mImageryPtr = NULL;
			mTileX = 1.0f;
			mTileY = 1.0f;
			mNativeScale = false;
			mNativeFill = false;
		}
		//############################################################################
		StaticImage::~StaticImage() {
			/**/
		}
		//############################################################################
		void StaticImage::setImagery( ImageryPtr imageryPtr ) {
			mImageryPtr = imageryPtr;
			invalidate();
		}
		//############################################################################
		ImageryPtr StaticImage::getImagery() const {
			return mImageryPtr;
		}
		//############################################################################
		void StaticImage::setNativeScale( bool nativeScale ) {
			mNativeScale = nativeScale;
			invalidate();
		}
		//############################################################################
		bool StaticImage::getNativeScale() const {
			return mNativeScale;
		}
		//############################################################################
		void StaticImage::setNativeFill( bool nativeFill ) {
			mNativeFill = nativeFill;
			invalidate();
		}
		//############################################################################
		bool StaticImage::getNativeFill() const {
			return mNativeFill;
		}
		//############################################################################
		void StaticImage::setTilingX( float tiling ) {
			mTileX = tiling;
			invalidate();
		}
		//############################################################################
		float StaticImage::getTilingX() const {
			return mTileX;
		}
		//############################################################################
		void StaticImage::setTilingY( float tiling ) {
			mTileY = tiling;
			invalidate();
		}
		//############################################################################
		float StaticImage::getTilingY() const {
			return mTileY;
		}
		//############################################################################
		Widget* StaticImage::createStaticImageFactory() {
			return new StaticImage;
		}
		//############################################################################
		void StaticImage::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			if ( mImageryPtr ) {
				Brush& b = evtArgs.brush;
				if ( mNativeScale ) {
					if ( mNativeFill ) {
						b.Image.drawImageUnscaledAndTiled( mImageryPtr, getRect() );
					} else {
						b.pushClippingRect( getRect() );
						b.Image.drawImageUnscaled( mImageryPtr, getPosition() );
						b.pop();
					}
				} else {
					b.Image.drawImageTiled( mImageryPtr, getRect(), mTileX, mTileY );
				}
			}
		}
		//############################################################################

	} // namespace Amethyst {
} // namespace OpenGUI {
