#include "Amethyst_Label.h"

namespace OpenGUI {
	namespace Amethyst {
		class Label_Text_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Text";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Label& l = dynamic_cast<Label&>( objectRef );
					valueOut.setValue( l.getText() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Label& l = dynamic_cast<Label&>( objectRef );
					l.setText( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_STRING;
			}
		}
		gLabel_Text_ObjectProperty;
		//############################################################################
		class Label_Alignment_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Text";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					Label& l = dynamic_cast<Label&>( objectRef );
					valueOut.setValue( l.getText() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					Label& l = dynamic_cast<Label&>( objectRef );
					l.setText( valueIn.getValueAsString() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_IVECTOR2;
			}
		}
		gLabel_Alignment_ObjectProperty;
		//############################################################################
		class Label_ObjectAccessorList : public ObjectAccessorList {
		public:
			Label_ObjectAccessorList() {
				addAccessor( &gLabel_Text_ObjectProperty );
				addAccessor( &gLabel_Alignment_ObjectProperty );
			}
			~Label_ObjectAccessorList() {}
		}
		gLabel_ObjectAccessorList;
		//############################################################################
		//############################################################################
		ObjectAccessorList* Label::getAccessors() {
			return &gLabel_ObjectAccessorList;
		}
		//############################################################################
		char* Label::getClassName() {
			return "Amethyst::Label";
		}
		//############################################################################
		Widget* Label::CreateLabelFactory() {
			return new Label();
		}
		//############################################################################
		Label::Label() {
			if ( gLabel_ObjectAccessorList.getParent() == 0 )
				gLabel_ObjectAccessorList.setParent( Control::getAccessors() );

			//setup defaults for properties
			mText = "";
			m_alignh = TextAlignment::ALIGN_LEFT;
			m_alignv = TextAlignment::ALIGN_TOP;
		}
		//############################################################################
		Label::~Label() {
			/**/
		}
		//############################################################################
		void Label::setText( const std::string& text ) {
			invalidate();
			mText = text;
		}
		//############################################################################
		const std::string& Label::getText() const {
			return mText;
		}
		//############################################################################
		void Label::setFont( const Font& fnt ) {
			mFont = fnt;
		}
		//############################################################################
		const Font& Label::getFont() const {
			return mFont;
		}
		//############################################################################
		void Label::setAlignment( TextAlignment::Alignment h, TextAlignment::Alignment v ) {
			m_alignh = h;
			m_alignv = v;
		}
		//############################################################################
		void Label::getAlignment( TextAlignment::Alignment &h, TextAlignment::Alignment &v ) {
			h = m_alignh;
			v = m_alignv;
		}
		//############################################################################
		void Label::setAlignment( IVector2 &align ) {
			TextAlignment::Alignment h = ( TextAlignment::Alignment ) align.x;
			TextAlignment::Alignment v = ( TextAlignment::Alignment ) align.y;
			setAlignment( h, v );
		}
		//############################################################################
		void Label::getAlignment( IVector2 &align ) {
			TextAlignment::Alignment h;
			TextAlignment::Alignment v;
			getAlignment( h, v );
			align.x = h;
			align.y = v;
		}
		//############################################################################

		void Label::onDraw( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			b.Text.drawTextArea( mText, getRect(), mFont, false, m_alignh, m_alignv );
		}
		//############################################################################
	} // namespace Amethyst{
} // namespace OpenGUI{
