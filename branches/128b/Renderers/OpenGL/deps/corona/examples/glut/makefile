# GNU/UNIX makefile
# assumes you have the following variables set:
# CPLUS_INCLUDE_PATH, LIBRARY_PATH, LD_LIBRARY_PATH, C_INCLUDE_PATH

CC = g++
LIBS = -lglut -lGL -lGLU -lcorona

glut: glut.cpp
	$(CC) -o glut glut.cpp $(LIBS)
