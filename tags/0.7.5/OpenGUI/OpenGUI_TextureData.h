#ifndef D10169F3_7AC3_4a10_8691_2762C02DA230
#define D10169F3_7AC3_4a10_8691_2762C02DA230

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

namespace OpenGUI{
	/*! \brief
		Represents in memory Texture data.
		Also provides built-in loading of BMP, GIF, JPEG, PCX, PNG, and TGA image files
		(via the current ResourceProvider), into a known data format so
		that textures can be created from them.

		This loader only provides data in 3 formats, signified by the BytesPerPixel:\n
		- RGB -- 3 Bpp
		- RGBA -- 4Bpp
		- A -- 1 Bpp

		If you want something more robust, "http://openil.sourceforge.net",
		and load them yourself. =)
	*/
	class OPENGUI_API TextureData
	{
	public:
		TextureData();
		~TextureData();
		unsigned char* getPixelData() const; //!< Returns a pointer to the pixel data.
		int getWidth() const; //!< Returns the texture data width.
		int getHeight() const;//!< Returns the texture data height.
		int getBPP() const;//!< Returns the bytes per pixel.

		//! Fills this TextureData object. All parameters are required. Unless you know what you're doing, you probably don't want to do this.
		/*!
			\param width The width of the image
			\param height The height of the image
			\param bpp Bytes per pixel
			\param dataSource The source of the data to contain.

			The \c dataSource is copied to a new buffer, so updates to buffer originally given will not
			be reflected in the texture data.
		*/
		void setData(int width, int height, int bpp, void* dataSource);

		//! Creates new internal data with the given width and height and bpp, initializes with the given initData.
		/*!
			\param width The width of the image
			\param height The height of the image
			\param bpp Bytes per pixel
			\param initData If non-zero, this must be an array of unsigned char with a length equal to \c bpp.
				The contents of the array will be repeated as initialization data for the contents of the
				TextureData. If zero is given in place of a valid pointer, all bytes will be initialized to 0.
		*/
		void createNewData(int width, int height, int bpp, unsigned char* initData);
	private:
		unsigned char* mPixelData;
		int mHeight; //image height
		int mWidth; //image width
		int mBPP; //bytes per pixel
	public:
		//! Loads the given \c filename into a TextureData object and returns the resulting object pointer, or 0 on fail.
		/*! \note This uses the Corona library to read the file format.	*/
		static TextureData* LoadTextureData(std::string filename);

	};
};//namespace OpenGUI{
#endif
