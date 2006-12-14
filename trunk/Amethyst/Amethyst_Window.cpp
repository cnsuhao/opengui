#include "Amethyst_Window.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Face( WindowP_FaceBG, "FaceBG", Window, getFaceBG, setFaceBG );
		SimpleProperty_Cursor(WindowP_UL, "CursorUL", Window, getCursorUL, setCursorUL);
		SimpleProperty_Cursor(WindowP_LL, "CursorLL", Window, getCursorLL, setCursorLL);
		SimpleProperty_Cursor(WindowP_UR, "CursorUR", Window, getCursorUR, setCursorUR);
		SimpleProperty_Cursor(WindowP_LR, "CursorLR", Window, getCursorLR, setCursorLR);
		//############################################################################
		class Window_ObjectAccessorList : public ObjectAccessorList {
		public:
			Window_ObjectAccessorList() {
				addAccessor( &WindowP_FaceBG );
				addAccessor( &WindowP_UL );
				addAccessor( &WindowP_LL );
				addAccessor( &WindowP_UR );
				addAccessor( &WindowP_LR );
				/*addAccessor( &ScrollBarP_Maximum );
				addAccessor( &ScrollBarP_Coverage );
				addAccessor( &ScrollBarP_FaceBG );
				addAccessor( &ScrollBarP_FaceThumb );
				addAccessor( &ScrollBarP_Vertical );*/
			}
			~Window_ObjectAccessorList() {}
		}
		gWindow_ObjectAccessorList;
		//############################################################################
		//############################################################################
		Widget* Window::createWindowFactory() {
			return new Window;
		}
		//############################################################################
		ObjectAccessorList* Window::getAccessors() {
			return &gWindow_ObjectAccessorList;
		}
		//############################################################################
		Window::Window() {
			if ( gWindow_ObjectAccessorList.getParent() == 0 )
				gWindow_ObjectAccessorList.setParent( OpenGUI::Window::getAccessors() );
			mCursorState = NORMAL;
		}
		//############################################################################
		Window::~Window() {
			/**/
		}
		//############################################################################
		void Window::setCursorLL( CursorPtr cursorPtr ) {
			mCursorLL = cursorPtr;
			updateCursor();
		}
		//############################################################################
		CursorPtr Window::getCursorLL() const {
			return mCursorLL;
		}
		//############################################################################
		void Window::setCursorLR( CursorPtr cursorPtr ) {
			mCursorLR = cursorPtr;
			updateCursor();
		}
		//############################################################################
		CursorPtr Window::getCursorLR() const {
			return mCursorLR;
		}
		//############################################################################
		void Window::setCursorUL( CursorPtr cursorPtr ) {
			mCursorUL = cursorPtr;
			updateCursor();
		}
		//############################################################################
		CursorPtr Window::getCursorUL() const {
			return mCursorUL;
		}
		//############################################################################
		void Window::setCursorUR( CursorPtr cursorPtr ) {
			mCursorUR = cursorPtr;
			updateCursor();
		}
		//############################################################################
		CursorPtr Window::getCursorUR() const {
			return mCursorUR;
		}
		//############################################################################
		void Window::setFaceBG( FacePtr faceBG ) {
			mFaceBG = faceBG;
			invalidate();
		}
		//############################################################################
		FacePtr Window::getFaceBG() const {
			return mFaceBG;
		}
		//############################################################################
		void Window::onDrawBG( Object* sender, Draw_EventArgs& evtArgs ) {
			if ( mFaceBG )
				evtArgs.brush.Image.drawFace( mFaceBG, getRect() );
		}
		//############################################################################
		void Window::onCursor_Move( Object* sender, Cursor_EventArgs& evtArgs ) {
			// we need to run this first to ensure we don't wobble between cursor states
			OpenGUI::Window::onCursor_Move( sender, evtArgs );

			CursorState tmp = NORMAL;
			FVector2 pos;
			if ( hasCursorFocus() )
				pos = pointFromScreen( evtArgs.Position );
			else
				pos = evtArgs.Position;

			pos -= getPosition();

			if ( pos.x < 15 && pos.y < 15 )
				tmp = UL;
			if ( pos.x > ( getSize().x - 15 )  && pos.y > ( getSize().y - 15 ) )
				tmp = LR;
			if ( pos.x < 15  && pos.y > ( getSize().y - 15 ) )
				tmp = LL;
			if ( pos.x > ( getSize().x - 15 )  && pos.y < 15 )
				tmp = UR;

			if ( tmp != mCursorState ) {
				mCursorState = tmp;
				updateCursor();
			}
		}
		//############################################################################
		void Window::onCursor_Enter( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Window::onCursor_Enter( sender, evtArgs );
		}
		//############################################################################
		void Window::onCursor_Leave( Object* sender, Cursor_EventArgs& evtArgs ) {
			OpenGUI::Window::onCursor_Leave( sender, evtArgs );
		}
		//############################################################################
		void Window::onCursor_Press( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( mCursorState == UL )
				eventResize_Begin( true, true, true, true );
			if ( mCursorState == LR )
				eventResize_Begin( true, true, false, false );
			if ( mCursorState == LL )
				eventResize_Begin( true, true, true, false );
			if ( mCursorState == UR )
				eventResize_Begin( true, true, false, true );
			OpenGUI::Window::onCursor_Press( sender, evtArgs );
		}
		//############################################################################
		void Window::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
			if ( isResizing() )
				eventResize_End();
			OpenGUI::Window::onCursor_Release( sender, evtArgs );
		}
		//############################################################################
		void Window::onCursor_Focused( Object* sender, Focus_EventArgs& evtArgs ) {
			OpenGUI::Window::onCursor_Focused( sender, evtArgs );
		}
		//############################################################################
		void Window::onCursor_FocusLost( Object* sender, Focus_EventArgs& evtArgs ) {
			OpenGUI::Window::onCursor_FocusLost( sender, evtArgs );
		}
		//############################################################################
		void Window::updateCursor() {
			if ( mCursorState == UL && mCursorUL ) {
				setCursor( mCursorUL );
				return;
			}
			if ( mCursorState == UR && mCursorUR ) {
				setCursor( mCursorUR );
				return;
			}
			if ( mCursorState == LL && mCursorLL ) {
				setCursor( mCursorLL );
				return;
			}
			if ( mCursorState == LR && mCursorLR ) {
				setCursor( mCursorLR );
				return;
			}
			setCursor( 0 );
		}
		//############################################################################
	} //namespace Amethyst {
} // namespace OpenGUI {