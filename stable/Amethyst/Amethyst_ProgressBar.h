#ifndef Amethyst_ProgressBar_h__
#define Amethyst_ProgressBar_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {
		//! progress bar
		class AMETHYST_API ProgressBar : public Control {
		public:
			ProgressBar();
			virtual ~ProgressBar();

			void setFont( const Font& fnt )			{
				mFont = fnt;
			}
			const Font& getFont() const				{
				return mFont;
			}

			void setStep( float s )					{
				mStep = s;
			}
			float getStep() const					{
				return mStep;
			}

			void setCurrentValue( float s )			{
				mCurrentValue = s;
			}
			float getCurrentValue() const			{
				return mCurrentValue;
			}

			void setDoneColor( const Color &color )	{
				m_cComplete = color;
			}
			const Color& getDoneColor() const		{
				return m_cComplete;
			}

			void setTodoColor( const Color &color )	{
				m_cTodo = color;
			}
			const Color& getTodoColor() const		{
				return m_cTodo;
			}

			void doStep()							{
				mCurrentValue += mStep;
				if(mCurrentValue >1.0f)
					mCurrentValue = 1.0f;
			}

			static Widget* createProgressBarFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			virtual void onResized( Object* sender, Resized_EventArgs& evtArgs );

			Font mFont;
			float mStep;
			float mCurrentValue;

			Color m_cComplete;
			Color m_cTodo;
		};
	}
}

#endif // Amethyst_ProgressBar_h__
