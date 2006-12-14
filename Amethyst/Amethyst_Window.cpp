#include "Amethyst_Window.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Face( WindowP_FaceBG, "FaceBG", Window, getFaceBG, setFaceBG );
		//############################################################################
		class Window_ObjectAccessorList : public ObjectAccessorList {
		public:
			Window_ObjectAccessorList() {
				addAccessor( &WindowP_FaceBG );
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
		}
		//############################################################################
		Window::~Window() {
			/**/
		}
		//############################################################################
		void Window::setCursorLL( CursorPtr cursorPtr ) {
			mCursorLL = cursorPtr;
		}
		//############################################################################
		CursorPtr Window::getCursorLL() const {
			return mCursorLL;
		}
		//############################################################################
		void Window::setCursorLR( CursorPtr cursorPtr ) {
			mCursorLR = cursorPtr;
		}
		//############################################################################
		CursorPtr Window::getCursorLR() const {
			return mCursorLR;
		}
		//############################################################################
		void Window::setCursorUL( CursorPtr cursorPtr ) {
			mCursorUL = cursorPtr;
		}
		//############################################################################
		CursorPtr Window::getCursorUL() const {
			return mCursorUL;
		}
		//############################################################################
		void Window::setCursorUR( CursorPtr cursorPtr ) {
			mCursorUR = cursorPtr;
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
			OpenGUI::Window::onCursor_Move( sender, evtArgs );
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
			OpenGUI::Window::onCursor_Press( sender, evtArgs );
		}
		//############################################################################
		void Window::onCursor_Release( Object* sender, Cursor_EventArgs& evtArgs ) {
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
		void Window::updateCursor(){
			/**/
		}
		//############################################################################
	} //namespace Amethyst {
} // namespace OpenGUI {