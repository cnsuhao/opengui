#include "BMPTests.h"


void
BMPTests::testLoader() {
  static const string base = "images/bmpsuite/";
  static const string reference_base = "images/bmpsuite/reference/";

  static Comparison images[] = {
    { "g01bg.bmp",     "01bg.png"    },
    { "g01bw.bmp",     "01bw.png"    },
    { "g01p1.bmp",     "01p1.png"    },
    { "g01wb.bmp",     "01bw.png"    },
    { "g04.bmp",       "04.png"      },
    { "g04p4.bmp",     "04p4.png"    },
    { "g04rle.bmp",    "04.png"      },
    { "g08.bmp",       "08.png"      },
    { "g08offs.bmp",   "08.png"      },
    { "g08os2.bmp",    "08.png"      },
    { "g08p256.bmp",   "08.png"      },
    { "g08p64.bmp",    "08p64.png"   },
    { "g08pi256.bmp",  "08.png"      },
    { "g08pi64.bmp",   "08.png"      },
    { "g08res11.bmp",  "08.png"      },
    { "g08res21.bmp",  "08.png"      },
    { "g08res22.bmp",  "08.png"      },
    { "g08rle.bmp",    "08.png"      },
    { "g08s0.bmp",     "08.png"      },
    { "g08w124.bmp",   "08w124.png"  },
    { "g08w125.bmp",   "08w125.png"  },
    { "g08w126.bmp",   "08w126.png"  },
    { "g16bf555.bmp",  "16bf555.png" },
    { "g16bf565.bmp",  "16bf565.png" },
    { "g16def555.bmp", "16bf555.png" },
    { "g24.bmp",       "24.png"      },
    { "g32bf.bmp",     "24.png"      },
    { "g32def.bmp",    "24.png"      },
  };
  static const int image_count = sizeof(images) / sizeof(*images);

  for (int i = 0; i < image_count; ++i) {
    AssertImagesEqual(base + images[i].image,
                      reference_base + images[i].reference);
  }
}


Test*
BMPTests::suite() {
  typedef TestCaller<BMPTests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("Test BMP Loader", &BMPTests::testLoader));
  return suite;
}
