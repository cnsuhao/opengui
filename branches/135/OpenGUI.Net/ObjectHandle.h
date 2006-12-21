// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef ObjectHandle_h__
#define ObjectHandle_h__

using namespace System;

namespace OpenGUI_Net {
	ref class Object; // forward declaration

	class ObjectHandle: public OpenGUI::ObjectHandle {
	public:
		ObjectHandle();
		~ObjectHandle();
		Object ^ getManaged() {
			return m_ObjectRef;
		}
		void _setManaged( Object ^ mObject ) {
			m_ObjectRef = mObject;
		}
	private:
		gcroot < Object ^ > m_ObjectRef;
	};
} // namespace OpenGUI_Net {
#endif // ObjectHandle_h__
