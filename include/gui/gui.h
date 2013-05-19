#ifndef GUI_H
#define GUI_H

#include <SDL/SDL.h>
#include "list.h"
#include "queue.h"
#include "gui/button.h"
#include "gui/text.h"
#include "gui/gui_image.h"

typedef struct {
	GUI_WidgetType type;
	int level;
	int id;
	union {
		Button *button;
		Text *text;
		Image *image;
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

extern Button* GUI_CreateButton(unsigned int id, int level, char* text, char* image, SDL_Color color, int px, int py, int w, int h);

extern Text* GUI_CreateText(unsigned int id, int level, char* text, SDL_Color color, int px, int py, FONT_SIZE size);

extern Image* GUI_CreateImage(unsigned int id, int level, const char* image, int px, int py, float sizex, float sizey);

GUI_Widget* GUI_GetWidget(unsigned int id);

void GUI_RemoveWidget(unsigned int id);

#endif
