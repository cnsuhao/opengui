#ifndef CCFEE719_8FDE_46ce_8F52_350F92CA56CD
#define CCFEE719_8FDE_46ce_8F52_350F92CA56CD

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Math.h"

namespace OpenGUI {
	//No thanks Bill
#undef min
#undef max

	/*! \addtogroup Types
	The base types used within %OpenGUI
	@{
	*/

	class Radian; //forward declaration
	class Degree; //forward declaration

	//! Represents radians and provide some basic utility functions.
	/*! This class is used to store radian values, as well as provide some basic
		conversion functions.
	*/
	class Radian {
	public:
		//! Constructor initialized with radian in a float
		explicit Radian( float radian_value = 0.0f ) : value( radian_value ) {}
		//! Constructor initialized with a Degree
		Radian( const Degree& degree_value ); //defined after Degree

		//! returns the current value as a float in degrees
		float valueDegrees() const {
			return Math::RadiansToDegrees( value );
		}
		//! returns the current value as a float in radians
		float valueRadians() const {
			return value;
		}

		//! assignment with a radian in a float
		const Radian& operator = ( const float& radian_float ) {
			value = radian_float;
			return *this;
		}

		//! assignment with a Radian
		const Radian& operator = ( const Radian& radian ) {
			value = radian.value;
			return *this;
		}
		//! assignment with a Degree
		inline const Radian& operator = ( const Degree& degree ); //defined after Degree

		//! addition with a Radian
		Radian operator + ( const Radian& right ) const {
			return Radian( value + right.value );
		}
		//! addition with a Degree
		inline Radian operator + ( const Degree& right ) const; //defined after Degree

		//! addition/assignment with a Radian
		Radian& operator += ( const Radian& right ) {
			value += right.value;
			return *this;
		}
		//! addition/assignment with a Degree
		inline Radian& operator += ( const Degree& right ); //defined after Degree

		//! inverse operator
		Radian operator - () {
			return Radian( -value );
		}

		//! subtraction with a Radian
		Radian operator - ( const Radian& right ) const {
			return Radian( value - right.value );
		}
		//! subtraction with a Degree
		inline Radian operator - ( const Degree& right ) const; //defined after Degree

		//! subtraction/assignment  with a Radian
		Radian& operator -= ( const Radian& right ) {
			value -= right.value;
			return *this;
		}
		//! subtraction/assignment  with a Degree
		inline Radian& operator -= ( const Degree& right ); //defined after Degree

		//! Equal
		bool operator == ( const Radian& right ) const {
			return value == right.value;
		}
		//! Not Equal
		bool operator != ( const Radian& right ) const {
			return value != right.value;
		}

		//! Less than
		bool operator < ( const Radian& right ) const {
			return value <  right.value;
		}
		//! Less than or equal
		bool operator <= ( const Radian& right ) const {
			return value <= right.value;
		}

		//Greater than
		bool operator > ( const Radian& right ) const {
			return value >  right.value;
		}
		//Greater than or equal
		bool operator >= ( const Radian& right ) const {
			return value >= right.value;
		}

	private:
		float value;
	};


	//! Represents degrees and provide some basic utility functions.
	/*! Degrees are not used by any functions in %OpenGUI, but are offered here
	as a supported type since they are the most human familiar method of measuring
	angles.
	*/
	class Degree {
	public:
		//! Constructor initialized with degree in a float
		explicit Degree( float degree_value = 0.0f ) : value( degree_value ) {}
		//! Constructor initialized with a Radian
		Degree( const Radian& radian_value ) {
			value = radian_value.valueDegrees();
		}

		//! returns the current value as a float in degrees
		float valueDegrees() const {
			return value;
		}
		//! returns the current value as a float in radians
		float valueRadians() const {
			return Math::DegreesToRadians( value );
		}

		//! assignment with a degree in a float
		const Degree& operator = ( const float& degree_float ) {
			value = degree_float;
			return *this;
		}

