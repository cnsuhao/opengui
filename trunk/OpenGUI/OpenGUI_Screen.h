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
	class OPENGUI_API Screen : public I_WidgetContainer {
		friend class ScreenManager;
	public:
		//! returns the name of this screen
		const std::string& getName() const;
		//! returns the size of this screen
		const FVector2& getSize() const;
		//! returns the size of the render target of this screen
		IVector2 getRenderTargetSize() const;

		//! renders this Screen to it's current render target
		void update();
		//! returns true if this screen is automatically updated
		bool isAutoUpdating() const {
			return mAutoUpdating;
		}
		//! sets if this screen is automatically updated
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
		Screen( const std::string& screenName, const FVector2& initialSize );
		virtual ~Screen();
	private:
		bool mAutoUpdating;
		std::string mName;
		FVector2 mSize;
		RenderTexturePtr renderTarget;
	};

} //namespace OpenGUI{

#endif // C98B3B2E_E8CB_4091_BFE6_F66803F67963
