#ifndef Amethyst_Panel_h__
#define Amethyst_Panel_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API Panel: public ContainerControl {
		public:
			Panel();
			virtual ~Panel();

			// override this function to create the scrolling functionality.
			virtual void _draw( Brush& brush );

			static Widget* CreatePanelFactory();

			void SetScrollingOffset(const FVector2 &o) {mScrollingOffset = o;}
			void GetScrollingOffset(FVector2 &o) {o = mScrollingOffset;}

			void Scroll(const FVector2 &s);

			// Returns normalized values for positions of the left (x) and right (y)
			// of the visible area of the canvas
			FVector2	GetHPct(void);
			// Returns normalized values for positions of the top (x) and bottom (y)
			// of the visible area of the canvas
			FVector2	GetVPct(void);

			void		SetViewPosition(const FVector2 &hv);

		protected:
			// Event Overrides
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onChildAttached( Object* sender, Attach_EventArgs& evtArgs );
			virtual void onChildDetached( Object* sender, Attach_EventArgs& evtArgs );

			void	_genCanvasSize();

			// scrolling values
			FVector2	mScrollingOffset;
			FVector2	mCanvasSize;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Panel_h__
