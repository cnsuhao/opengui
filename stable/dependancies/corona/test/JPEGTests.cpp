#include "JPEGTests.h"


void
JPEGTests::testLoader() {
  static string images[] = {
    "63",
    "63-1-subsampling",
    "63-floating",
    "63-high",
    "63-low",
    "63-progressive",
    "63-restart",
    "64",
    "comic-progressive",
  };
  static const int image_count = sizeof(images) / sizeof(*images);

  static const string img_prefix("images/jpeg/");
  static const string img_suffix(".jpeg");

  static const string ref_prefix("images/jpeg/ref/");
  static const string ref_suffix(".png");

  for (int i = 0; i < image_count; ++i) {
    AssertImagesEqual(img_prefix + images[i] + img_suffix,
                      ref_prefix + images[i] + ref_suffix);
  }
}


void
JPEGTests::testIncomplete() {
  auto_ptr<Image> image(OpenImage("images/jpeg/jack-incomplete.jpeg"));
  CPPUNIT_ASSERT(image.get() != 0);
}


Test*
JPEGTests::suite() {
  typedef TestCaller<JPEGTests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("JPEG Loader", &JPEGTests::testLoader));
  suite->addTest(new Caller("Incomplete JPEG", &JPEGTests::testIncomplete));
  return suite;
}
