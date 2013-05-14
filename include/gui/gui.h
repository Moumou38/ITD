#ifndef GUI_H
#define GUI_H

#include <SDL/SDL.h>
#include "list.h"
#include "queue.h"
#include "gui/button.h"
#include "gui/text.h"

typedef struct {
	GUI_WidgetType type;
	int level;
	union {
		Button *button;
		Text *text;
	} w;
} GUI_Widget;

extern GUI_Event* createGuiEvent();

extern void GUI_Init();

extern void GUI_Quit();

extern void GUI_DrawAll();

extern void GUI_Draw(int level);

extern void GUI_Clear();

extern void GUI_ProceedEvents(SDL_Event* event);

extern int GUI_PollEvent(GUI_Event* gui); 

extern Button* GUI_CreateButton(unsigned int id, int level, char* text, SDL_Surface* image, int px, int py, int w, int h);

extern Text* GUI_CreateText(unsigned int id, int level, char* text, SDL_Color color, int px, int py, FONT_SIZE size);

#endif
