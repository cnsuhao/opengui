#ifndef E39B7506_85C2_40b6_B15D_1309792163B9
#define E39B7506_85C2_40b6_B15D_1309792163B9

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Brush_Caching.h"
#include "OpenGUI_RenderTexture.h"

namespace OpenGUI {

	//! Brush that renders its output to a RenderTexture
	class Brush_RTT: public Brush {
	public:
		//! Constructor requires a pointer to the Screen that this Brush will eventually be drawn to
		Brush_RTT( Screen* parentScreen, const FVector2& size );
		//! Destructor
		virtual ~Brush_RTT();

		//! sends the contents of this caching Brush into the output stream of the given Brush
		void emerge( Brush& targetBrush );

		virtual const FVector2& getPPU_Raw() const;
		virtual const FVector2& getUPI_Raw() const;
		virtual bool isRTTContext() const {
			return true;
		}
	protected:
		virtual void appendRenderOperation( RenderOperation &renderOp );
		virtual void onActivate();
		virtual void onClear();
	private:
		Screen* mScreen;
		FVector2 mDrawSize;
		FVector2 mMaxUV;
		RenderTexturePtr mRenderTexture;
	};
} // namespace OpenGUI{

#endif // E39B7506_85C2_40b6_B15D_1309792163B9
