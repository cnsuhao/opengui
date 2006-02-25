#ifndef JPEG_TESTS_H
#define JPEG_TESTS_H


#include "ImageTestCase.h"


class JPEGTests : public ImageTestCase {
public:
  void testLoader();
  void testIncomplete();
  static Test* suite();
};


#endif
