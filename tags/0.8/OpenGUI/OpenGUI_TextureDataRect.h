// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef EA979D9D_03C6_49eb_BF38_D74FE70AB976
#define EA979D9D_03C6_49eb_BF38_D74FE70AB976

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {

	class TextureData;	//forward declaration

	//! Used to represent colors for a few functions within TextureDataRect
	class OPENGUI_API TDRColor {
	public:
		//! Default constructor provides pure white, 100% alpha.
		TDRColor()
				: Red( 255 ), Green( 255 ), Blue( 255 ), Alpha( 255 ) {}
		//! Custom constructor allows for definition of each color element. Alpha is optional and defaults to 100%.
		TDRColor( unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255 )
				: Red( red ), Green( green ), Blue( blue ), Alpha( alpha ) {}

		unsigned char Red; //!< red channel
		unsigned char Green; //!< green channel
		unsigned char Blue; //!< blue channel
		unsigned char Alpha; //!< alpha channel
	};

	//! Provides a clean and reliable method of altering the contents of a TextureData object.
	/*!
		These objects represent a subset of data from a TextureData object. The immediate contents
		of the image data contained is not directly linked to the data of a TextureData object. When
		a TextureDataRect is created, they can be created with a provided background color but otherwise
		empty, or they can be initialized with existing data from a TextureData object. Either way, making
		changes to the contents of a TextureDataRect does not immediately update the contents of any
		TextureData object. The TextureDataRect must be applied to a TextureData object using the
		\c paste() function. (It is entirely valid to create a TextureDataRect of size 0,0.)

		\note All offsets and rects use the upper left of the image as 0,0 and the bottom right as sX,sY
			where sX is the width of the image, and sY is the height of the image.

		\remarks The overall functionality of TextureDataRect is limited on purpose. If you require more
			complex image editing operations, it is highly recommended that you utilize a full blown image
			library, such as DevIL.

		\warning TextureDataRect only supports one color mode: 4 channel, 32-bit, RGBA. All copies and
			pastes between non-RGBA TextureData objects are subject to a very crude form of data conversion.
			Color channels that do not fit into \c paste() destinations are dropped without error or warning,
			and color channels that are missing in \c copy() sources are autofilled with 0. If this doesn't
			fit your needs, see the above remarks.
	*/
	class OPENGUI_API TextureDataRect {
	public:
		//! create a blank slate of the given size and color
		TextureDataRect( const IVector2& size = IVector2(), const TDRColor& color = TDRColor() );
		//! create using an existing TextureData as the source of data. \c srcRect defines the sub area with it to use, as well as size
		TextureDataRect( const TextureData* srcTextureData, const IRect& srcRect );
		//! create using an existing TextureDataRect as the source of data. \c srcRect defines the sub area with it to use, as well as size
		TextureDataRect( const TextureDataRect* srcTextureDataRect, const IRect& srcRect );

		~TextureDataRect();//!< destructor

		//! Returns the width and height of the texture data rect
		IVector2 getSize();
		//! Sets the size of this object to the given size.
		/*! Existing data that fits within the new size is preserved but will be cropped as appropriate.
			Any new real estate will be filled with the provided color, or white w/ 100% alpha if none is
			provided.

			\note It is impossible to have a negative value for either dimension, so any negative dimensions
				are automatically changed to a 0. If either dimension is 0, the other is automatically set
				to 0 as well.
		*/
		void setSize( const IVector2& newSize, const TDRColor& color = TDRColor() );
		//! Fills this TextureDataRect with the given color, overwriting any existing data.
		void fill( const TDRColor& color = TDRColor() );

		//! Copies the contents of an existing TextureData into the buffer of this object.
		/*!
			\param srcTextureData The TextureData object that is used as the data source.
			\param srcRect The rect within the source that is to be copied.
			\note This TextureDataRect will be automatically resized to perfectly hold the
				copied data. If you are attempting to copy the data to an offset position,
				use a temporary TextureDataRect to \c copy() the data out, and \c paste() it
				into the desired TextureDataRect at the desired position. Any data that is
				already held by this object will be properly discarded before the copy occurs.
			\warning If you attempt to copy off the end of a data source on either axis by
				specifying an invalid \c srcRect, the area copied will be adjusted in size
				to fit the available area of the data source. This means it is possible to
				end up copying a rect of 0 height and 0 width. (If either height or width
				are adjusted to a size of 0, the other is automatically set to 0 as well and
				the copy will immediately return without performing any copy at all. The
				previous contents of this object are still discarded.)
		*/
		void copy( const TextureData* srcTextureData, IRect srcRect );
		//! Copies the contents of an existing TextureDataRect into the buffer of this object.
		/*!
			\param srcTextureDataRect The TextureDataRect object that is used as the data source.
			\param srcRect The rect within the source that is to be copied.
			\note This TextureDataRect will be automatically resized to perfectly hold the
				copied data. If you are attempting to copy the data to an offset position,
				use a temporary TextureDataRect to \c copy() the data out, and \c paste() it
				into the desired TextureDataRect at the desired position. Any data that is
				already held by this object will be properly discarded before the copy occurs.
			\warning If you attempt to copy off the end of a data source on either axis by
				specifying an invalid \c srcRect, the area copied will be adjusted in size
				to fit the available area of the data source. This means it is possible to
				end up copying a rect of 0 height and 0 width. (If either height or width
				are adjusted to a size of 0, the other is automatically set to 0 as well and
				the copy will immediately return without performing any copy at all. The
				previous contents of this object are still discarded.)
		*/
		void copy( const TextureDataRect* srcTextureDataRect, IRect srcRect );
		//! Writes the contents of this object's buffer onto a TextureData at the desired offset.
		/*!
			\param dstTextureData The TextureData object that is the destination for writing.
			\param dstOffset The position within the destination to begin the paste.

			\note The \c paste operation, like the \c copy operation, respects logical image
				dimensions. This means that if part of your paste does not fit within the
				destination, the part that does not fit will not be written, and no error
				will ever be thrown for it. The destination will \b not be resized to make
				it fit.
		*/
		void paste( TextureData* dstTextureData, const IVector2& dstOffset ) const;
		//! Writes the contents of this object's buffer onto a TextureDataRect at the desired offset.
		/*!
			\param dstTextureDataRect The TextureDataRect object that is the destination for writing.
			\param dstOffset The position within the destination to begin the paste.

			\note The \c paste operation, like the \c copy operation, respects logical image
				dimensions. This means that if part of your paste does not fit within the
				destination, the part that does not fit will not be written, and no error
				will ever be thrown for it. The destination will \b not be resized to make
				it fit.
		*/
		void paste( TextureDataRect* dstTextureDataRect, const IVector2& dstOffset ) const;

		//! Provides pixel write functionality.
		/*! This function respects logical image dimensions. Writes outside of the image area
			will do nothing.
		*/
		inline void write( const IVector2& position, const TDRColor& color ) {
			//only allow writes within the available data range
			if ( position.x < 0 || position.y < 0 ||
					position.x >= mSize.x || position.y >= mSize.y )
				return;
			mData[( mSize.x * position.y ) + position.x ] = color;
		}

		//! Provides pixel read functionality.
		/*! This function respects logical image dimensions. Reads outside of the image area
			will return pure white w/ 100% alpha.
		*/
		inline TDRColor read( const IVector2& position ) const {
			//only allow reads within the available data range
			if ( position.x < 0 || position.y < 0 ||
					position.x >= mSize.x || position.y >= mSize.y )
				return TDRColor();
			return mData[( mSize.x * position.y ) + position.x ];
		}
	private:
		TDRColor* mData;
		IVector2 mSize;
		//! \internal Deletes any existing mData, and resets the mSize to (0,0)
		void _reset();
		//! \internal Allocates a new buffer to hold an image of the given size. Calls \c _reset() first.
		void _buildBuffer( const IVector2& size );
	};

}
;//namespace OpenGUI{
//OpenGUI_TextureDataRect


#endif
