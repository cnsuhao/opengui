// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef Viewport_h__
#define Viewport_h__

using namespace System;

namespace OpenGUI_Net {

	ref class Screen; // forward declaration
	ref class Viewport; // forward declaration

	class ViewportExchange: public OpenGUI::Viewport {
	public:
		ViewportExchange( OpenGUI_Net::Viewport ^ managedViewport ) {
			m_Viewport = managedViewport;
		}
		virtual const OpenGUI::IVector2& getSize();

		OpenGUI_Net::Viewport ^ getManagedViewport() {
			return m_Viewport;
		}
	protected:
		virtual void preUpdate( OpenGUI::Screen* updatingScreen );
		virtual void postUpdate( OpenGUI::Screen* updatingScreen );
		virtual void screenAttached( OpenGUI::Screen* attachingScreen );
		virtual void screenDetached( OpenGUI::Screen* detachingScreen );
	private:
		// theoretically, the garbage collector is smart enough to notice self maintaining leaks like this
		gcroot < OpenGUI_Net::Viewport ^ > m_Viewport;
	};

	public ref class Viewport abstract {
	public:
		Viewport() {
			m_ViewportExchange = new ViewportExchange( this );
		}
		~Viewport() {
			delete m_ViewportExchange;
		}
		virtual IVector2 getSize() = 0;
		virtual void preUpdate( Screen ^ updatingScreen ) = 0;
		virtual void postUpdate( Screen ^ updatingScreen ) = 0;
		virtual void screenAttached( Screen ^ attachingScreen ) = 0;
		virtual void screenDetached( Screen ^ detachingScreen ) = 0;

		OpenGUI::Viewport* getNativeViewport() {
			return m_ViewportExchange;
		}
	private:
		ViewportExchange* m_ViewportExchange;
	};

} // namespace OpenGUI_Net {

#endif // Viewport_h__
