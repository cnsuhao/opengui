#ifndef PCX_TESTS_H
#define PCX_TESTS_H


#include "ImageTestCase.h"


class PCXTests : public ImageTestCase {
public:
  void testLoader();
  static Test* suite();
};


#endif
