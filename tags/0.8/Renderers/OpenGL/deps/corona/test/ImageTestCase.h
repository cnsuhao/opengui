#ifndef IMAGE_TEST_CASE_H
#define IMAGE_TEST_CASE_H


#include "TestFramework.h"


class ImageTestCase : public CppUnit::TestCase {
public:
  struct Comparison {
    const char* image;
    const char* reference;
  };

  void AssertImagesEqual(
    const string& image_file,
    const string& reference_file)
  {
    auto_ptr<Image> img1(OpenImage(image_file.c_str(), PF_R8G8B8A8));
    CPPUNIT_ASSERT_MESSAGE("opening " + image_file, img1.get() != 0);

    auto_ptr<Image> img2(OpenImage(reference_file.c_str(), PF_R8G8B8A8));
    CPPUNIT_ASSERT_MESSAGE("opening " + reference_file, img2.get() != 0);

    AssertImagesEqual("testing " + image_file, img1.get(), img2.get());
  }

  void AssertImagesEqual(
    const string& message,
    Image* i1,
    Image* i2)
  {
    // compare sizes
    CPPUNIT_ASSERT(i1->getWidth()  == i2->getWidth() &&
                   i1->getHeight() == i2->getHeight());
    
    // by this point, we can assume they have the same size
    int width  = i1->getWidth();
    int height = i1->getHeight();
    
    // compare formats
    PixelFormat i1_format = i1->getFormat();
    CPPUNIT_ASSERT_MESSAGE(message, i1_format == i2->getFormat());

    // compare pixel data
    int pixel_comparison = memcmp(
      i1->getPixels(),
      i2->getPixels(),
      width * height * GetPixelSize(i1_format));
    CPPUNIT_ASSERT_MESSAGE(message, pixel_comparison == 0);

    // compare palette formats
    PixelFormat i1_plt_format = i1->getPaletteFormat();
    PixelFormat i2_plt_format = i2->getPaletteFormat();
    CPPUNIT_ASSERT_MESSAGE(message, i1_plt_format == i2_plt_format);

    // compare palette sizes
    int i1_plt_size = i1->getPaletteSize();
    int i2_plt_size = i2->getPaletteSize();
    CPPUNIT_ASSERT_MESSAGE(message, i1_plt_size == i2_plt_size);

    // compare palette data
    int palette_comparison = memcmp(
      i1->getPalette(),
      i2->getPalette(),
      i1_plt_size * GetPixelSize(i1_plt_format));
    CPPUNIT_ASSERT_MESSAGE(message, palette_comparison == 0);
  }
};


#endif
