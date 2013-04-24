/*!
 *	\file button.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 10/04/13
 *	
 *	\brief Structures de données et fonctions des boutons
 */

#ifndef BUTTON_H
#define BUTTON_H

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
	BS_DEFAULT = 0,
	BS_HOVER = 1,
	BS_PRESSED = 2,
	BS_DISABLED = 3
} ButtonState;

typedef enum {
	BF_NONE = 0x0000,
	BF_MOVABLE = 0x0001,
	BF_ENABLED = 0x0010,
} ButtonFlags;

typedef struct {
	unsigned int id;
	unsigned int type;
	char* text;
	GLuint tex[4];
	Position pos, size;
	ButtonState state;
	ButtonFlags flags;
} Button;

extern Button* createButton(unsigned int id, char* text, SDL_Surface* image, int px, int py, int w, int h);

extern Button* createEmptyButton(GLuint color);

extern void drawButton(Button* b);

extern int injectEventToButton(Button* b, SDL_Event* event, GUI_ButtonEvent* guiEv);

extern int hoverButton(Button* b, Position p);

extern int clickedButton(Button* b, Position p, int pressed);


extern int isButtonClicked(Button* b);



extern void removeButton(Button* b);

extern int mouseInButton(Button* b, Position p);

extern void enableButtonFlag(Button* b, ButtonFlags flags);

extern void disableButtonFlag(Button* b, ButtonFlags flags);

#endif
