#ifndef D10169F3_7AC3_4a10_8691_2762C02DA230
#define D10169F3_7AC3_4a10_8691_2762C02DA230

#include "OpenGUI_Exports.h"
namespace OpenGUI{
	/*! \brief
		Provides loading of BMP, GIF, JPEG, PCX, PNG, and TGA image files
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
		unsigned char* getPixelData(); //!< Returns a pointer to the pixel data.
		int getWidth(); //!< Returns the texture data width.
		int getHeight();//!< Returns the texture data height.
		int getBPP();//!< Returns the bytes per pixel.

		//! Fills this TextureData object. All parameters are required. Unless you know what you're doing, you probably don't want to do this.
		void setData(int width, int height, int bpp, void* dataSource);
	private:
		unsigned char* mPixelData;
		int mHeight; //image height
		int mWidth; //image width
		int mBPP; //bytes per pixel
	public:
		static TextureData* LoadTextureData(std::string filename);
		
	};
};//namespace OpenGUI{
#endif
