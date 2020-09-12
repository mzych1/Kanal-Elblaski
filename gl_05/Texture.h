#ifndef texture_h
#define texture_h

#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

GLuint LoadMipmapTexture(GLuint texId, const char* fname);


#endif