#include "GIFTests.h"


void
GIFTests::testLoader() {
  static string images[] = {
    "clustindex",
    "cover",
    "enter",
    "fireball",
    "image95",
    "panly01",
    "porsche",
    "quake",
    "solid2",
    "x-trans",
    "zemus2",
  };
  static const int image_count = sizeof(images) / sizeof(*images);

  static const string img_prefix("images/gif/");
  static const string img_suffix(".gif");

  static const string ref_prefix("images/gif/ref/");
  static const string ref_suffix(".png");

  for (int i = 0; i < image_count; ++i) {
    AssertImagesEqual(img_prefix + images[i] + img_suffix,
                      ref_prefix + images[i] + ref_suffix);
  }
}


Test*
GIFTests::suite() {
  typedef TestCaller<GIFTests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("Test GIF Loader", &GIFTests::testLoader));
  return suite;
}