		//! assignment with a Degree
		const Degree& operator = ( const Degree& degree ) {
			value = degree.value;
			return *this;
		}
		//! assignment with a Radian
		const Degree& operator = ( const Radian& radian ) {
			value = radian.valueDegrees();
			return *this;
		}

		//! addition with a Degree
		Degree operator + ( const Degree& right ) const {
			return Degree( value + right.value );
		}
		//! addition with a Radian
		Degree operator + ( const Radian& right ) const {
			return Degree( value + right.valueDegrees() );
		}

		//! addition/assignment with a Degree
		Degree& operator += ( const Degree& right ) {
			value += right.value;
			return *this;
		}
		//! addition/assignment with a Radian
		Degree& operator += ( const Radian& right ) {
			value += right.valueDegrees();
			return *this;
		}

		//! inverse operator
		Degree operator - () {
			return Degree( -value );
		}

		//! subtraction with a Degree
		Degree operator - ( const Degree& right ) const {
			return Degree( value - right.value );
		}
		//! subtraction with a Radian
		Degree operator - ( const Radian& right ) const {
			return Degree( value - right.valueDegrees() );
		}

		//! subtraction/assignment  with a Degree
		Degree& operator -= ( const Degree& right ) {
			value -= right.value;
			return *this;
		}
		//! subtraction/assignment  with a Radian
		Degree& operator -= ( const Radian& right ) {
			value -= right.valueDegrees();
			return *this;
		}

		//! Equal
		bool operator == ( const Degree& right ) const {
			return value == right.value;
		}
		//! Not Equal
		bool operator != ( const Degree& right ) const {
			return value != right.value;
		}

		//! Less than
		bool operator < ( const Degree& right ) const {
			return value <  right.value;
		}
		//! Less than or equal
		bool operator <= ( const Degree& right ) const {
			return value <= right.value;
		}

		//Greater than
		bool operator > ( const Degree& right ) const {
			return value >  right.value;
		}
		//Greater than or equal
		bool operator >= ( const Degree& right ) const {
			return value >= right.value;
		}

	private:
		float value;
	};

	/*! @} */ //temporarily suspend grouping
	// THESE RADIAN METHODS ARE DEFINED HERE DUE TO INTERDEPENDENCE WITH DEGREE
	inline Radian::Radian( const Degree& degree_value ) {
		value = degree_value.valueRadians();
	}
	inline const Radian& Radian::operator= ( const Degree& degree ) {
		value = degree.valueRadians();
		return *this;
	}

	inline Radian Radian::operator+ ( const Degree& right ) const {
		return Radian( value + right.valueRadians() );
	}
	inline Radian& Radian::operator+= ( const Degree& right ) {
		value += right.valueRadians();
		return *this;
	}
	inline Radian Radian::operator- ( const Degree& right ) const {
		return Radian( value - right.valueRadians() );
	}
	inline Radian& Radian::operator-= ( const Degree& right ) {
		value -= right.valueRadians();
		return *this;
	}
	// END OF RADIAN/DEGREE DEPENDENT METHOD DEFINITIONS
	/*! \addtogroup Types
	@{
	*/

	//! IVector2s are two dimensional vectors based on integers.
	class OPENGUI_API IVector2 {
	public:
		//! constructor
		IVector2() : x( 0 ), y( 0 ) {}
		//! constructor
		IVector2( int x, int y ) : x( x ), y( y ) {}
		//! operator +
		IVector2 operator+( const IVector2& right ) const  {
			return IVector2( x + right.x, y + right.y );
		}
		//! operator -
		IVector2 operator-( const IVector2& right ) const  {
			return IVector2( x - right.x, y - right.y );
		}
		//! operator *
		IVector2 operator*( const IVector2& right ) const  {
			return IVector2( x * right.x, y * right.y );
		}
		//! operator /
		IVector2 operator/( const IVector2& right ) const  {
			return IVector2( x / right.x, y / right.y );
		}

