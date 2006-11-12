#include "PCXTests.h"


void
PCXTests::testLoader() {
  static string images[] = {
    "greyscale",
    "greyscale_odd",
    "palettized",
    "palettized_odd",
    "test",
    "test_odd",

    // we don't support these yet
    //"test_v0",
    //"test_v0_odd",
    //"test_v2",
    //"test_v2_odd",
  };
  static const int image_count = sizeof(images) / sizeof(*images);

  static const string img_prefix("images/pcx/");
  static const string img_suffix(".pcx");

  static const string ref_prefix("images/pcx/ref/");
  static const string ref_suffix(".png");

  for (int i = 0; i < image_count; ++i) {
    AssertImagesEqual(img_prefix + images[i] + img_suffix,
                      ref_prefix + images[i] + ref_suffix);
  }
}


Test*
PCXTests::suite() {
  typedef TestCaller<PCXTests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("Test PCX Loader", &PCXTests::testLoader));
  return suite;
}
