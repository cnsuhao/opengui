#ifndef BA005A9D_5FCE_4363_A3C3_CDE071FA13B5
#define BA005A9D_5FCE_4363_A3C3_CDE071FA13B5

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"


namespace OpenGUI {

	class Object; //forward declaration
	class EventHandlerList; //forward declaration

	//! Base class for event arguments
	class OPENGUI_API EventArgs {
	public:
		//! virtual destructor to support polymorphism
		virtual ~EventArgs() {}
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
