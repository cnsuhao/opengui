// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef EventArgs_h__
#define EventArgs_h__

using namespace System;

namespace OpenGUI_Net {

	//############################################################################
	public ref class EventArgs {
	public:
		//
	};
	//############################################################################
	public ref class Input_EventArgs: EventArgs {
	public:
		Input_EventArgs() {
			mConsumed = false;
		}
		void eat() {
			mConsumed = true;
		}
		property bool Consumed{
			bool get() {
				return mConsumed;
			}
		}
	private:
		bool mConsumed;
	};
	//############################################################################
	public ref class Cursor_EventArgs: Input_EventArgs {
	public:
		Cursor_EventArgs( FVector2 position ) {
			mPosition = position;
		}
		property FVector2 Position{
			FVector2 get() {
				return mPosition;
			}
		}
		property float X{
			float get() {
				return mPosition.x;
			}
		}
		property float Y{
			float get() {
				return mPosition.y;
			}
		}
	private:
		FVector2 mPosition;
	};
	//############################################################################
	public ref class Key_EventArgs: Input_EventArgs {
	public:
		Key_EventArgs( char key ) {
			mKey = key;
		}

		property char Character{
			char get() {
				return mKey;
			}
		}
	private:
		char mKey;
	};
	//############################################################################

} // namespace OpenGUI_Net {

#endif // EventArgs_h__