		//! comparison operator
		bool operator==( const IVector2& right ) const  {
			return x == right.x && y == right.y;
		}
		//! comparison operator
		bool operator!=( const IVector2& right ) const  {
			return !operator==( right );
		}
		//! Return a string representation of this value
		std::string toStr() const {
			std::stringstream ss;
			ss << "( " << x << " x " << y << " )" ;
			return ss.str();
		}
		int x; //!< direct access to x
		int y; //!< direct access to y
	};

	//! IRects are rects built from int values. Internally they are comprised of two IVector2's.
	class OPENGUI_API IRect {
	public:
		//! constructor
		IRect() {}
		//! constructor
		IRect( const IVector2& min, const IVector2 max ): min( min ), max( max ) {}
		//! constructor
		IRect( const int& left, const int& top, const int& right, const int& bottom ) {
			min.y = top;
			min.x = left;
			max.x = right;
			max.y = bottom;
		}
		~IRect() {}

		//!returns top,left
		const IVector2& getPosition() const {
			return min;
		}
		//! return size as IVector2
		IVector2 getSize() const {
			return max - min;
		}
		//! return width
		int getWidth() const {
			return max.x - min.x;
		}
		//! return height
		int getHeight() const {
			return max.y - min.y;
		}
		//! return total area
		int getArea() const {
			return getWidth() * getHeight();
		}
		//! sets new width
		void setWidth( const int& newWidth ) {
			max.x = min.x + newWidth;
		}
		//! sets new height
		void setHeight( const int& newHeight ) {
			max.y = min.y + newHeight;
		}
		//! sets new size
		void setSize( const IVector2& newSize ) {
			max = min + newSize;
		}
		//! sets new position
		void setPosition( const IVector2& newPosition ) {
			IVector2 tmpSize = max - min;
			min = newPosition;
			max = min + tmpSize;
		}

		//! offset position by given IVector2
		void offset( const IVector2& offsetVector ) {
			min = min + offsetVector;
			max = max + offsetVector;
		}
		//! return true if given point is inside this IRect
		bool inside( IVector2 point ) {
			if (	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y )
				return true;
			return false;
		}
		//! Return a string representation of this value
		std::string toStr() const {
			std::stringstream ss;
			ss << "{ " << min.toStr() << " X " << max.toStr() << " }" ;
			return ss.str();
		}
		//! comparison operator
		bool operator==( const IRect& right ) const  {
			return min == right.min && max == right.max;
		}
		//! comparison operator
		bool operator!=( const IRect& right ) const  {
			return !operator==( right );
		}
		IVector2 min; //!< direct access to upper left point
		IVector2 max; //!< direct access to lower right point
	};


	//! The FVector2 is a two dimensional vector based on floats.
	/*!
	This object often represents a screen coordinate starting from the upper left corner of the screen.
	The value a FVector2 represents is very much an issue of context.
	In the rendering areas of OpenGUI, a FVector2 is quite often a representation of screen position between 0,0 (upper left) and 1,1 (lower right).
	*/
	class OPENGUI_API FVector2 {
	public:
		//! constructor
		FVector2() : x( 0 ), y( 0 ) {}
		//! constructor
		FVector2( float x, float y ) : x( x ), y( y ) {}
		//! operator +
		FVector2 operator+( const FVector2& right ) const  {
			return FVector2( x + right.x, y + right.y );
		}
		//! operator -
		FVector2 operator-( const FVector2& right ) const  {
			return FVector2( x - right.x, y - right.y );
		}
		//! operator *
		FVector2 operator*( const FVector2& right ) const  {
			return FVector2( x * right.x, y * right.y );
		}
		//! operator /
		FVector2 operator/( const FVector2& right ) const  {
			return FVector2( x / right.x, y / right.y );
		}

		//! comparison operator
		bool operator==( const FVector2& right ) const  {
			return x == right.x && y == right.y;
		}
		//! comparison operator
		bool operator!=( const FVector2& right ) const  {
			return !operator==( right );
		}

