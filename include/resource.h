#ifndef RESOURCE_H
#define RESOURCE_H

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <string.h>

#include "list.h"
#include "image.h"

GLuint getTexture(const char* name);

void initResourcesManager();

void deleteResourcesManager();

#endif
