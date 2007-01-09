#ifndef FILE_TESTS_H
#define FILE_TESTS_H


#include "ImageTestCase.h"


class FileTests : public ImageTestCase {
public:
  void testMemoryFiles();
  void testMemoryLoads();
  static Test* suite();
};


#endif
