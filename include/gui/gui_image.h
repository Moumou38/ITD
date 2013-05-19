#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#if defined __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "tools.h"
#include "image.h"
#include "gui/enums.h"

typedef struct {
	unsigned int id;
	unsigned int type;
	GLuint tex[1];
	Position pos, size;
} Image;


extern Image* createImage(unsigned int id, const char* image, int px, int py, float sizex, float sizey);

extern void drawImage(Image* t);

extern void removeImage(Image* t);

#endif
