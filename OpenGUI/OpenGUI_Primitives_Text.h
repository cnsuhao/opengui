#ifndef DEBD741D_17FC_427b_B0BE_929BC6F5654B
#define DEBD741D_17FC_427b_B0BE_929BC6F5654B

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{
	//class Texture; //forward declaration
	//class Imagery; //forward declaration
	//class Element; //forward declaration

	namespace Render{

		//! Provides a simple interface for drawing text strings
		/*! The primitive maintains stateful positioning, meaning that as text is
		drawn in internal next-character-position is updated so that future output
		generated from the primitive is appended to existing output. This internal
		positioning can be altered only by outputting text and the \c reset() and
		\c advanceLine() functions.
		*/
		class OPENGUI_API PrimitiveText : public Primitive{
		public:
			//! default constructor
			PrimitiveText();
			virtual ~PrimitiveText();
			//! returns the RenderOperationList that is the result of this operation
			RenderOperationList getRenderOperationList();
			//! Sets the element used as the context for obtaining pixel alignment
			void setContext(Element* contextElement);
			//! Sets the text string to generate on the next call to getRenderOperationList()
			void setText(std::string textString);
			//! Sets the font by name, and the size of the font
			void setFont(std::string fontName, unsigned int fontSize_points);
			//! Sets the position of the primitive
			void setPosition(const FVector2& baselinePosition);
			//! Gets the current position of the primitive
			FVector2 getPosition();
			//! Advances the current pen position of the primitive to the next line of text
			/*! \return The new pen position offset after the line advance */
			FVector2 advanceLine(bool carriageReturn=true);
			//! Resets the pen position offset to 0,0
			/*! \return The new pen position offset after the reset (will always be 0,0)*/
			FVector2 reset();

			//! Returns the width of the current text string 
			/*! \note This function requires access to each of glyphs' metrics,
			and will hit the font cache to get them. This means that the glyphs
			will be loaded into the font cache. There is currently no way around this.
			*/
			float getTextWidth();
			//! Returns the height of the current text string
			float getTextHeight();
			//! Returns the combined width and height of the text string
			/*! The results of this function assume that the pen position is at the starting
			location. As such, its results will not reflect the width difference that would
			normally occur if the pen were to carriage return due to a new line character.
			*/
			FVector2 getTextSize();
			//! Returns the height of a single line of text. Does not include any additional line spacing that may be specified by \c setLineSpacing()
			float getLineHeight();

			//! Returns the width of the current text string in pixels
			/*! \note This function requires access to each of glyphs' metrics,
			and will hit the font cache to get them. This means that the glyphs
			will be loaded into the font cache. There is currently no way around this.
			*/
			int getTextPixelWidth();
			//! Returns the height of the current text string in pixels
			int getTextPixelHeight();
			//! Returns the combined width and height of the text string in pixels
			/*! The results of this function assume that the pen position is at the starting
			location. As such, its results will not reflect the width difference that would
			normally occur if the pen were to carriage return due to a new line character.
			*/
			IVector2 getTextPixelSize();
			//! Returns the height of a single line of text in pixels. Does not include any additional line spacing that may be specified by \c setLineSpacing()
			int getLinePixelHeight();

			//! Adjusts the spacing between glyphs in pixels
			/*! \remark The value is represented as a float to support fractions of pixels. */
			void setTextSpacing(float spacing_per_glyph){mAdvTextSpacing = spacing_per_glyph;}
			//! Gets the current spacing between glyphs in pixels
			/*! \remark The value is represented as a float to support fractions of pixels. */
			float getTextSpacing(){return mAdvTextSpacing;}

			//! Adjusts the spacing between lines in pixels
			/*! \remark The value is represented as a float to support fractions of pixels. */
			void setLineSpacing(float spacing_per_line){mAdvLineSpacing = spacing_per_line;}
			//! Gets the current spacing between glyphs in pixels
			/*! \remark The value is represented as a float to support fractions of pixels. */
			float getLineSpacing(){return mAdvLineSpacing;}

			//! Toggles automatic line advance when the new line character (\\n) is found. <i>Default is off</i>
			/*! Automatic line advance implies a carriage return as well. \c advanceLine(true) */
			void setAutoLineAdvance(bool auto_advance){mAutoLineFeed = auto_advance;}
			//! Returns the current value of the automatic line advance setting.
			bool getAutoLineAdvance(){return mAutoLineFeed;}

			// renderText( Rect, text, font, color, align, scroll )

		private:
			std::string mTextContents;
			FVector2 mPosition;
			FVector2 mPenPosition;
			Element* mContext;

			std::string mFontName;
			unsigned int mFontSize;

			float mAdvTextSpacing;
			float mAdvLineSpacing;
			unsigned int mLineCount;

			bool mAutoLineFeed;

			FVector2 _getPixelScale();
		};

		//! Provides a simple interface for generating text areas (text in a box)
		class OPENGUI_API PrimitiveTextBox : public Primitive{
		public:
			//! constructor
			PrimitiveTextBox();
			virtual ~PrimitiveTextBox();
			//! returns the RenderOperationList that is the result of this operation
			RenderOperationList getRenderOperationList();

			//! Sets the element used as the context for obtaining pixel alignment
			void setContext(Element* contextElement){mContext = contextElement;}
			//! Get the current position and size of the Box
			FRect getRect(){return mRect;}
			//! Sets the size and position of the Box to the given FRect
			void setRect(FRect rect){mRect=rect;}

			//! sets the text to place in the text box
			void setText(std::string textString);
			//! sets the font and font size to use in rendering
			void setFont(std::string fontName, unsigned int fontSize_points);

			//! sets the horizontal alignment method to apply to the output text
			void setAlignment_Horiz(TextAlignment alignment){mAlignHoriz = alignment;}
			//! retrieves the current horizontal alignment method
			TextAlignment getAlignment_Horiz(){return mAlignHoriz;}

			//! sets the vertical alignment method to apply to the output text
			void setAlignment_Vert(TextAlignment alignment){mAlignVert = alignment;}
			//! retrieves the current vertical alignment method
			TextAlignment getAlignment_Vert(){return mAlignVert;}

			//! toggles automatic word wrapping
			void setAutoWrap(bool wrap){mAutoWrap=wrap;}
			//! get current setting of word wrapping
			bool getAutoWrap(){return mAutoWrap;}

		private:
			std::string mTextContents;
			FRect mRect;
			Element* mContext;

			std::string mFontName;
			unsigned int mFontSize;

			TextAlignment mAlignVert;
			TextAlignment mAlignHoriz;

			float mAdvTextSpacing;
			float mAdvLineSpacing;

			bool mAutoWrap;

			typedef std::list<std::string> StringList;
			void _WrapText(StringList& strList);
			std::string _SubTextByWidth(std::string input, float width);
			//Breaks a string into a list of strings by splitting on new-line characters
			void _Tokenize(const std::string& inputStr, StringList& outputStrList, char token);
			FVector2 _getPixelScale();
		};

	};//namespace Render{
};
#endif
