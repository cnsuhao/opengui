#ifndef E278D21F_0B04_437C_8A77_E84A74699F89
#define E278D21F_0B04_437C_8A77_E84A74699F89

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_Object.h"

namespace OpenGUI {


	//############################################################################
	//! Base class for Accessor system
	/*! All accessors must be
	*/
	class OPENGUI_API ObjectAccessor {
	public:
		ObjectAccessor() {}
		virtual ~ObjectAccessor() {}

		virtual const char* getAccessorName() = 0;
		enum ObjectAccessorType {
			TYPE_PROPERTY, TYPE_METHOD
		};
		//! Returns the type of Accessor
		/*! This is automatically handled when you inherit from ObjectProperty or ObjectMethod */
		virtual ObjectAccessorType getAccessorType() = 0;
	};


	//############################################################################
	//! Base class for Property Accessors
	/*! Object Properties that applications wish to expose should inherit this class. */
	class OPENGUI_API ObjectProperty : ObjectAccessor {
	public:
		//! Returns TYPE_PROPERTY. Do not override!
		virtual ObjectAccessorType getAccessorType() {
			return TYPE_PROPERTY;
		}
		//! Called to retrieve the current value
		virtual void get( Value& valueOut ) {}
		//! Called to set the current value
		virtual void set( Value& valueIn ) {}
	};


	//############################################################################
	//! Base class for Method Accessors
	/*! Object Method that applications wish to expose should inherit this class. */
	class OPENGUI_API ObjectMethod : ObjectAccessor {
	public:
		//! Returns TYPE_METHOD. Do not override!
		virtual ObjectAccessorType getAccessorType() {
			return TYPE_METHOD;
		}
		//! Called when the method is invoked.
		virtual void invoke( ValueList& paramIn, ValueList& returnOut ) = 0;
	};


	//############################################################################
	/*! \brief The ObjectAccessorList is a inheritance capable string -> ObjectAccessor mapping.
	*/
	class OPENGUI_API ObjectAccessorList {
	public:
		//! constructor
		ObjectAccessorList();
		//! destructor
		~ObjectAccessorList();

		//! Sets the parent of this ObjectAccessorList.
		void setParent( ObjectAccessorList* parent );
		//! Retrieves the current parent of this ObjectAccessorList.
		ObjectAccessorList* getParent();

		//! Adds a new ObjectAccessor
		void addAccessor( ObjectAccessor* accessor );

		//! Gets the ObjectAccessor by \c accessorName
		ObjectAccessor* getAccessor( const std::string& accessorName, bool recursive = true );

	private:
		ObjectAccessorList* mParent;

		typedef std::map<std::string, ObjectAccessor*> ObjectAccessorMap;
		ObjectAccessorMap mObjectAccessorMap;
	};


}//namespace OpenGUI{

#endif
