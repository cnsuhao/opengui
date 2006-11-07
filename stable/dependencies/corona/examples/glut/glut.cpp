#include <stdlib.h>
#include <GL/glut.h>
#include <corona.h>
#include <memory>
#include <stdio.h>
#include <math.h>
using namespace std;
using namespace corona;


GLuint g_texture;


inline void coord(float x, float y) {
  glTexCoord2f(x, y);
  glVertex2f(x, y);
}


void display() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 1, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glBegin(GL_QUADS);
  coord(0, 0);
  coord(1, 0);
  coord(1, 1);
  coord(0, 1);
  glEnd();

  glutSwapBuffers();
}


void reshape(int w, int h) {
  glViewport(0, 0, w, h);
}


void error(const char* message);


int count_bits(int n) {
  int total = 0;
  int i = 0;
  while (i < 32) {
    if (n & (1 << i)) {
      ++total;
    }
    ++i;
  }
  return total;
}


int main(int argc, char** argv) {

  if (argc != 2) {
    error("Usage: glut <filename>");
    return EXIT_FAILURE;
  }

  glutInit(&argc, argv);

  auto_ptr<Image> img(OpenImage(argv[1], PF_R8G8B8A8));
  if (!img.get()) {
    error("Error loading image");
    return EXIT_FAILURE;
  }

  // verify power-of-two dimensions
  const int width  = img->getWidth();
  const int height = img->getHeight();
  if (count_bits(width) != 1 || count_bits(height) != 1) {
    error("Image must have dimensions that are powers of two");
    return EXIT_FAILURE;
  }

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Corona/GLUT Image Test");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &g_texture);
  glBindTexture(GL_TEXTURE_2D, g_texture);
  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
    0, GL_RGBA, GL_UNSIGNED_BYTE, img->getPixels());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glutMainLoop();

  // VC++ 6 sucks
  return 0;
}


#ifdef _WIN32

  #include <windows.h>

  void error(const char* message) {
    MessageBox(0, message, "Corona/GLUT", MB_ICONERROR | MB_OK);
  }

  int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main(__argc, __argv);
  }

#else

  void error(const char* message) {
    puts(message);
  }

#endif
