#ifndef PNG_TESTS_H
#define PNG_TESTS_H


#include "ImageTestCase.h"


class PNGTests : public ImageTestCase {
public:
  void testLoader();
  void testWriter();
  static Test* suite();
};


#endif
