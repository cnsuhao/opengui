#include "OpenGUI_GenericCursor.h"

namespace OpenGUI {

	//############################################################################
	GenericCursor::GenericCursor() {
		/**/
	}
	//############################################################################
	GenericCursor::~GenericCursor() {
		/**/
	}
	//############################################################################
	CursorPtr GenericCursor::GenericCursorFactory() {
		return new GenericCursor;
	}
	//############################################################################
	void GenericCursor::setImagery( ImageryPtr imagery ) {
		mImagery = imagery;
	}
	//############################################################################
	ImageryPtr GenericCursor::getImagery() {
		return mImagery;
	}
	//############################################################################
	void GenericCursor::setOffset( const FVector2& offset ) {
		mOffset = offset;
	}
	//############################################################################
	const FVector2& GenericCursor::getOffset() {
		return mOffset;
	}
	//############################################################################
	void GenericCursor::onDraw( Object* sender, DrawCursor_EventArgs& evtArgs ) {
		if ( mImagery ) {}
		Brush& b = evtArgs.brush;
		FRect tmpCursor;
		tmpCursor.setHeight( 30.0f );
		tmpCursor.setWidth( 30.0f );
		b.pushPosition( evtArgs.Position );
		b.pushRotation( Degree( 45.0f ) );
		b.Primitive.drawRect( tmpCursor );
		b.pop();
		b.pop();
	}
	//############################################################################

}//namespace OpenGUI{
