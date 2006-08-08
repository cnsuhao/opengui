#ifndef CCFEE719_8FDE_46ce_8F52_350F92CA56CD
#define CCFEE719_8FDE_46ce_8F52_350F92CA56CD

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI{
//No thanks Bill
#undef min
#undef max

	//! IVector2s are two dimensional vectors based on integers.
	class OPENGUI_API IVector2
	{
	public:
		//! constructor
		IVector2() : x(0), y(0) {}
		//! constructor
		IVector2( int x, int y) : x(x), y(y) {}
		//! operator +
		IVector2 operator+(const IVector2& right) const  { return IVector2(x + right.x, y + right.y); }
		//! operator -
		IVector2 operator-(const IVector2& right) const  { return IVector2(x - right.x, y - right.y); }
		//! operator *
		IVector2 operator*(const IVector2& right) const  { return IVector2(x * right.x, y * right.y); }
		//! operator /
		IVector2 operator/(const IVector2& right) const  { return IVector2(x / right.x, y / right.y); }

		//! comparison operator
		bool operator==(const IVector2& right) const  { return x==right.x && y == right.y; }
		//! comparison operator
		bool operator!=(const IVector2& right) const  { return !operator==(right); }
		//! Return a string representation of this value
		std::string toStr() const
			{
				std::stringstream ss;
				ss << "( " << x << " x " << y <<" )" ;
				return ss.str();
			}
		int x; //!< direct access to x
		int y; //!< direct access to y
	};

	//! IRects are rects built from int values. Internally they are comprised of two IVector2's.
	class OPENGUI_API IRect
	{
	public:
		//! constructor
		IRect() {}
		//! constructor
		IRect(const IVector2& min, const IVector2 max):min(min),max(max) {}
		//! constructor
		IRect(const int& left, const int& top, const int& right, const int& bottom)
			{
				min.y = top;
				min.x = left;
				max.x = right;
				max.y = bottom;
			}
		~IRect() {}

		//!returns top,left
		const IVector2& getPosition() const { return min; }
		//! return size as IVector2
		IVector2 getSize() const { return max - min; }
		//! return width
		int getWidth() const { return max.x - min.x; }
		//! return height
		int getHeight() const { return max.y - min.y; }
		//! return total area
		int getArea() const { return getWidth() * getHeight(); }
		//! sets new width
		void setWidth(const int& newWidth) { max.x = min.x + newWidth; }
		//! sets new height
		void setHeight(const int& newHeight) { max.y = min.y + newHeight; }
		//! sets new size
		void setSize(const IVector2& newSize) { max = min + newSize; }
		//! sets new position
		void setPosition(const IVector2& newPosition)
			{
				IVector2 tmpSize = max - min;
				min = newPosition;
				max = min + tmpSize;
			}

		//! offset position by given IVector2
		void offset(const IVector2& offsetVector)
			{
				min = min + offsetVector;
				max = max + offsetVector;
			}
		//! return true if given point is inside this IRect
		bool inside(IVector2 point)
			{
				if(	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y)
					return true;
				return false;
			}
		//! Return a string representation of this value
		std::string toStr() const
			{
				std::stringstream ss;
				ss << "{ " << min.toStr() << " X " << max.toStr() <<" }" ;
				return ss.str();
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
	class OPENGUI_API FVector2
	{
	public:
		//! constructor
		FVector2() : x(0), y(0) {}
		//! constructor
		FVector2( float x, float y) : x(x), y(y) {}
		//! operator +
		FVector2 operator+(const FVector2& right) const  { return FVector2(x + right.x, y + right.y); }
		//! operator -
		FVector2 operator-(const FVector2& right) const  { return FVector2(x - right.x, y - right.y); }
		//! operator *
		FVector2 operator*(const FVector2& right) const  { return FVector2(x * right.x, y * right.y); }
		//! operator /
		FVector2 operator/(const FVector2& right) const  { return FVector2(x / right.x, y / right.y); }

		//! comparison operator
		bool operator==(const FVector2& right) const  { return x==right.x && y == right.y; }
		//! comparison operator
		bool operator!=(const FVector2& right) const  { return !operator==(right); }

		//! returns inverse FVector2 -x,-y
		FVector2 operator-() const  { return FVector2(-x,-y); }
		
		//! Returns a pixel aligned copy of this FVector2
		FVector2 pixelAligned(const IVector2& resolution) const
			{
				FVector2 tmpF;
				IVector2 tmpI((int)(x * (float)resolution.x),(int)(y * (float)resolution.y));
				tmpF.x = ((float)tmpI.x) / (float)resolution.x;
				tmpF.y = ((float)tmpI.y) / (float)resolution.y;
				return tmpF;
			}
		//! Returns the length of vector
		float length()
			{
				return sqrt((x*x) + (y*y));
			}
		//! Return a string representation of this value
		std::string toStr() const
			{
				std::stringstream ss;
				ss << "( " << x << " x " << y <<" )" ;
				return ss.str();
			}
		float x; //!< direct access to x
		float y; //!< direct access to y
	};

	//! FRects are rects built from float values. Internally they are comprised of two FVector2's.
	class OPENGUI_API FRect
	{
	public:
		//! constructor
		FRect() {}
		//! constructor
		FRect(const FVector2& min, const FVector2 max):min(min),max(max) {}
		//! constructor
		FRect(const float& left, const float& top, const float& right, const float& bottom)
			{
				min.y = top;
				min.x = left;
				max.x = right;
				max.y = bottom;
			}
		~FRect() {}

		//! return position
		const FVector2& getPosition() const { return min; }
		//! return size
		FVector2 getSize() const { return max - min; }
		//! return width
		float getWidth() const { return max.x - min.x; }
		//! return height
		float getHeight() const { return max.y - min.y; }

		//! set new width
		void setWidth(const float& newWidth) { max.x = min.x + newWidth; }
		//! set new height
		void setHeight(const float& newHeight) { max.y = min.y + newHeight; }
		//! set new size
		void setSize(const FVector2& newSize) { max = min + newSize; }
		//! set new position
		void setPosition(const FVector2& newPosition)
			{
				FVector2 tmpSize = max - min;
				min = newPosition;
				max = min + tmpSize;
			}
		//! offset position by \c offsetVector
		void offset(const FVector2& offsetVector)
			{
				min = min + offsetVector;
				max = max + offsetVector;
			}
		//! Normalizes the rect, ensuring that min really is the min and max really is the max
		FRect& normalize()
			{
				float tmp;
				if(min.x > max.x){tmp=min.x; min.x=max.x; max.x=tmp;}
				if(min.y > max.y){tmp=min.y; min.y=max.y; max.y=tmp;}
				return (*this);
			}
		//! return true if given point is within bounds of this rect
		bool isInside(const FVector2& point)
			{
				if(	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y)
					return true;
				return false;
			}
		//! Return the given outer coord as an inner coord
		/*! inner coord is defined as upper left = 0,0, lower right = 1.0f,1.0f */
		FVector2 getInnerCoord(const FVector2& outerFVector2)
			{
				return FVector2(
					(outerFVector2.x - min.x)/getWidth(),
					(outerFVector2.y - min.y)/getHeight()
				);
			}
		//! Return the given inner coord as an outer coord
		/*! inner coord is defined as upper left = 0,0, lower right = 1.0f,1.0f */
		FVector2 getOuterCoord(const FVector2& innerFVector2)
			{
				return FVector2(
					((innerFVector2.x*getWidth()) + min.x),
					((innerFVector2.y*getHeight()) + min.y)
				);
				
			}
		//! Returns a pixel aligned copy of this FRect
		FRect pixelAligned(const IVector2& resolution) const
			{
				return FRect(min.pixelAligned(resolution),max.pixelAligned(resolution));
			}
		//! Return a string representation of this value
		std::string toStr() const
			{
				std::stringstream ss;
				ss << "{ " << min.toStr() << " X " << max.toStr() <<" }" ;
				return ss.str();
			}
		FVector2 min; //!< direct access to upper left point
		FVector2 max; //!< direct access to lower right point
	};

	/*! \brief
		This type is used throughout %OpenGUI to represent the 4 horizontal
		alignment types (Left,Center,Right,Justified) and the
	*/
	class TextAlignment{
	public:
		typedef enum {
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
		}Alignment;
		TextAlignment& operator=(const Alignment& rhs)
			{value = rhs; return *this;}
		
		bool operator==(const Alignment& rhs)
			{return value == rhs;}
		bool operator==(const TextAlignment& rhs)
			{return value == rhs.value;}
		Alignment value;

		//a few little methods to handle various casts and assignments
		operator Alignment&(){return value;}
		TextAlignment(const Alignment& rhs){value=rhs;}
		//! Default constructor initializes as ALIGN_LEFT/ALIGN_TOP depending on usage context. (They have same value)
		TextAlignment():value(ALIGN_LEFT){} //default constructor
	};

	
};

#endif

