#include "Amethyst_Panel.h"

namespace OpenGUI {
	namespace Amethyst {

		Panel::Panel()
		{
		}

		Panel::~Panel()
		{
		}


		Widget* Panel::CreatePanelFactory()
		{
			return new Panel;
		}

		void Panel::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			Control::onDraw( sender, evtArgs );
		}



		//############################################################################
		void Panel::_draw( Brush& brush ) {
			if ( getVisible() ) {

				Brush_Caching& cacheBrush = _getCacheBrush();

				// do we need to rebuild the cache brush?
				if ( isCacheDirty() ) {
					cacheBrush.pushPosition( -getPosition() ); //offset to parent coords for Container drawing
					//draw background
					cacheBrush._pushMarker( this );
					eventDrawBG( cacheBrush );
					cacheBrush._popMarker( this );
					cacheBrush.pop(); // pop the parent coords offset

					// now scroll the panel contents
					cacheBrush.pushPosition(FVector2(-30,-30));

					//draw children
					if ( m_ClipChildren ) // setup the client area clip if we have one
						cacheBrush.pushClippingRect( getClientArea() );
					for ( WidgetCollection::reverse_iterator iter = Children.rbegin();
						iter != Children.rend(); iter++ ) {
							iter->_draw( cacheBrush );
					}
					if ( m_ClipChildren ) // pop the client area clip if we had one
						cacheBrush.pop();

					// remove the scroll coords
					cacheBrush.pop();

					cacheBrush.pushPosition( -getPosition() ); //offset to parent coords for Container drawing
					//draw foreground
					cacheBrush._pushMarker( this );
					eventDraw( cacheBrush );
					cacheBrush._popMarker( this );
					cacheBrush.pop(); // pop the parent coords offset
				}

				//push cache into output stream
				brush.pushAlpha( getAlpha() );
				brush.pushPosition( getPosition() );
				cacheBrush.emerge( brush );
				brush.pop(); // pop position offset
				brush.pop(); // pop alpha
			}
		}

	}

}
