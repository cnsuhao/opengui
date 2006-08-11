#ifndef TGA_TESTS_H
#define TGA_TESTS_H


#include "ImageTestCase.h"


class TGATests : public ImageTestCase {
public:
  void testLoader();
  static Test* suite();
};


#endif
