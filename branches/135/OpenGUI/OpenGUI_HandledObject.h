// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef B0BDEF13_B844_499a_859C_A7D3D68B6427
#define B0BDEF13_B844_499a_859C_A7D3D68B6427

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_CONFIG.h"

namespace OpenGUI {
	//! Provides a single base class to maintain object handles for use with bindings
	/*! Each base class that is likely to require a retrievable handle derives from
	HandledObject. 
	*/
	class OPENGUI_API HandledObject {
	public:
		HandledObject(): m_HandlePtr( 0 ) {}
		~HandledObject() {
			if ( m_HandlePtr ) {
				_Free_ObjectHandle();
			}
		}
		void _Init_ObjectHandle( void* handlePointer ) {
			m_HandlePtr = handlePointer;
		}
		void _Free_ObjectHandle( void ) {
			delete m_HandlePtr;
		}
		void* _Get_ObjectHandle( void ) {
			return m_HandlePtr;
		}
	private:
		void* m_HandlePtr;
	};
} // namespace OpenGUI {

#endif // B0BDEF13_B844_499a_859C_A7D3D68B6427