		//! returns inverse FVector2 -x,-y
		FVector2 operator-() const  {
			return FVector2( -x, -y );
		}

		//! Returns a pixel aligned copy of this FVector2
		FVector2 pixelAligned( const IVector2& resolution ) const {
			FVector2 tmpF;
			IVector2 tmpI(( int )( x *( float )resolution.x ), ( int )( y *( float )resolution.y ) );
			tmpF.x = (( float )tmpI.x ) / ( float )resolution.x;
			tmpF.y = (( float )tmpI.y ) / ( float )resolution.y;
			return tmpF;
		}
		//! Returns the length of vector
		float length() {
			return sqrt(( x*x ) + ( y*y ) );
		}
		//! Return a string representation of this value
		std::string toStr() const {
			std::stringstream ss;
			ss << "( " << x << " x " << y << " )" ;
			return ss.str();
		}
		float x; //!< direct access to x
		float y; //!< direct access to y
	};

	//! FRects are rects built from float values. Internally they are comprised of two FVector2's.
	class OPENGUI_API FRect {
	public:
		//! constructor
		FRect() {}
		//! constructor
		FRect( const FVector2& min, const FVector2 max ): min( min ), max( max ) {}
		//! constructor
		FRect( const float& left, const float& top, const float& right, const float& bottom ) {
			min.y = top;
			min.x = left;
			max.x = right;
			max.y = bottom;
		}
		~FRect() {}

		//! return position
		const FVector2& getPosition() const {
			return min;
		}
		//! return size
		FVector2 getSize() const {
			return max - min;
		}
		//! return width
		float getWidth() const {
			return max.x - min.x;
		}
		//! return height
		float getHeight() const {
			return max.y - min.y;
		}

		//! set new width
		void setWidth( const float& newWidth ) {
			max.x = min.x + newWidth;
		}
		//! set new height
		void setHeight( const float& newHeight ) {
			max.y = min.y + newHeight;
		}
		//! set new size
		void setSize( const FVector2& newSize ) {
			max = min + newSize;
		}
		//! set new position
		void setPosition( const FVector2& newPosition ) {
			FVector2 tmpSize = max - min;
			min = newPosition;
			max = min + tmpSize;
		}
		//! offset position by \c offsetVector
		void offset( const FVector2& offsetVector ) {
			min = min + offsetVector;
			max = max + offsetVector;
		}
		//! Normalizes the rect, ensuring that min really is the min and max really is the max
		FRect& normalize() {
			float tmp;
			if ( min.x > max.x ) {
				tmp = min.x;
				min.x = max.x;
				max.x = tmp;
			}
			if ( min.y > max.y ) {
				tmp = min.y;
				min.y = max.y;
				max.y = tmp;
			}
			return ( *this );
		}
		//! return true if given point is within bounds of this rect
		bool isInside( const FVector2& point ) {
			if (	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y )
				return true;
			return false;
		}
		//! Return the given outer coord as an inner coord
		/*! inner coord is defined as upper left = 0,0, lower right = 1.0f,1.0f */
		FVector2 getInnerCoord( const FVector2& outerFVector2 ) {
			return FVector2(
					   ( outerFVector2.x - min.x ) / getWidth(),
					   ( outerFVector2.y - min.y ) / getHeight()
				   );
		}
		//! Return the given inner coord as an outer coord
		/*! inner coord is defined as upper left = 0,0, lower right = 1.0f,1.0f */
		FVector2 getOuterCoord( const FVector2& innerFVector2 ) {
			return FVector2(
					   (( innerFVector2.x*getWidth() ) + min.x ),
					   (( innerFVector2.y*getHeight() ) + min.y )
				   );

		}
		//! Returns a pixel aligned copy of this FRect
		FRect pixelAligned( const IVector2& resolution ) const {
			return FRect( min.pixelAligned( resolution ), max.pixelAligned( resolution ) );
		}
		//! Return a string representation of this value
		std::string toStr() const {
			std::stringstream ss;
			ss << "{ " << min.toStr() << " X " << max.toStr() << " }" ;
			return ss.str();
		}
		//! comparison operator
		bool operator==( const FRect& right ) const  {
			return min == right.min && max == right.max;
		}
		//! comparison operator
		bool operator!=( const FRect& right ) const  {
			return !operator==( right );
		}
		FVector2 min; //!< direct access to upper left point
		FVector2 max; //!< direct access to lower right point
	};

