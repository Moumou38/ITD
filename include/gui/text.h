/*!
 *	\file text.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 24/04/13
 *	
 *	\brief Structures de données et fonctions du text
 */

#ifndef TEXT_H
#define TEXT_H

#if defined __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "tools.h"
#include "image.h"
#include "gui/enums.h"


typedef struct {
	unsigned int id;
	unsigned int type;
	char* text;
	GLuint tex[1];
	Position pos, size;
	SDL_Color color;
} Text;

extern Text* createText(unsigned int id, char* text, SDL_Color color, int px, int py, int w, int h);

extern void setText(Text* t, const char* text);

extern void drawText(Text* t);

extern void removeText(Text* t);

#endif
