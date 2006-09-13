#ifndef AC660DA3_935C_49BC_AB5A_0CC6BBFBFA8E
#define AC660DA3_935C_49BC_AB5A_0CC6BBFBFA8E

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Value.h"
//

namespace OpenGUI {
	//! display
	namespace Test {
		class ObjectAccessorList; //forward declaration

		//! Base class for all GUI objects. Provides an exposed interface to the Accessor system.
		class OPENGUI_API Object {
		public:
			Object();
			virtual ~Object();

			//! returns the value of \c propertyName via \c valueOut
			void getProperty( const std::string& propertyName, Types::Value& valueOut );
			//! sets the value of \c propertyName to the contents of \c valueIn
			void setProperty( const std::string& propertyName, Types::Value& valueIn );
			//! invokes \c methodName, sending \c paramIn as arguments, and catching return values in \c returnOut
			void callMethod( const std::string& methodName, Types::ValueList& paramIn, Types::ValueList& returnOut );

			//! returns this object's ObjectAccessorList head
			virtual ObjectAccessorList* getAccessors();
			virtual char* getClassName();
		};

	}//namespace Test{
}//namespace OpenGUI{

#endif
