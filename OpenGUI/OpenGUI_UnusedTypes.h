

//! \internal UNUSED The UDim is the base unit of measure for everything, it allows simultaneous representation of both relative and absolute measure.
/*!
	As the base of all measurements, the default value for a UDim is 0,0. This means
	all objects built from UDims will always start with an initialized value of some sort.
*/
class OPENGUI_API UDim {
public:
	UDim(): scale( 0 ), offset( 0 ) {}
	UDim( const float scale, const int offset ) : scale( scale ), offset( offset ) {}
	~UDim() {}

	UDim operator+( const UDim& right ) const  {
		return UDim( scale + right.scale, offset + right.offset );
	}
	UDim operator-( const UDim& right ) const  {
		return UDim( scale - right.scale, offset - right.offset );
	}
	UDim operator*( const UDim& right ) const  {
		return UDim( scale * right.scale, offset * right.offset );
	}
	UDim operator/( const UDim& right ) const  {
		return UDim( scale / right.scale, offset / right.offset );
	}
	UDim operator*( const float& right ) const  {
		return UDim( scale * right, offset );
	}
	UDim operator/( const float& right ) const  {
		return UDim( scale / right, offset );
	}

	bool operator==( const UDim& right ) const {
		return scale == right.scale && offset == right.offset;
	}
	bool operator!=( const UDim& right ) const {
		return !operator==( right );
	}

	//! \internal UNUSED  Evaluates this UDim against a given scalelimit and returns the resulting float and int values in a UDim
	/*!
		Both halfs of the input represent the same concept, only using different metrics. Both
		the scale and the offset of the input are interpretted as the maximum scale along the axis.
		The returned UDim is the value of the current UDim when placed within the given scalelimit,
		having both its scale and offset combined. So as a UDim's value increases toward the scalelimit,
		it's value becomes closer to 1.0 in scale, and scalelimit.offset in offset.\n
		The value is determined as such:\n
		((scalelimit.scale/scalelimit.offset)*offset) + <b> This is the offset value </b> \n
		(scale/scalelimit.scale) <b>This is the scale value as scaled by the scalelimit.scale</b>\n\n
		
		Basically, you provide the size of the area that this UDim is supposed to be working within,
		using both a float and int representation, and this function will tell you where this UDim
		lies within that area, and it will return those results using both float and int.
	*/
	UDim freeze( const UDim& scalelimit ) {
		UDim ret;
		ret.scale = scale / scalelimit.scale;
		if ( scalelimit.offset != 0 )
			ret.scale += (( scalelimit.scale / ( float )scalelimit.offset ) * offset );
		ret.offset = ( int )(( ret.scale / scalelimit.scale ) * scalelimit.offset );
		return ret;
	}

	//! Return a string representation of this value
	std::string toStr() {
		std::stringstream ss;
		ss << "[" << scale << "+" << offset << "]";
		return ss.str();
	}

	float scale;
	int offset;
};


//! \internal UNUSED The UVector2 is a 2 dimensional vector that is built from two UDim objects
class OPENGUI_API UVector2 {
public:
	UVector2() {}
	UVector2( const UDim& x, const UDim& y ) : x( x ), y( y ) {}
	UVector2( const float& xscale, const int& xoffset, const float& yscale, const int& yoffset ) : x( UDim( xscale, xoffset ) ), y( UDim( yscale, yoffset ) ) {}
	~UVector2() {}

	UVector2 operator+( const UVector2& right ) const  {
		return UVector2( x + right.x, y + right.y );
	}
	UVector2 operator-( const UVector2& right ) const  {
		return UVector2( x - right.x, y - right.y );
	}
	UVector2 operator*( const UVector2& right ) const  {
		return UVector2( x * right.x, y * right.y );
	}
	UVector2 operator/( const UVector2& right ) const  {
		return UVector2( x / right.x, y / right.y );
	}
	UVector2 operator*( const FVector2& right ) const  {
		return UVector2( x / right.x, y / right.y );
	}
	UVector2 operator/( const FVector2& right ) const  {
		return UVector2( x / right.x, y / right.y );
	}

	bool operator==( const UVector2& right ) const  {
		return x == right.x && y == right.y;
	}
	bool operator!=( const UVector2& right ) const  {
		return !operator==( right );
	}

	//! Freezes this UVector2 using a given UVector2 of scalelimits and returns the resulting UVector2. \see UDim::freeze()
	UVector2 freeze( const UVector2& scale ) {
		return UVector2( x.freeze( scale.x ), y.freeze( scale.y ) );
	}

	//! Return a string representation of this value
	std::string toStr() {
		std::stringstream ss;
		ss << "( " << x.toStr() << " x " << y.toStr() << " )" ;
		return ss.str();
	}

	UDim x;
	UDim y;
};

//! \internal UNUSED The URect is a rect built from UVector2 objects.
class OPENGUI_API URect {
public:
	URect() {}
	URect( const UVector2& min, const UVector2 max ): min( min ), max( max ) {}
	URect( const UDim& top, const UDim& left, const UDim& bottom, const UDim& right ) {
		min.y = top;
		min.x = left;
		max.x = right;
		max.y = bottom;
	}
	~URect() {}

	const UVector2& getPosition() const {
		return min;
	}
	UVector2 getSize() const {
		return max - min;
	}
	UDim getWidth() const {
		return max.x - min.x;
	}
	UDim getHeight() const {
		return max.y - min.y;
	}

	void setWidth( const UDim& newWidth ) {
		max.x = min.x + newWidth;
	}
	void setHeight( const UDim& newHeight ) {
		max.y = min.y + newHeight;
	}
	void setSize( const UVector2& newSize ) {
		max = min + newSize;
	}
	void setPosition( const UVector2& newPosition ) {
		UVector2 tmpSize = max - min;
		min = newPosition;
		max = min + tmpSize;
	}

	void offset( const UVector2& offsetVector ) {
		min = min + offsetVector;
		max = max + offsetVector;
	}

	//! Evaluates this URect against a given UVector2 scale and returns the resulting URect \see UVector2::freeze() and UDim::freeze()
	URect freeze( const UVector2& scale ) {
		return URect( min.freeze( scale ), max.freeze( scale ) );
	}

	//! Return a string representation of this value
	std::string toStr() {
		std::stringstream ss;
		ss << "{ " << min.toStr() << " X " << max.toStr() << " }" ;
		return ss.str();
	}

	UVector2 min, max;
};