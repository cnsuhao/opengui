#ifndef BMP_TESTS_H
#define BMP_TESTS_H


#include "ImageTestCase.h"


class BMPTests : public ImageTestCase {
public:
  void testLoader();
  static Test* suite();
};


#endif
