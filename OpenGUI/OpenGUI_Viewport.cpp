// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Viewport.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"

namespace OpenGUI {
	//############################################################################
	Viewport::Viewport() {
		/**/
	}
	//############################################################################
	Viewport::~Viewport() {
		while ( mScreens.size() > 0 ) {
			Screen* screen = *( mScreens.begin() );
			screen->setViewport( 0 );
		}
	}
	//############################################################################
	void Viewport::_screenAttach( Screen* screen ) {
		ScreenSet::iterator iter = mScreens.find( screen );
		if ( iter != mScreens.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Screen [" + screen->getName() + "] is already attached to this Viewport", __FUNCTION__ );
		mScreens.insert( screen );
		screenAttached( screen );
	}
	//############################################################################
	void Viewport::_screenDetach( Screen* screen ) {
		ScreenSet::iterator iter = mScreens.find( screen );
		if ( iter == mScreens.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Screen [" + screen->getName() + "] is not attached to this Viewport", __FUNCTION__ );
		mScreens.erase( screen );
		screenDetached( screen );
	}
	//############################################################################
	const Viewport::ScreenSet& Viewport::getScreenSet() {
		return mScreens;
	}
	//############################################################################
}
