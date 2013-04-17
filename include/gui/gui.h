#ifndef GUI_H
#define GUI_H

#include <SDL/SDL.h>
#include "list.h"
#include "queue.h"

typedef enum {
	GUI_ET_BUTTON
} GUI_EventType;

typedef enum {
	GUI_HOVER,
	GUI_PRESSED,
	GUI_RELEASED
} GUI_EventButtonAction;

typedef struct {
	GUI_EventType type;
	unsigned int id;
	GUI_EventButtonAction action;
} GUI_ButtonEvent;

typedef union {
	GUI_EventType type;
	GUI_ButtonEvent button;
} GUI_Event;

extern void GUI_Init();

extern void GUI_Quit();

extern int GUI_PollEvent(SDL_Event* event, GUI_Event* gui); 

#endif
