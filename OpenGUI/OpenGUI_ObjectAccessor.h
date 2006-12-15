// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef E278D21F_0B04_437C_8A77_E84A74699F89
#define E278D21F_0B04_437C_8A77_E84A74699F89

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_Object.h"

namespace OpenGUI {


	//############################################################################
	//! Base class for Accessor system
	/*! This is an internal abstract base class. All accessors must be derived from either
		ObjectProperty or ObjectMethod.
	*/
	class OPENGUI_API ObjectAccessor {
	public:
		ObjectAccessor() {}
		virtual ~ObjectAccessor() {}
		//! Returns the name of the group of this accessor, default is "General"
		virtual const char* getAccessorGroup();
		//! Returns the name of this accessor
		virtual const char* getAccessorName() = 0;

		//! \internal Accessor type identification
		enum ObjectAccessorType {
			TYPE_PROPERTY, TYPE_METHOD
		};

		//! \internal Returns the type of Accessor
		/*! \internal This is automatically handled when you inherit from ObjectProperty or ObjectMethod */
		virtual ObjectAccessorType _getAccessorType() = 0;
	};


	//############################################################################
	//! Base class for Property Accessors
	/*! Object Properties that applications wish to expose should inherit this class. */
	class OPENGUI_API ObjectProperty : public ObjectAccessor {
	public:
		virtual ~ObjectProperty() {}

		//! \internal Returns TYPE_PROPERTY. Do not override!
		virtual ObjectAccessorType _getAccessorType() {
			return TYPE_PROPERTY;
		}
		//! Called to retrieve the current value
		virtual void get( Object& objectRef, Value& valueOut ) = 0;
		//! Called to set the current value
		virtual void set( Object& objectRef, Value& valueIn ) = 0;
		//! Needs to return the expected Value type
		virtual Value::ValueType getPropertyType() = 0;
		//! Used by ObjectAccessorList to determine if this property is write protected. Default returns \c TRUE ( property can be \c get and \c set )
		virtual bool getPermSettable();
	};


	//############################################################################
	//! Base class for Method Accessors
	/*! Object Method that applications wish to expose should inherit this class. */
	class OPENGUI_API ObjectMethod : public ObjectAccessor {
	public:
		virtual ~ObjectMethod() {}

		//! \internal Returns TYPE_METHOD. Do not override!
		virtual ObjectAccessorType _getAccessorType() {
			return TYPE_METHOD;
		}
		//! Called when the method is invoked.
		virtual void invoke( Object& objectRef, ValueList& paramIn, ValueList& returnOut ) = 0;
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
