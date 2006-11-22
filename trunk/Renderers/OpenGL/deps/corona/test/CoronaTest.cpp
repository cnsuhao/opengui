#include "TestFramework.h"
#include "APITests.h"
#include "BMPTests.h"
#include "FileTests.h"
#include "GIFTests.h"
#include "JPEGTests.h"
#include "PaletteTests.h"
#include "PCXTests.h"
#include "PNGTests.h"
#include "TGATests.h"


int main() {
  TextTestRunner runner;
  runner.addTest(APITests::suite());
  runner.addTest(FileTests::suite());
  runner.addTest(BMPTests::suite());
  runner.addTest(GIFTests::suite());
  runner.addTest(JPEGTests::suite());
  runner.addTest(PCXTests::suite());
  runner.addTest(PNGTests::suite());
  runner.addTest(TGATests::suite());

  // this is last because it depends on proper image loaders
  runner.addTest(PaletteTests::suite());

  runner.run();
  return 0;
}
