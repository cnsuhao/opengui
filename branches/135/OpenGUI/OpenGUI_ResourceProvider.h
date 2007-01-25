// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef C2BAA2EC_6763_411d_8E50_19614B119573
#define C2BAA2EC_6763_411d_8E50_19614B119573

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Resource.h"

namespace OpenGUI {
	//! Abstract class. Used as a base class for custom resource providers.
	class OPENGUI_API ResourceProvider {
	public:
		// Constructor (base implemenation does nothing)
		ResourceProvider() { }
		// virtual destructor (base implemenation does nothing)
		virtual ~ResourceProvider() { }

		//! This will be called whenever %OpenGUI needs data from the registered resource provider.
		virtual void loadResource( const String& filename, Resource& output ) = 0;

		//! This is called whenever %OpenGUI is done with the data and is ready to destroy the Resource contents
		virtual void unloadResource( Resource& resource ) = 0;
	};
}
;//namespace OpenGUI{
#endif

