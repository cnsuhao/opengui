#include <algorithm>
#include "APITests.h"


void
APITests::testBasicOperations(int width, int height) {
  const PixelFormat format = PF_R8G8B8A8;
  const int bpp = 4;

  auto_ptr<Image> image(CreateImage(width, height, format));
  CPPUNIT_ASSERT(image->getWidth()  == width);
  CPPUNIT_ASSERT(image->getHeight() == height);
  CPPUNIT_ASSERT(image->getFormat() == format);

  // verify that the image is black
  byte* pixels = (byte*)image->getPixels();
  for (int i = 0; i < width * height * bpp; ++i) {
    CPPUNIT_ASSERT(pixels[i] == 0);
  }

  // fill the image with random pixels
  for (int i = 0; i < width * height * bpp; ++i) {
    pixels[i] = rand() % 256;
  }

  auto_ptr<Image> create_clone(
      CreateImage(image->getWidth(), image->getHeight(),
                  image->getFormat(), image->getPixels()));
  CPPUNIT_ASSERT(create_clone.get());
  CPPUNIT_ASSERT(image->getWidth()  == create_clone->getWidth());
  CPPUNIT_ASSERT(image->getHeight() == create_clone->getHeight());
  CPPUNIT_ASSERT(image->getFormat() == create_clone->getFormat());
  CPPUNIT_ASSERT(memcmp(image->getPixels(),
                        create_clone->getPixels(),
                        width * height * bpp) == 0);

  // clone the image (use same pixel format)
  auto_ptr<Image> identical_clone(CloneImage(image.get()));
  CPPUNIT_ASSERT(image->getWidth()  == identical_clone->getWidth());
  CPPUNIT_ASSERT(image->getHeight() == identical_clone->getHeight());
  CPPUNIT_ASSERT(image->getFormat() == identical_clone->getFormat());
  CPPUNIT_ASSERT(memcmp(image->getPixels(),
                        identical_clone->getPixels(),
                        width * height * bpp) == 0);

  // clone the image, removing the alpha channel
  auto_ptr<Image> other_clone(CloneImage(identical_clone.get(), PF_R8G8B8));
  CPPUNIT_ASSERT(image->getWidth()  == other_clone->getWidth());
  CPPUNIT_ASSERT(image->getHeight() == other_clone->getHeight());
  CPPUNIT_ASSERT(other_clone->getFormat() == PF_R8G8B8);
  byte* image_p = (byte*)image->getPixels();
  byte* other_p = (byte*)other_clone->getPixels();
  for (int i = 0; i < width * height; ++i) {
    CPPUNIT_ASSERT(*image_p++ == *other_p++);
    CPPUNIT_ASSERT(*image_p++ == *other_p++);
    CPPUNIT_ASSERT(*image_p++ == *other_p++);
    ++image_p;  // skip alpha
  }

  // flip the image
  // clone source first, since flip frees the original
  auto_ptr<Image> flip_none(FlipImage(CloneImage(image.get()), 0));
  auto_ptr<Image> flip_x   (FlipImage(CloneImage(image.get()), CA_X));
  auto_ptr<Image> flip_y   (FlipImage(CloneImage(image.get()), CA_Y));
  auto_ptr<Image> flip_xy  (FlipImage(CloneImage(image.get()), CA_X | CA_Y));

  AssertImagesEqual("No flipping", flip_none.get(), image.get());

  CPPUNIT_ASSERT(flip_x.get() != 0);
  CPPUNIT_ASSERT(width  == flip_x->getWidth());
  CPPUNIT_ASSERT(height == flip_x->getHeight());
  CPPUNIT_ASSERT(format == flip_x->getFormat());

  CPPUNIT_ASSERT(flip_y.get() != 0);
  CPPUNIT_ASSERT(width  == flip_y->getWidth());
  CPPUNIT_ASSERT(height == flip_y->getHeight());
  CPPUNIT_ASSERT(format == flip_y->getFormat());

  CPPUNIT_ASSERT(flip_xy.get() != 0);
  CPPUNIT_ASSERT(width  == flip_xy->getWidth()); 
  CPPUNIT_ASSERT(height == flip_xy->getHeight());
  CPPUNIT_ASSERT(format == flip_xy->getFormat());

  const byte* flip_x_pixels  = (const byte*)flip_x->getPixels();
  const byte* flip_y_pixels  = (const byte*)flip_y->getPixels();
  const byte* flip_xy_pixels = (const byte*)flip_xy->getPixels();

  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      const int image_index = (h * width + w) * bpp;
      const int opp_w = width  - 1 - w;
      const int opp_h = height - 1 - h;
      const int flip_x_index  = (opp_h * width + w) * bpp;
      const int flip_y_index  = (h * width + opp_w) * bpp;
      const int flip_xy_index = (opp_h * width + opp_w) * bpp;
      
      for (int p = 0; p < bpp; p++) {
        CPPUNIT_ASSERT(pixels[image_index] == flip_x_pixels [flip_x_index]);
        CPPUNIT_ASSERT(pixels[image_index] == flip_y_pixels [flip_y_index]);
        CPPUNIT_ASSERT(pixels[image_index] == flip_xy_pixels[flip_xy_index]);
      }
    }
  }

}


