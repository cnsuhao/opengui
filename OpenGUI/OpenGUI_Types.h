#ifndef CCFEE719_8FDE_46ce_8F52_350F92CA56CD
#define CCFEE719_8FDE_46ce_8F52_350F92CA56CD
#include <cmath>
#include <string>
#include <sstream>
#include "OpenGUI_Exports.h"

namespace OpenGUI{
//No thanks Bill
#undef min
#undef max

	//! Most users are probably looking for UVector2. IVector2s are only used briefly by the imagery system when working with pixel based texture locations.
	class OPENGUI_API IVector2
	{
	public:
		IVector2() : x(0), y(0) {}
		IVector2( int x, int y) : x(x), y(y) {}
		IVector2 operator+(const IVector2& right) const  { return IVector2(x + right.x, y + right.y); }
		IVector2 operator-(const IVector2& right) const  { return IVector2(x - right.x, y - right.y); }
		IVector2 operator*(const IVector2& right) const  { return IVector2(x * right.x, y * right.y); }
		IVector2 operator/(const IVector2& right) const  { return IVector2(x / right.x, y / right.y); }

		bool operator==(const IVector2& right) const  { return x==right.x && y == right.y; }
		bool operator!=(const IVector2& right) const  { return !operator==(right); }
		//! Return a string representation of this value
		std::string toStr() const
			{
				std::stringstream ss;
				ss << "( " << x << " x " << y <<" )" ;
				return ss.str();
			}
		int x;
		int y;
	};

	/*! Most users are probably looking for URect. IRects are rects built from IDim values, 
		and are only useful for defining pixel based areas within image files.
	*/
	class OPENGUI_API IRect
	{
	public:
		IRect() {}
		IRect(const IVector2& min, const IVector2 max):min(min),max(max) {}
		IRect(const int& left, const int& top, const int& right, const int& bottom)
			{
				min.y = top;
				min.x = left;
				max.x = right;
				max.y = bottom;
			}
		~IRect() {}

		const IVector2& getPosition() const { return min; }
		IVector2 getSize() const { return max - min; }
		int getWidth() const { return max.x - min.x; }
		int getHeight() const { return max.y - min.y; }

		void setWidth(const int& newWidth) { max.x = min.x + newWidth; }
		void setHeight(const int& newHeight) { max.y = min.y + newHeight; }
		void setSize(const IVector2& newSize) { max = min + newSize; }
		void setPosition(const IVector2& newPosition)
			{
				IVector2 tmpSize = max - min;
				min = newPosition;
				max = min + tmpSize;
			}

		void offset(const IVector2& offsetVector)
			{
				min = min + offsetVector;
				max = max + offsetVector;
			}
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
		IVector2 min;
		IVector2 max;
	};


	//! Most users are probably looking for UVector2. The FVector2 is the unit of measure used in the final rendering stages OpenGUI.
	/*!
		This object often represents a screen coordinate starting from the upper left corner of the screen.
		Unlike UVector2, the value a FVector2 represents is very much an issue of context.
		In the rendering areas of OpenGUI, a FVector2 is quite often a representation of screen position between 0,0 (upper left) and 1,1 (lower right).
		In the internal code, it can also represent a scaling factor for both axis at once, which is used to convert a UVector2
		to a screen position FVector2 so that it can be used in the final rendering stages.
	*/
	class OPENGUI_API FVector2
	{
	public:
		FVector2() : x(0), y(0) {}
		FVector2( float x, float y) : x(x), y(y) {}
		FVector2 operator+(const FVector2& right) const  { return FVector2(x + right.x, y + right.y); }
		FVector2 operator-(const FVector2& right) const  { return FVector2(x - right.x, y - right.y); }
		FVector2 operator*(const FVector2& right) const  { return FVector2(x * right.x, y * right.y); }
		FVector2 operator/(const FVector2& right) const  { return FVector2(x / right.x, y / right.y); }

		bool operator==(const FVector2& right) const  { return x==right.x && y == right.y; }
		bool operator!=(const FVector2& right) const  { return !operator==(right); }
		//! This function takes the FVector2 with values between 0,0 and 1,1 and aligns it's value to the nearest pixel, as defined by resolution.
		FVector2 pixelAligned(const IVector2& resolution)
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
		float x;
		float y;
	};

	class OPENGUI_API FRect
	{
	public:
		FRect() {}
		FRect(const FVector2& min, const FVector2 max):min(min),max(max) {}
		FRect(const float& left, const float& top, const float& right, const float& bottom)
			{
				min.y = top;
				min.x = left;
				max.x = right;
				max.y = bottom;
			}
		~FRect() {}

		const FVector2& getPosition() const { return min; }
		FVector2 getSize() const { return max - min; }
		float getWidth() const { return max.x - min.x; }
		float getHeight() const { return max.y - min.y; }

		void setWidth(const float& newWidth) { max.x = min.x + newWidth; }
		void setHeight(const float& newHeight) { max.y = min.y + newHeight; }
		void setSize(const FVector2& newSize) { max = min + newSize; }
		void setPosition(const FVector2& newPosition)
			{
				FVector2 tmpSize = max - min;
				min = newPosition;
				max = min + tmpSize;
			}

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
		bool isInside(const FVector2& point)
			{
				if(	point.x >= min.x && point.x < max.x &&
					point.y >= min.y && point.y < max.y)
					return true;
				return false;
			}
		//! Return the given outer coord as an inner coord
		FVector2 getInnerCoord(const FVector2& outerFVector2)
			{
				return FVector2(
					(outerFVector2.x - min.x)/getWidth(),
					(outerFVector2.y - min.y)/getHeight()
				);
			}
		//! Return the given inner coord as an outer coord
		FVector2 getOuterCoord(const FVector2& innerFVector2)
			{
				return FVector2(
					((innerFVector2.x*getWidth()) + min.x),
					((innerFVector2.y*getHeight()) + min.y)
				);
				
			}
		FRect pixelAligned(const IVector2& resolution)
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
		FVector2 min;
		FVector2 max;
	};



	
};

#endif