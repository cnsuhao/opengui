// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"

#include "Screen.h"
#include "ObjectHandle.h"
#include "Viewport.h"

namespace OpenGUI_Net {

	//############################################################################
	bool Screen::injectCursorMovement( float x_rel, float y_rel ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->injectCursorMovement( x_rel, y_rel );
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::injectCursorPosition( float x_pos, float y_pos ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->injectCursorPosition( x_pos, y_pos );
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::injectCursorPosition_Percent( float x_perc, float y_perc ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->injectCursorPosition( x_perc, y_perc );
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::injectCursorPress() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->injectCursorPress();
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::injectCursorRelease() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return 	s->injectCursorRelease();
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::injectCursorPress_State( bool pressed ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->injectCursorPress_State( pressed );
		THRU_THROW_END
	}
	//############################################################################
	FVector2 Screen::getCursorPos() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		FVector2 fv2;
		THRU_THROW_BEGIN
		fv2 = Marshal::FVECTOR2( s->getCursorPos() );
		THRU_THROW_END
		return fv2;
	}
	//############################################################################
	FVector2 Screen::getCursorPos_Percent() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		FVector2 fv2;
		THRU_THROW_BEGIN
		fv2 = Marshal::FVECTOR2( s->getCursorPos_Percent() );
		THRU_THROW_END
		return fv2;
	}
	//############################################################################
	//void setCursor( Cursor cursor );
	//############################################################################
	void Screen::enableCursor() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->enableCursor();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::disableCursor() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->disableCursor();
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::cursorEnabled() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->cursorEnabled();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::showCursor() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->showCursor();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::hideCursor() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->hideCursor();
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::cursorVisible() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->cursorVisible();
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::injectCharacter( char character ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->injectCharacter( character );
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::isAutoTiming() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->isAutoTiming();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::setAutoTiming( bool doAutoTime ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->setAutoTiming( doAutoTime );
		THRU_THROW_END
	}
	//############################################################################
	void Screen::injectTime( unsigned int milliseconds ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->injectTime( milliseconds );
		THRU_THROW_END
	}
	//############################################################################
	void Screen::injectTime( float seconds ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->injectTime( seconds );
		THRU_THROW_END
	}
	//############################################################################
	String ^ Screen::getName() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		String ^ str;
		THRU_THROW_BEGIN
		str = Marshal::STRING( s->getName() );
		THRU_THROW_END
		return str;
	}
	//############################################################################
	FVector2 Screen::getSize() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		FVector2 fv2;
		THRU_THROW_BEGIN
		fv2 = Marshal::FVECTOR2( s->getSize() );
		THRU_THROW_END
		return fv2;
	}
	//############################################################################
	void Screen::setSize( FVector2 newSize ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		OpenGUI::FVector2 fv2 = Marshal::FVECTOR2( newSize );
		THRU_THROW_BEGIN
		s->setSize( fv2 );
		THRU_THROW_END
	}
	//############################################################################
	FVector2 Screen::getPPU() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		FVector2 fv2;
		THRU_THROW_BEGIN
		fv2 = Marshal::FVECTOR2( s->getPPU() );
		THRU_THROW_END
		return fv2;
	}
	//############################################################################
	FVector2 Screen::getUPI() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		FVector2 fv2;
		THRU_THROW_BEGIN
		fv2 = Marshal::FVECTOR2( s->getUPI() );
		THRU_THROW_END
		return fv2;
	}
	//############################################################################
	void Screen::setUPI( FVector2 newUPI ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		OpenGUI::FVector2 fv2 = Marshal::FVECTOR2( newUPI );
		THRU_THROW_BEGIN
		s->setUPI( fv2 );
		THRU_THROW_END
	}
	//############################################################################
	void Screen::update() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->update();
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::isAutoUpdating() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->isAutoUpdating();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::setAutoUpdating( bool autoUpdate ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->setAutoUpdating( autoUpdate );
		THRU_THROW_END
	}
	//############################################################################
	void Screen::setViewport( Viewport ^ viewport ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		MNYI;
		/*THRU_THROW_BEGIN
		s->setViewport();
		THRU_THROW_END*/
	}
	//############################################################################
	Viewport ^ Screen::getViewport() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		MNYI;
		/*THRU_THROW_BEGIN
		s->getViewport();
		THRU_THROW_END*/
	}
	//############################################################################
	void Screen::invalidateAll() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->invalidateAll();
		THRU_THROW_END
	}
	//############################################################################
	float Screen::statsGetUpdateTime() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->statsGetUpdateTime();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::statsResetUpdateTime() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->statsResetUpdateTime();
		THRU_THROW_END
	}
	//############################################################################
	void Screen::setActive( bool active ) {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		s->setActive( active );
		THRU_THROW_END
	}
	//############################################################################
	bool Screen::isActive() {
		sanityTest();
		OpenGUI::Screen* s = dynamic_cast<OpenGUI::Screen*>( getHandle()->getObject() );
		THRU_THROW_BEGIN
		return s->isActive();
		THRU_THROW_END
	}
	//############################################################################
} // namespace OpenGUI_Net {
