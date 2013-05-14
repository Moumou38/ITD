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

typedef enum {
	FONT_8 = 0,
	FONT_12 = 1,
	FONT_24 = 2,
	FONT_32 = 3,
	FONT_48 = 4,
	MAX_FONTS = 5
} FONT_SIZE;


typedef struct {
	unsigned int id;
	unsigned int type;
	char* text;
	GLuint tex[1];
	Position pos, size;
	SDL_Color color;
	TTF_Font* font;
} Text;

extern TTF_Font *polices[MAX_FONTS];

extern void Text_Init();

extern void Text_Quit();

extern Text* createText(unsigned int id, char* text, SDL_Color color, int px, int py, FONT_SIZE size);

extern void setText(Text* t, const char* text);

extern void drawText(Text* t);

extern void removeText(Text* t);

#endif
