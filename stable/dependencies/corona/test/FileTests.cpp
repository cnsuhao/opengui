#include <stdio.h>
#include "FileTests.h"


inline int GetFileSize(File* file) {
  int pos = file->tell();
  if (!file->seek(0, File::END)) {
    return -1;
  }
  int end = file->tell();
  if (!file->seek(pos, File::BEGIN)) {
    return -1;
  }
  return end;
}


void
FileTests::testMemoryFiles() {
  // a valid size but no data?
  std::auto_ptr<File> invalid_file1(CreateMemoryFile(0, 1));
  CPPUNIT_ASSERT(invalid_file1.get() == 0);

  // invalid size
  char dummy[3];
  std::auto_ptr<File> invalid_file2(CreateMemoryFile(dummy, -1));
  CPPUNIT_ASSERT(invalid_file2.get() == 0);

  // no size, no buffer
  std::auto_ptr<File> empty_file(CreateMemoryFile(0, 0));
  CPPUNIT_ASSERT(empty_file.get() != 0);

  dummy[0] = 1;
  dummy[1] = 2;
  dummy[2] = 3;
  CPPUNIT_ASSERT(empty_file->write(dummy, 3) == 3);
  CPPUNIT_ASSERT(GetFileSize(empty_file.get()) == 3);
  CPPUNIT_ASSERT(empty_file->read(dummy, 3) == 0);
  CPPUNIT_ASSERT(empty_file->seek(0, File::BEGIN) == true);
  CPPUNIT_ASSERT(empty_file->read(dummy, 3) == 3);
  CPPUNIT_ASSERT(dummy[0] == 1 && dummy[1] == 2 && dummy[2] == 3);

  byte* buffer = new byte[101];
  for (int i = 0; i < 101; ++i) {
    buffer[i] = i;
  }
  auto_ptr<File> file(CreateMemoryFile(buffer, 101));
  delete[] buffer;

  // make sure the file is valid
  CPPUNIT_ASSERT(file.get() != 0);

  char beginning[10];
  char end[20];
  CPPUNIT_ASSERT(file->read(beginning, 10) == 10);
  CPPUNIT_ASSERT(file->seek(-10, File::END));
  CPPUNIT_ASSERT(file->read(end, 20) == 10);

  for (int i = 0; i < 10; ++i) {
    CPPUNIT_ASSERT(beginning[i] == i);
    CPPUNIT_ASSERT(end[i] == i + 91);
  }
}


void
FileTests::testMemoryLoads() {
  static string images[] = {
    "bmpsuite/g04rle.bmp",
    "gif/solid2.gif",
    "jpeg/63-restart.jpeg",
    "pcx/test.pcx",
    "pngsuite/g07n3p04.png",
    "targa/test.tga",
  };
  static const int image_count = sizeof(images) / sizeof(*images);

  for (int i = 0; i < image_count; ++i) {
    string filename = "images/" + images[i];

    // first, load the file into a big block of memory
    FILE* file = fopen(filename.c_str(), "rb");
    CPPUNIT_ASSERT(file != 0);
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    byte* buffer = new byte[file_size];
    fseek(file, 0, SEEK_SET);
    CPPUNIT_ASSERT((int)fread(buffer, 1, file_size, file) == file_size);
    fclose(file);

    // then create a memory file from it
    auto_ptr<File> memfile(CreateMemoryFile(buffer, file_size));
    CPPUNIT_ASSERT(memfile.get() != 0);
    delete[] buffer;

    // load a copy of the image from the memfile
    auto_ptr<Image> memimage(OpenImage(memfile.get()));
    CPPUNIT_ASSERT_MESSAGE("opening " + images[i], memimage.get() != 0);

    // then ask Corona to load it without using a MemFile
    auto_ptr<Image> diskimage(OpenImage(filename.c_str()));
    CPPUNIT_ASSERT_MESSAGE("opening " + images[i], diskimage.get() != 0);

    AssertImagesEqual(images[i], memimage.get(), diskimage.get());
  }
}


Test*
FileTests::suite() {
  typedef TestCaller<FileTests> Caller;

  TestSuite* suite = new TestSuite();
  suite->addTest(new Caller("MemoryFile Tests", &FileTests::testMemoryFiles));
  suite->addTest(new Caller("Load from MemoryFile", &FileTests::testMemoryLoads));
  return suite;
}