void
APITests::testAPI() {
  for (int w = 0; w <= 16; ++w) {
    for (int h = 0; h <= 16; ++h) {
      testBasicOperations(w, h);
    }
  }
}


/// Basically the same as SimpleImage, but it sets a boolean flag when
/// the image is deleted.
class TestDeletionImage : public DLLImplementation<Image> {
public:
  TestDeletionImage(
    int width, int height,
    PixelFormat format, byte* pixels,
    byte* palette, int palette_size, PixelFormat palette_format,
    bool& deleted)
  : m_deleted(deleted)
  {
    m_width          = width;
    m_height         = height;
    m_format         = format;
    m_pixels         = pixels;
    m_palette        = palette;
    m_palette_size   = palette_size;
    m_palette_format = palette_format;
  }

  ~TestDeletionImage() {
    delete[] m_pixels;
    delete[] m_palette;
    m_deleted = true;
  }

  int COR_CALL getWidth() {
    return m_width;
  }

  int COR_CALL getHeight() {
    return m_height;
  }

  PixelFormat COR_CALL getFormat() {
    return m_format;
  }

  void* COR_CALL getPixels() {
    return m_pixels;
  }

  void* COR_CALL getPalette() {
    return m_palette;
  }

  int COR_CALL getPaletteSize() {
    return m_palette_size;
  }

  PixelFormat COR_CALL getPaletteFormat() {
    return m_palette_format;
  }

private:
  int         m_width;
  int         m_height;
  PixelFormat m_format;
  byte*       m_pixels;
  byte*       m_palette;
  int         m_palette_size;
  PixelFormat m_palette_format;
  bool&       m_deleted;
};


