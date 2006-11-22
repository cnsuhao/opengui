#include "PaletteTests.h"


struct RGB {
  byte red;
  byte green;
  byte blue;
};

struct BGR {
  byte blue;
  byte green;
  byte red;
};


void
PaletteTests::testAPI() {
  // make sure basic palettized image stuff works
  auto_ptr<Image> img1(CreateImage(32, 32, PF_I8,
                                   256, PF_R8G8B8));
  byte* pixels = (byte*)img1->getPixels();
  RGB* palette = (RGB*)img1->getPalette();
  for (int i = 0; i < 32 * 32; ++i) {
    pixels[i] = i % 256;
  }
  for (int i = 0; i < 256; ++i) {
    palette[i].red   = i;
    palette[i].green = i;
    palette[i].blue  = i;
  }

  CPPUNIT_ASSERT(img1->getFormat() == PF_I8);
  CPPUNIT_ASSERT(img1->getPaletteFormat() == PF_R8G8B8);

  // duplicate
  auto_ptr<Image> clone(CloneImage(img1.get()));
  CPPUNIT_ASSERT(clone->getFormat() == PF_I8);
  CPPUNIT_ASSERT(clone->getPaletteFormat() == PF_R8G8B8);
  CPPUNIT_ASSERT(clone->getPaletteSize() == 256);

  AssertImagesEqual("Comparing clone of palettized image",
                    img1.get(), clone.get());

  // convert to R8G8B8
  auto_ptr<Image> conv(CloneImage(img1.get(), PF_R8G8B8));
  CPPUNIT_ASSERT(conv->getFormat() == PF_R8G8B8);
  CPPUNIT_ASSERT(conv->getPalette() == 0);
  CPPUNIT_ASSERT(conv->getPaletteFormat() == PF_DONTCARE);
  CPPUNIT_ASSERT(conv->getPaletteSize() == 0);

  // make sure the converted image is right
  RGB* conv_pixels = (RGB*)conv->getPixels();
  bool exact = true;
  for (int i = 0; i < 32 * 32; ++i) {
    exact = exact && (conv_pixels[i].red   == i % 256 &&
                      conv_pixels[i].green == i % 256 &&
                      conv_pixels[i].blue  == i % 256);
  }
  CPPUNIT_ASSERT(exact == true);

  // passing in an invalid palette size should fail
  auto_ptr<Image> img2(CreateImage(32, 32, PF_I8, 255, PF_R8G8B8));
  auto_ptr<Image> img3(CreateImage(32, 32, PF_I8, 257, PF_R8G8B8));
  CPPUNIT_ASSERT(img2.get() == 0);
  CPPUNIT_ASSERT(img3.get() == 0);

  // can't create palettized images with direct-color CreateImage and
  // vice versa
  auto_ptr<Image> img4(CreateImage(32, 32, PF_I8));
  auto_ptr<Image> img5(CreateImage(32, 32, PF_R8G8B8, 256, PF_R8G8B8));
  auto_ptr<Image> img6(CreateImage(32, 32, PF_R8G8B8, 256, PF_I8));
  CPPUNIT_ASSERT(img4.get() == 0);
  CPPUNIT_ASSERT(img5.get() == 0);
  CPPUNIT_ASSERT(img6.get() == 0);


  // test ConvertPaletteFormat

  auto_ptr<Image> img7(CreateImage(16, 16, PF_I8, 256, PF_R8G8B8));
  CPPUNIT_ASSERT(img7.get() != 0);

  pixels = (byte*)img7->getPixels();
  for (int i = 0; i < 16 * 16; ++i) {
    pixels[i] = i;
  }
  palette = (RGB*)img7->getPalette();
  for (int i = 0; i < 256; ++i) {
    palette[i].red   = i;
    palette[i].green = 255 - i;
    palette[i].blue  = 127 + (i % 2);
  }

  auto_ptr<Image> img8(ConvertPalette(CloneImage(img7.get()), PF_B8G8R8));
  CPPUNIT_ASSERT(img8.get() != 0);
  CPPUNIT_ASSERT(img8->getWidth() == 16);
  CPPUNIT_ASSERT(img8->getHeight() == 16);
  CPPUNIT_ASSERT(img8->getFormat() == PF_I8);
  CPPUNIT_ASSERT(img8->getPaletteSize() == 256);
  CPPUNIT_ASSERT(img8->getPaletteFormat() == PF_B8G8R8);

  bool pixels_correct = true;
  pixels = (byte*)img8->getPixels();
  for (int i = 0; i < 16 * 16; ++i) {
    pixels_correct = pixels_correct && (pixels[i] == i);
  }
  CPPUNIT_ASSERT(pixels_correct == true);

  bool palette_correct = true;
  BGR* bgr_palette = (BGR*)img8->getPalette();
  for (int i = 0; i < 256; ++i) {
    palette_correct = palette_correct && (
      bgr_palette[i].red   == i       &&
      bgr_palette[i].green == 255 - i &&
      bgr_palette[i].blue  == 127 + (i % 2));
  }
  CPPUNIT_ASSERT(palette_correct == true);
}


void
PaletteTests::testImages() {
  auto_ptr<Image> pcx(OpenImage("images/palettized/pcx.pcx"));
  // @todo  test BMP images
  // @todo  test PNG images
  // @todo  test GIF images

  CPPUNIT_ASSERT(pcx.get() && pcx->getFormat() == PF_I8);
}


Test*
PaletteTests::suite() {
  typedef TestCaller<PaletteTests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("Palettized Image Tests", &PaletteTests::testAPI));
  suite->addTest(new Caller("Palettized Images",      &PaletteTests::testImages));
  return suite;
}
