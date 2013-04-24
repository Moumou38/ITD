#include "gui/gui.h"

Queue* events = NULL;
List* widgets = NULL;

GUI_Event* createGuiEvent()
{
	GUI_Event* gui = malloc(sizeof(GUI_Event));
	gui->type = GUI_NONE;
	return gui;
}

void GUI_Init()
{
	events = queue_init();
	widgets = list_init();
	printf("GUI initialized\n");
}

void GUI_Quit()
{
	GUI_Clear();
	list_delete(widgets);
	queue_delete(events);
}

void GUI_Draw()
{
	Data* d = list_getData(widgets, 0);
	while(d != NULL)
	{
		GUI_Widget* w = (GUI_Widget*)d->value;
		switch(w->type) {
			case GUI_BUTTON:
					drawButton(w->w.button);
				break;
			case GUI_TEXT:
					drawText(w->w.text);
				break;
			default:
				break;
		}
		d = d->next;
	}
}

void GUI_Clear()
{
	while(list_size(widgets)) {
		GUI_Widget* w = list_get(widgets, 0);
		switch(w->type) {
			case GUI_BUTTON:
					removeButton(w->w.button);
				break;
			case GUI_TEXT:
					removeText(w->w.text);
				break;
			default:
				break;
		}
		list_remove(widgets, 0);
	}

	while(queue_size(events))
	{
		GUI_Event* ev = (GUI_Event*)queue_peek(events);
		queue_pop(events);
		free(ev);
	}
}

void GUI_ProceedEvents(SDL_Event* event)
{
	Data* d = list_getData(widgets, 0);
	while(d != NULL)
	{
		GUI_Event* gui = createGuiEvent();
		GUI_Widget* w = (GUI_Widget*)d->value;
		switch(w->type) {
			case GUI_BUTTON:
					injectEventToButton(w->w.button, event, &(gui->button));
				break;
			default:
				break;
		}
		if(gui->type != GUI_NONE) {
			queue_push(events, (void*)gui);
		}
		else 
			free(gui);

		d = d->next;
	}
}

int GUI_PollEvent(GUI_Event* gui)
{
	if(!queue_size(events))
		return 0;
	else {
		GUI_Event* ev = (GUI_Event*)queue_peek(events);
		*gui = *ev;
		queue_pop(events);
		free(ev);
		return 1;
	}
}

void GUI_RegisterButton(Button* b)
{
	GUI_Widget* w = malloc(sizeof(GUI_Widget));
	w->type = GUI_BUTTON;
	w->w.button = b;
	list_append(widgets, w);
}

Button* GUI_CreateButton(unsigned int id, char* text, SDL_Surface* image, int px, int py, int w, int h)
{
	GUI_Widget* wid = malloc(sizeof(GUI_Widget));
	wid->type = GUI_BUTTON;
	wid->w.button = createButton(id, text, image, px, py, w, h);
	list_append(widgets, wid);
	return wid->w.button;
}

Text* GUI_CreateText(unsigned int id, char* text, SDL_Color color, int px, int py, int w, int h)
{
	GUI_Widget* wid = malloc(sizeof(GUI_Widget));
	wid->type = GUI_TEXT;
	wid->w.text = createText(id, text, color, px, py, w, h);
	list_append(widgets, wid);
	return wid->w.text;
}
