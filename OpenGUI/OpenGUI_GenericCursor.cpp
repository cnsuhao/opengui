// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_GenericCursor.h"
#include "OpenGUI_ImageryManager.h"

namespace OpenGUI {
	//############################################################################
	class GenericCursor_Image_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Imagery";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				GenericCursor& c = dynamic_cast<GenericCursor&>( objectRef );
				valueOut.setValue( c.getImagery()->getName() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				GenericCursor& c = dynamic_cast<GenericCursor&>( objectRef );
				ImageryPtr img = ImageryManager::getSingleton().getImagery( valueIn.getValueAsString() );
				c.setImagery( img );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_STRING;
		}
	}
	gGenericCursor_Image_ObjectProperty;
	//############################################################################
	class GenericCursor_Offset_ObjectProperty : public ObjectProperty {
	public:
		virtual const char* getAccessorName() {
			return "Offset";
		}
		//############################################################################
		virtual void get( Object& objectRef, Value& valueOut ) {
			try {
				GenericCursor& c = dynamic_cast<GenericCursor&>( objectRef );
				valueOut.setValue( c.getOffset() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual void set( Object& objectRef, Value& valueIn ) {
			try {
				GenericCursor& c = dynamic_cast<GenericCursor&>( objectRef );
				c.setOffset( valueIn.getValueAsIVector2() );
			} catch ( std::bad_cast e ) {
				OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
			}
		}
		//############################################################################
		virtual Value::ValueType getPropertyType() {
			return Value::T_IVECTOR2;
		}
	}
	gGenericCursor_Offset_ObjectProperty;
	//############################################################################
	class GenericCursor_ObjectAccessorList : public ObjectAccessorList {
	public:
		GenericCursor_ObjectAccessorList() {
			addAccessor( &gGenericCursor_Image_ObjectProperty );
			addAccessor( &gGenericCursor_Offset_ObjectProperty );
		}
		~GenericCursor_ObjectAccessorList() {}
	}
	gGenericCursor_ObjectAccessorList;
	//############################################################################
	//############################################################################

	//############################################################################
	ObjectAccessorList* GenericCursor::getAccessors() {
		return &gGenericCursor_ObjectAccessorList;
	}
	//############################################################################
	//############################################################################
	GenericCursor::GenericCursor() {
		if ( gGenericCursor_ObjectAccessorList.getParent() == 0 )
			gGenericCursor_ObjectAccessorList.setParent( Cursor::getAccessors() );

		// the constructor values for these properties is sufficient
		//mImagery = 0;
		//mOffset = 0x0;
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
		_updateOffsetCache();
	}
	//############################################################################
	ImageryPtr GenericCursor::getImagery() {
		return mImagery;
	}
	//############################################################################
	void GenericCursor::setOffset( const IVector2& offset ) {
		mOffset = offset;
		_updateOffsetCache();
	}
	//############################################################################
	const IVector2& GenericCursor::getOffset() {
		return mOffset;
	}
	//############################################################################
	void GenericCursor::onDraw( Object* sender, DrawCursor_EventArgs& evtArgs ) {
		Brush& b = evtArgs.brush;
		FRect tmpCursor;
		const FVector2& size = getSize();

		tmpCursor.setSize( size );

		b.pushPosition( evtArgs.Position );

		if ( mImagery ) {
			b.pushPosition( -( size.x * mOffsetCache.x ), -( size.y * mOffsetCache.y ) );
			b.Image.drawImage( mImagery, tmpCursor );
			b.pop(); // b.pushPosition( offset );
		} else {
			b.Primitive.drawRect( tmpCursor );
		}

		b.pop(); // b.pushPosition( evtArgs.Position );
	}
	//############################################################################
	void GenericCursor::_updateOffsetCache() {
		if ( mImagery ) {
			IVector2& imgSize = mImagery->getImagesetRect().getSize();
			mOffsetCache.x = (( float ) mOffset.x / ( float ) imgSize.x );
			mOffsetCache.y = (( float ) mOffset.y / ( float ) imgSize.y );
		}
	}
	//############################################################################

}//namespace OpenGUI{
