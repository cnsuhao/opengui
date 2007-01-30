#ifndef PALETTE_TESTS_H
#define PALETTE_TESTS_H


#include "ImageTestCase.h"


class PaletteTests : public ImageTestCase {
public:
  void testAPI();
  void testImages();
  static Test* suite();
};


#endif