void
APITests::testFormatQueries() {
    CPPUNIT_ASSERT(GetPixelSize(PF_R8G8B8A8) == 4);
    CPPUNIT_ASSERT(GetPixelSize(PF_B8G8R8A8) == 4);
    CPPUNIT_ASSERT(GetPixelSize(PF_R8G8B8)   == 3);
    CPPUNIT_ASSERT(GetPixelSize(PF_B8G8R8)   == 3);
    CPPUNIT_ASSERT(GetPixelSize(PF_I8)       == 1);
    CPPUNIT_ASSERT(GetPixelSize(PF_DONTCARE) == 0);
    
    CPPUNIT_ASSERT(IsDirect(PF_R8G8B8A8));
    CPPUNIT_ASSERT(IsDirect(PF_B8G8R8A8));
    CPPUNIT_ASSERT(IsDirect(PF_R8G8B8));
    CPPUNIT_ASSERT(IsDirect(PF_B8G8R8));
    CPPUNIT_ASSERT(!IsDirect(PF_I8));
    CPPUNIT_ASSERT(!IsDirect(PF_DONTCARE));
    
    CPPUNIT_ASSERT(!IsPalettized(PF_R8G8B8A8));
    CPPUNIT_ASSERT(!IsPalettized(PF_B8G8R8A8));
    CPPUNIT_ASSERT(!IsPalettized(PF_R8G8B8));
    CPPUNIT_ASSERT(!IsPalettized(PF_B8G8R8));
    CPPUNIT_ASSERT(IsPalettized(PF_I8));
    CPPUNIT_ASSERT(!IsPalettized(PF_DONTCARE));

    CPPUNIT_ASSERT(GetPaletteSize(PF_R8G8B8A8) == 0);
    CPPUNIT_ASSERT(GetPaletteSize(PF_B8G8R8A8) == 0);
    CPPUNIT_ASSERT(GetPaletteSize(PF_R8G8B8)   == 0);
    CPPUNIT_ASSERT(GetPaletteSize(PF_B8G8R8)   == 0);
    CPPUNIT_ASSERT(GetPaletteSize(PF_I8)       == 256);
    CPPUNIT_ASSERT(GetPaletteSize(PF_DONTCARE) == 0);
}


/**
 * Replacement for new[] that initializes with the type's default
 * value.  This is needed so valgrind doesn't think the test uses
 * uninitialized memory.
 */
template<typename T>
inline T* allocate(size_t size) {
  T* t = new T[size];
  std::fill(t, t + size, T());
  return t;
}


void
APITests::testMemory() {
  {
    // ConvertImage() should delete the image if it successfully
    // converts.
    bool convert_image_deleted = false;
    Image* image = new TestDeletionImage(
      16, 16, PF_I8, allocate<byte>(256), allocate<byte>(256 * 4), 256, PF_R8G8B8,
      convert_image_deleted);
    delete ConvertImage(image, PF_R8G8B8A8);
    CPPUNIT_ASSERT(convert_image_deleted == true);
  }

  {
    // ConvertImage() should also delete the image if it cannot
    // convert.
    bool convert_image_deleted = false;
    Image* image = new TestDeletionImage(
      16, 16, PF_I8, allocate<byte>(256), allocate<byte>(256 * 4), 256, PF_R8G8B8,
      convert_image_deleted);
    delete ConvertImage(image, PF_I8);
    CPPUNIT_ASSERT(convert_image_deleted == true);
  }

  {
    bool convert_palette_deleted = false;
    Image* image = new TestDeletionImage(
      16, 16, PF_I8, allocate<byte>(256), allocate<byte>(256 * 4), 256, PF_R8G8B8,
      convert_palette_deleted);
    delete ConvertPalette(image, PF_R8G8B8A8);
    CPPUNIT_ASSERT(convert_palette_deleted == true);
  }

  {
    bool convert_palette_deleted = false;
    Image* image = new TestDeletionImage(
      16, 16, PF_I8, allocate<byte>(256), allocate<byte>(256 * 4), 256, PF_R8G8B8,
      convert_palette_deleted);
    delete ConvertPalette(image, PF_I8);
    CPPUNIT_ASSERT(convert_palette_deleted == true);
  }

  {
    bool convert_image_deleted = false;
    Image* image = new TestDeletionImage(
      16, 16, PF_I8, allocate<byte>(256), allocate<byte>(256 * 4), 256, PF_R8G8B8,
      convert_image_deleted);
    delete FlipImage(image, CA_X);
    CPPUNIT_ASSERT(convert_image_deleted == true);
  }
}


Test*
APITests::suite() {
  typedef TestCaller<APITests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("Basic API Tests",   &APITests::testAPI));
  suite->addTest(new Caller("Format Queries",    &APITests::testFormatQueries));
  suite->addTest(new Caller("Memory Management", &APITests::testMemory));
  return suite;
}
