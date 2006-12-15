// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef BA005A9D_5FCE_4363_A3C3_CDE071FA13B5
#define BA005A9D_5FCE_4363_A3C3_CDE071FA13B5

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"


namespace OpenGUI {

	class Object; //forward declaration
	class EventHandlerList; //forward declaration
	class WidgetCollection; //forward declaration
	class Widget; //forward declaration

	//! Base class for event arguments
	class OPENGUI_API EventArgs {
	public:
		//! default constructor does absolutely nothing
		EventArgs() {}
		//! virtual destructor to support polymorphism
		virtual ~EventArgs() {
			/**/
		}
	};

	//! Base class for event arguments
	class OPENGUI_API Focus_EventArgs: public EventArgs {
	public:
		//! Constructor requires the pointers to the Widgets that received and lost focus
		Focus_EventArgs( const Widget* received, const Widget* lost ):
				Received( received ), Lost( lost ) {
			/**/
		}
		virtual ~Focus_EventArgs() {
			/**/
		}
		//! Pointer to the Widget that is receiving focus, or 0 (NULL) if none
		const Widget* Received;
		//! Pointer to the Widget that has lost focus, or 0 (NULL) if none
		const Widget* Lost;
	};

	//! Base class for input related events
	/*! The purpose of this class is to ensure a standard interface for signaling
	input consumption. */
	class OPENGUI_API Input_EventArgs: public EventArgs {
	public:
		Input_EventArgs(): Consumed( false ) {
			/**/
		}
		virtual ~Input_EventArgs() {
			/**/
		}
		//! consume this input event
		/*! This does not necessarily prevent the event from continuing its propagation,
		it merely marks it as having been used somewhere, so that the input injection
		routine that created it will return true, rather than false. */
		void eat() {
			bool& tmp = const_cast<bool&>( Consumed );
			tmp = true;
		}
		//! Ready only member for getting the current consumption state of this event
		const bool Consumed;
	};

	//! Specialization of EventArgs for Attach/Detach events
	class OPENGUI_API Attach_EventArgs: public EventArgs {
	public:
		//! Constructor requires a pointer to the parent being attached/detached to/from
		Attach_EventArgs( WidgetCollection* collection, Widget* child ): collection( collection ), child( child ) {
			/**/
		}
		virtual ~Attach_EventArgs() {
			/**/
		}
		//! Pointer to the WidgetCollection being attached/detached to/from
		const WidgetCollection* collection;
		//! Pointer to the child that was attached/detached
		const Widget* child;
	};

	//! Specialization of EventArgs for Cursor events
	class OPENGUI_API Cursor_EventArgs: public Input_EventArgs {
	public:
		//! Constructor requires the X and Y position of the cursor
		Cursor_EventArgs( float x_pos, float y_pos ):
				Position( x_pos, y_pos ), X( Position.x ), Y( Position.y ) {
			/**/
		}
		virtual ~Cursor_EventArgs() {
			/**/
		}
		//! The cursor position
		const FVector2 Position;
		//! The cursor X position
		const float& X;
		//! The cursor Y position
		const float& Y;
	};

	//! Specialization of EventArgs for Key events
	class OPENGUI_API Key_EventArgs: public Input_EventArgs {
	public:
		//! Constructor requires the \c character this event references
		Key_EventArgs( char character ): Character( character ) {
			/**/
		}
		virtual ~Key_EventArgs() {
			/**/
		}
		const char Character;
	};

	//! Specialization of EventArgs for Control Moved events
	class OPENGUI_API Moved_EventArgs: public EventArgs {
	public:
		//! Constructor requires the new and old positions
		Moved_EventArgs( const FVector2& newPosition, const FVector2& prevPosition )
				: newPosition( newPosition ), prevPosition( prevPosition ) {
			/**/
		}
		virtual ~Moved_EventArgs() {
			/**/
		}
		//! The new position after the move
		const FVector2 newPosition;
		//! The previous position from before the move
		const FVector2 prevPosition;
	};

	//! Specialization of EventArgs for Control Size events
	class OPENGUI_API Resized_EventArgs: public EventArgs {
	public:
		//! Constructor requires the new and old sizes
		Resized_EventArgs( const FVector2& newSize, const FVector2& prevSize )
				: newSize( newSize ), prevSize( prevSize ) {
			/**/
		}
		virtual ~Resized_EventArgs() {
			/**/
		}
		//! The new position after the move
		const FVector2 newSize;
		//! The previous position from before the move
		const FVector2 prevSize;
	};

	class OPENGUI_API Tick_EventArgs: public EventArgs {
	public:
		//! Constructor requires the time passed, in seconds, represented as a float
		Tick_EventArgs( float seconds ): Seconds( seconds ) {}
		//! virtual destructor to support polymorphism
		virtual ~Tick_EventArgs() {
			/**/
		}
		//! Number of seconds passed in this time event
		const float Seconds;
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
