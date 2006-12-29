#include "TGATests.h"


void
TGATests::testLoader() {
  std::string images[] = { "test", "rgb", "rgb_bottom_left", "rgba" };
  for (unsigned i = 0; i < sizeof(images) / sizeof(*images); ++i) {
    std::string& img = images[i];
    AssertImagesEqual("images/targa/" + img + ".tga",
		      "images/targa/reference/" + img + ".png");
  }
}

Test*
TGATests::suite() {
  typedef TestCaller<TGATests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("Test TGA Loader", &TGATests::testLoader));
  return suite;
}
