#ifndef Amethyst_StaticImage_h__
#define Amethyst_StaticImage_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		//! A simple image splatter, capable of drawing an Imagery to the screen
		/*!
		\par Properties
		 - Imagery
		 - Native_Scale
		 - Native_Fill
		 - TilingX
		 - TilingY
		*/
		class AMETHYST_API StaticImage: public Control {
		public:
			StaticImage();
			virtual ~StaticImage();

			//! Sets the imagery
			void setImagery( ImageryPtr imageryPtr );
			//! Gets the imagery
			ImageryPtr getImagery() const;

			//! Toggles native scaling (default is false)
			void setNativeScale( bool nativeScale );
			//! Gets the native scaling setting
			bool getNativeScale() const;
			//! Toggles filling of the area by tiling when using native scaling
			void setNativeFill( bool nativeFill );
			//! Gets the current native fill setting
			bool getNativeFill() const;
			//! Sets the number of tiles to use in the X direction when not drawing native scale
			void setTilingX( float tiling );
			//! Returns the X tiling
			float getTilingX() const;
			//! Sets the number of tiles to use in the Y direction when not drawing native scale
			void setTilingY( float tiling );
			//! Returns the Y tiling
			float getTilingY() const;

			static Widget* createStaticImageFactory();
			virtual ObjectAccessorList* getAccessors();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );

			ImageryPtr mImageryPtr;
			bool mNativeScale;
			bool mNativeFill;
			float mTileX;
			float mTileY;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_StaticImage_h__
