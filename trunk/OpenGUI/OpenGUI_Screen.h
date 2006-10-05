#ifndef C98B3B2E_E8CB_4091_BFE6_F66803F67963
#define C98B3B2E_E8CB_4091_BFE6_F66803F67963

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_RenderTexture.h"

namespace OpenGUI {
	class ScreenManager;

	//! Every GUI is built into a screen.
	/*! Screens are the base of every GUI display, and it's often best to think
		of them as a sort of virtual monitor. They contain widgets and windows,
		they accept input on an individual basis, and they can draw their output
		either to the main viewport (the default) or to a RenderTexture via
		bindRenderTexture().
	*/
	class OPENGUI_API Screen : public I_WidgetContainer {
		friend class ScreenManager; //Allow ScreenManager to create and destroy us
	public:
		//! returns the name of this Screen
		const std::string& getName() const;
		//! returns the size/resolution of this Screen
		const FVector2& getSize() const;
		//! changes the size/resolution of this Screen
		void setSize( const FVector2& newSize );

		//! returns the size of the render target of this Screen
		/*! \deprecated This should probably become private */
		const IVector2& getRenderTargetSize() const;

		//! returns the PPU (pixels per unit) of this Screen
		/*! PPU is different from DPI. PPU is the number of pixels per Screen size unit,
		and is calculated from the Screen size divided by the pixel size of the Screen's
		render target.
		\n Basically: PPU_Axis = ScreenSize_Axis / TargetSize_Axis
		\n (where Axis is uniformly replaced with the X and Y axis) */
		const FVector2& getPPU() const {
			if( _ValidPPUcache() ){
				return mPPUcache;
			}
			_UpdatePPU();
			return mPPUcache;
		}

		//! Returns the UPI (units per inch) of this Screen. \see setUPI()
		const IVector2& getUPI() const {
			return mUPI;
		}
		//! Changes the UPI (units per inch) of this Screen.
		/*! UPI is used to determine font scaling. The default of 96x96 is a copy
		of the standard used under common operating systems. What this does is cause your
		Screen to behave much like your desktop display when doing common tasks like word
		processing, etc. This means that unless you change the DPI of your Screen, you should
		really use a Screen resolution that is common, such as 800x600 or similar. Smaller
		Screen resolutions makes fonts look bigger and larger Screen resolutions make them look
		smaller, just like your computer already does.

		This system (combined with getDPU) allows us to render Screens with consistent font sizes
		and consistent Widget sizes (basically uniformly scaling everything), while still preserving
		pixel alignment where requested. */
		void setUPI(const IVector2& newUPI );

		//! renders this Screen to it's current render target
		void update();
		//! returns true if this screen is automatically updated
		bool isAutoUpdating() const {
			return mAutoUpdating;
		}
		//! sets if this screen is automatically updated
		/*! All new Screens are auto updating by default, and must be individually set not to be if that is not desired. */
		void setAutoUpdating( bool autoUpdate = true ) {
			mAutoUpdating = autoUpdate;
		}

		//! binds the given RenderTexture as the new render target for this Screen
		void bindRenderTexture( RenderTexturePtr renderTexture );
		//! unbinds the current RenderTexture from this Screen, resetting the render target to the main window
		void unbindRenderTexture();
		//! returns true if this screen is bound to a RenderTexture
		bool isBound() const;
	protected:
		// We aren't for creation outside of ScreenManager
		Screen( const std::string& screenName, const FVector2& initialSize );
		// Not for deletion either
		virtual ~Screen();
	private:
		bool mAutoUpdating;
		std::string mName;
		FVector2 mSize;
		IVector2 mUPI;
		mutable FVector2 mPPUcache; //mutable because overall it is state unrelated
		mutable bool mPPUcache_valid; //mutable because overall it is state unrelated
		const bool _ValidPPUcache() const {
			return mPPUcache_valid;
		}
		void _DirtyPPUcache(){
			mPPUcache_valid = false;
		}
		void _UpdatePPU() const; //updates the PPU cache
		RenderTexturePtr renderTarget;
	};

} //namespace OpenGUI{

#endif // C98B3B2E_E8CB_4091_BFE6_F66803F67963