	/*! \brief
	This type is used throughout %OpenGUI to represent the 4 horizontal
	alignment types (Left,Center,Right,Justified)
	*/
	class TextAlignment {
	public:
		//! Enum definition for representing alignment style
		enum Alignment {
			ALIGN_LEFT = 0, //!< Aligns text to left of widget
			ALIGN_TOP = 0, //!< Aligns text to top of widget
			ALIGN_RIGHT = 1, //!< Aligns text to right of widget
			ALIGN_BOTTOM = 1, //!< Aligns text to bottom of widget
			ALIGN_CENTER = 2, //!< Aligns text to the center of the widget. (This is valid for both horizontal and vertical alignments.)
			/*! \brief Evenly distributes text spacing to completely fill widget
			in the direction used. (This is valid for both horizontal and vertical alignments.)
			TextLabel applies a minimum span that must be met before this is applied to a line of text. This
			prevents short lines of text from being spaced unreasonable distances.
			*/
			ALIGN_JUSTIFIED = 3
		};

		TextAlignment& operator=( const Alignment& rhs ) {
			value = rhs;
			return *this;
		}

		bool operator==( const Alignment& rhs ) {
			return value == rhs;
		}
		bool operator==( const TextAlignment& rhs ) {
			return value == rhs.value;
		}
		Alignment value;

		//a few little methods to handle various casts and assignments
		operator Alignment&() {
			return value;
		}
		TextAlignment( const Alignment& rhs ) {
			value = rhs;
		}
		//! Default constructor initializes as ALIGN_LEFT/ALIGN_TOP depending on usage context. (They have same value)
		TextAlignment(): value( ALIGN_LEFT ) {} //default constructor
	};

	//! Used throughout %OpenGUI to define colors.
	/*! Supports an alpha channel. The default color is White, with alpha = 1.0f */
	class OPENGUI_API Color {
	public:
		//! Constructor with optional in place initialization
		Color( float R = 1.0f, float G = 1.0f, float B = 1.0f, float A = 1.0f ) : Red( R ), Blue( B ), Green( G ), Alpha( A ) {}

		float Red;//!<Red Channel
		float Green;//!<Green Channel
		float Blue;//!<Blue Channel
		float Alpha;//!<Alpha Channel

