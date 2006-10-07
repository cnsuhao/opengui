#ifndef BA005A9D_5FCE_4363_A3C3_CDE071FA13B5
#define BA005A9D_5FCE_4363_A3C3_CDE071FA13B5

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"


namespace OpenGUI {

	class Object; //forward declaration
	class EventHandlerList; //forward declaration
	class I_WidgetContainer; //forward declaration

	//! Base class for event arguments
	class OPENGUI_API EventArgs {
	public:
		//! virtual destructor to support polymorphism
		virtual ~EventArgs() {}
	};

	//! Specialization of EventArgs for Attach/Detach events
	class OPENGUI_API Attach_EventArgs: public EventArgs {
	public:
		//! Constructor requires a pointer to the parent being attached/detached to/from
		Attach_EventArgs( I_WidgetContainer* parent ): parent( parent ) {}
		virtual ~Attach_EventArgs() {}
		//! Pointer to the parent being attached/detached to/from
		const I_WidgetContainer* parent;
	};

	//! Specialization of EventArgs for Cursor events
	class OPENGUI_API Cursor_EventArgs: public EventArgs {
	public:
		//! Constructor requires the X and Y position of the cursor
		Cursor_EventArgs( float x_pos, float y_pos ):
		  Position(x_pos,y_pos), X(Position.x), Y(Position.y) {}
		virtual ~Cursor_EventArgs() {}
		//! The cursor position
		const FVector2 Position;
		//! The cursor X position
		const float& X;
		//! The cursor Y position
		const float& Y;
	};



	//! Provides a unified event definition, binding, and relaying service.
	class OPENGUI_API EventReceiver {
		//Only allow Object to create and destroy us. We're not for random reuse.
		friend class Object;
	public:

		//EventReceiver (){}
		//! Adds the given \c name to the list of valid (and bindable) events
		void createEvent( const std::string& name );
		//! Sends an event of the given \c name to all such bound EventHandler instances
		void sendEvent( const std::string& name, EventArgs& args );

		//! Returns the list of EventHandler objects for the event of given \c name
		EventHandlerList* getEventHandlers( const std::string& name );
		//! Returns reference to the list of EventHandler objects for the event of given \c name, throws exception if event does not exist
		EventHandlerList& operator[]( const std::string& name );
	private:
		EventReceiver();
		~EventReceiver();
		typedef std::map<std::string, EventHandlerList*> EventHandlerListMap;
		EventHandlerListMap mEventHandlerListMap;
		Object* mParent;
	};

}
;//namespace OpenGUI{
#endif
