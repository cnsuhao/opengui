#ifndef API_TESTS_H
#define API_TESTS_H


#include "ImageTestCase.h"


class APITests : public ImageTestCase {
public:
  void testBasicOperations(int width, int height);
  void testAPI();
  void testFormatQueries();
  void testMemory();
  static Test* suite();
};


#endif
