#include "Amethyst_ProgressBar.h"

namespace OpenGUI {
	namespace Amethyst {

		class ProgressBar_Step_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "Step";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ProgressBar & l = dynamic_cast<ProgressBar&>( objectRef );
					valueOut.setValue( l.getStep() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ProgressBar& l = dynamic_cast<ProgressBar&>( objectRef );
					l.setStep( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gProgressBar_Step_ObjectProperty;

		class ProgressBar_CurrentValue_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "CurrentValue";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ProgressBar & l = dynamic_cast<ProgressBar&>( objectRef );
					valueOut.setValue( l.getCurrentValue() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ProgressBar& l = dynamic_cast<ProgressBar&>( objectRef );
					l.setCurrentValue( valueIn.getValueAsFloat() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gProgressBar_CurrentValue_ObjectProperty;

		class ProgressBar_DoneColor_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "DoneColor";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ProgressBar & l = dynamic_cast<ProgressBar&>( objectRef );
					valueOut.setValue( l.getDoneColor() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ProgressBar& l = dynamic_cast<ProgressBar&>( objectRef );
					l.setDoneColor( valueIn.getValueAsColor() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_COLOR;
			}
		}
		gProgressBar_DoneColor_ObjectProperty;
		class ProgressBar_TodoColor_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "TodoColor";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ProgressBar & l = dynamic_cast<ProgressBar&>( objectRef );
					valueOut.setValue( l.getTodoColor() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ProgressBar& l = dynamic_cast<ProgressBar&>( objectRef );
					l.setTodoColor( valueIn.getValueAsColor() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_COLOR;
			}
		}
		gProgressBar_TodoColor_ObjectProperty;


		// this is a goofy property, any access will cause the "step" function to be called
		class ProgressBar_DoStep_ObjectProperty : public ObjectProperty {
		public:
			virtual const char* getAccessorName() {
				return "DoStep";
			}
			//############################################################################
			virtual void get( Object& objectRef, Value& valueOut ) {
				try {
					ProgressBar & l = dynamic_cast<ProgressBar&>( objectRef );
					l.doStep();
					valueOut.setValue( l.getCurrentValue() );
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual void set( Object& objectRef, Value& valueIn ) {
				try {
					ProgressBar& l = dynamic_cast<ProgressBar&>( objectRef );
					l.doStep();
				} catch ( std::bad_cast e ) {
					OG_THROW( Exception::ERR_INVALIDPARAMS, "Bad Object Pointer", __FUNCTION__ );
				}
			}
			//############################################################################
			virtual Value::ValueType getPropertyType() {
				return Value::T_FLOAT;
			}
		}
		gProgressBar_DoStep_ObjectProperty;

		class ProgressBar_ObjectAccessorList : public ObjectAccessorList {
		public:
			ProgressBar_ObjectAccessorList() {
				addAccessor( &gProgressBar_Step_ObjectProperty );
				addAccessor( &gProgressBar_CurrentValue_ObjectProperty );
				addAccessor( &gProgressBar_DoStep_ObjectProperty );
				addAccessor( &gProgressBar_TodoColor_ObjectProperty);
				addAccessor( &gProgressBar_DoneColor_ObjectProperty);
			}
			~ProgressBar_ObjectAccessorList() {}
		}
		gProgressBar_ObjectAccessorList;



		ProgressBar::ProgressBar()
		{
			if(gProgressBar_ObjectAccessorList.getParent() == NULL)
				gProgressBar_ObjectAccessorList.setParent(Widget::getAccessors());

			mStep = 0.1f;
			mCurrentValue = 0.0f;

			m_cComplete = Color(0,0,1,1);
			m_cTodo = Color(1,0,0,1);
		}

		ProgressBar::~ProgressBar()
		{
		}

		Widget* ProgressBar::createProgressBarFactory() {
			return new ProgressBar;
		}

		void ProgressBar::onDraw( Object* sender, Draw_EventArgs& evtArgs )
		{
			Brush& b = evtArgs.brush;
			FRect complete, todo;

			complete = getRect();
			complete.setWidth(mCurrentValue * complete.getWidth());

			todo = getRect();
			todo.offset(FVector2(mCurrentValue * todo.getWidth(), 0.0f));
			todo.setWidth((1.0f - mCurrentValue) * todo.getWidth());

			b.pushColor(m_cComplete);
			b.Primitive.drawRect(complete);
			b.pop();

			b.pushColor(m_cTodo);
			b.Primitive.drawRect(todo);
			b.pop();

			char buf[16];
			sprintf(buf, "%3.0f%%",mCurrentValue*100.0f);
			std::string pctText = buf;
			b.Text.drawTextArea( pctText, getRect(), mFont, false, TextAlignment::ALIGN_CENTER, TextAlignment::ALIGN_CENTER );
		}

		void ProgressBar::onResized( Object* sender, Resized_EventArgs& evtArgs )
		{
		}
	}
}
