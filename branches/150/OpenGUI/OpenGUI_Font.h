// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef A3E35C4A_48F9_429b_B13A_F3AB9BFF90D4
#define A3E35C4A_48F9_429b_B13A_F3AB9BFF90D4

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Resource.h"
#include "OpenGUI_RefObject.h"
#include "OpenGUI_FontSet.h"

namespace OpenGUI {


	//! A handle representing font type and size
	/*! Fonts are referenced using the Font object, which contain a reference to a FontSet and
	the desired size. These handles can be created at will by the user, and are automatically
	bound to the appropriate FontSet during the constructor. These handles are also capable of
	referencing the default FontSet at the default size, and this is usually accomplished by
	creating the object using the default constructor.

	Font handles also provide automatic support for	delayed binding under certain conditions
	and uses. If a Font is using delayed binding, the actual binding will occur on first use
	in a rendering context. If the desired FontSet cannot be found, the Font handle will
	automatically bind to the default Font. If no default Font is available, an exception will
	occur. ( The default Font is automatically bound to the first FontSet registered with the
	FontManager, and can be changed by FontManager::SetDefaultFont(). )

	\note You'll notice there are no methods for changing the size or FontSet of a Font object.
	That is because it is intended that a new Font object be created whenever the size or font
	type needs to be changed. Enough information about a Font handle can be retrieved to provide
	an avenue for changing only a single attribute.

	\warning Font sizes that are less than or equal to 0.0f are not legal for bound Font handles,
	and will automatically be interpretted as a request for the default font size.
	*/
	class OPENGUI_API Font {
	public:
		//! Create a font handle that will either immediate or delayed bind to the default font.
		Font();

		//! Create a font handle to the given \a fontSet at the given \a fontSize.
		Font( FontSetPtr fontSet, float fontSize );

		//! Create a font handle to the given registered \a fontName at the given \a fontSize.
		Font( const String& fontName, float fontSize );

		//! public destructor does nothing special
		~Font() {
			/**/
		}

		//! Returns \c true if this handle is bound to a FontSet
		bool isBound() const {
			return m_Bound;
		}

		//! Forces immediate binding of this Font, throwing an exception if the binding does not complete.
		void bind();

		//! Returns the name of the FontSet this Font is currently or will be bound to
		const String& getName() const {
			return m_FontName;
		}

		//! Returns the font size of this Font handle
		float getSize() const {
			return m_FontSize;
		}

		//! Returns the FontSetPtr of the Font handle
		FontSetPtr getFontSetPtr() const {
			return m_FontSetPtr;
		}

		//! Provides direct access to the bound FontSet's functions
		/*! This causes an immediate bind, throwing an exception if the bind fails. */
		FontSet* operator->() {
			bind();
			return m_FontSetPtr.operator ->();
		}

		//! Equality operator
		bool operator ==( const Font& right );

	private:
		bool m_Bound;
		FontSetPtr m_FontSetPtr;
		float m_FontSize;
		String m_FontName;

		bool _tryBind(); // tries to bind the font, returning false if failed for any reason
	};
};

#endif // A3E35C4A_48F9_429b_B13A_F3AB9BFF90D4

