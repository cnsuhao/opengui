#ifndef A0D166F7_A4DC_4019_8411_83D8DC435DFC
#define A0D166F7_A4DC_4019_8411_83D8DC435DFC

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Brush.h"
#include "OpenGUI_RenderTexture.h"

namespace OpenGUI {

	class Screen; // forward declaration

	//! Brush that caches its output to RTT surfaces if available, with automatic fall back to memory storage if necessary
	class OPENGUI_API Brush_Caching: public Brush {
	public:
		//! Constructor requires a pointer to the Screen that this Brush will eventually be drawn to
		Brush_Caching( Screen* parentScreen, const FVector2& size );
		//! Destructor
		virtual ~Brush_Caching();

		//! sends the contents of this caching Brush into the output stream of the given Brush
		void emerge( Brush& targetBrush );

		virtual const FVector2& getPPU_Raw() const;
		virtual const FVector2& getUPI_Raw() const;
		virtual bool isRTTContext() const {
			return isRTT();
		}

		//! returns \c true if this caching Brush is using a render texture for storage
		bool isRTT() const {
			return mRenderTexture.get() != 0;
		}
		//! returns \c true if this caching Brush is using memory for storage
		bool isMemory() const {
			return !isRTT();
		}
		//! public access to Brush::_clear()
		void clear(){
			_clear();
		}
		//! returns \c true if there is content stored that can be emerged
		bool hasContent() const{
			return mHasContent;
		}

	protected:
		virtual void appendRenderOperation( RenderOperation &renderOp );
		virtual void onActivate();
		virtual void onClear();

		bool initRTT();
		void cleanupRTT();
		void clearRTT();
		void activateRTT();
		void appendRTT( RenderOperation &renderOp );
		void emergeRTT( Brush& targetBrush );

		void initMemory();
		void cleanupMemory();
		void clearMemory();
		void activateMemory();
		void appendMemory( RenderOperation &renderOp );
		void emergeMemory( Brush& targetBrush );

	private:
		Screen* mScreen;
		FVector2 mDrawSize;
		FVector2 mMaxUV;
		RenderOperationList mRenderOpList;
		RenderTexturePtr mRenderTexture;
		bool mHasContent;
	};
} // namespace OpenGUI{

#endif // A0D166F7_A4DC_4019_8411_83D8DC435DFC