		//! Quickly generate a preset Color that is Red
		static Color PresetRed() {
			return Color( 1.0f, 0.0f, 0.0f, 1.0f );
		}
		//! Quickly generate a preset Color that is Green
		static Color PresetGreen() {
			return Color( 0.0f, 1.0f, 0.0f, 1.0f );
		}
		//! Quickly generate a preset Color that is Blue
		static Color PresetBlue() {
			return Color( 0.0f, 0.0f, 1.0f, 1.0f );
		}
		//! Quickly generate a preset Color that is White
		static Color PresetWhite() {
			return Color( 1.0f, 1.0f, 1.0f, 1.0f );
		}
		//! Quickly generate a preset Color that is Black
		static Color PresetBlack() {
			return Color( 0.0f, 0.0f, 0.0f, 1.0f );
		}
		//! Clamps the color channels between 0.0f and 1.0f
		void clamp() {
			if ( Red < 0.0f ) Red = 0.0f;
			if ( Red > 1.0f ) Red = 1.0f;
			if ( Green < 0.0f ) Green = 0.0f;
			if ( Green > 1.0f ) Green = 1.0f;
			if ( Blue < 0.0f ) Blue = 0.0f;
			if ( Blue > 1.0f ) Blue = 1.0f;
			if ( Alpha < 0.0f ) Alpha = 0.0f;
			if ( Alpha > 1.0f ) Alpha = 1.0f;
		}
		//! Normalizes the color channels by scaling the channel ranges to fall within 0.0f and 1.0f
		/*! If all channels have an equal value, the result will be the identity Color (all channels == 1.0f) */
		void normalize() {
			float min = 0.0f, max;
			min = Red;
			if ( Green < min ) min = Green;
			if ( Blue < min ) min = Blue;
			if ( Alpha < min ) min = Alpha;
			Red -= min;
			Green -= min;
			Blue -= min;
			Alpha -= min;

			max = Red;
			if ( Green > max ) max = Green;
			if ( Blue > max ) max = Blue;
			if ( Alpha > max ) max = Alpha;
			Red /= max;
			Green /= max;
			Blue /= max;
			Alpha /= max;
			clamp(); //we need to clamp in case we just performed a divide by zero
		}
		//! comparison operator
		bool operator==( const Color& right ) const  {
			return ( Red == right.Red
					 && Green == right.Green
					 && Blue == right.Blue
					 && Alpha == right.Alpha );
		}
		//! comparison operator
		bool operator!=( const Color& right ) const  {
			return !operator==( right );
		}
	};



	//! A string based Enum system
	/*! It's often necessary to provide a generic enum that can be created pragmatically.
	This class addresses that need. All values are stored and retrieved in lower case form.
	*/
	class OPENGUI_API Enum {
	public:
		//! Set of acceptable string ENUM values.
		typedef std::set<std::string> EnumList;
		//! constructor
		Enum();
		//! destructor
		virtual ~Enum();

		//! Adds the given string to the Enum's list of possible values
		/*! If this is the first item being added to the enum, it is automatically selected. */
		void addValue( std::string value );
		//! Sets the currently selected value
		void setValue( std::string value );
		//! Sets the currently selected value using a C-String
		void setValue( const char* value );
		//! Retrieves the currently selected value
		std::string getValue();
		//! Returns true if the given \c value is a valid selection for this Enum
		bool testValue( std::string value ) const;
		//! Returns the complete list of possible values
		EnumList getList() const {
			return mEnumList;
		}

		//! comparison operator
		bool operator==( const Enum& right ) const  {
			if ( 0 != mSelected.compare( right.mSelected ) )
				return false;
			return true;
		}
		//! comparison operator
		bool operator!=( const Enum& right ) const  {
			return !operator==( right );
		}
	private:
		EnumList mEnumList;
		std::string mSelected;
	};

	//! \internal base class for TextAlignment based Enums
	/*! This is just a functionality providing base class. You are most likely looking
	for Enum_TextAligntment_H or Enum_TextAligntment_V.
	*/
	class OPENGUI_API Enum_TextAligntment_base : public Enum {
	public:
		//! Set the value by TextAligntment
		void setValue( TextAlignment alignmentObj );
		//! Set the value by TextAligntment::Alignment
		virtual void setValue( TextAlignment::Alignment alignment ) = 0;
		//! Return the current value as a TextAligntment
		TextAlignment getTextAlignment();
	};

	//! Enum specialized for use in horizontal text alignments
	class OPENGUI_API Enum_TextAligntment_H : public Enum_TextAligntment_base {
	public:
		Enum_TextAligntment_H();
		virtual ~Enum_TextAligntment_H() {}
		virtual void setValue( TextAlignment::Alignment alignment );
	};

	//! Enum specialized for use in vertical text alignments
	class OPENGUI_API Enum_TextAligntment_V : public Enum_TextAligntment_base {
	public:
		Enum_TextAligntment_V();
		virtual ~Enum_TextAligntment_V() {}
		virtual void setValue( TextAlignment::Alignment alignment );
	};

	/*! @} */ //end of Types group

}//namespace OpenGUI {

#endif

