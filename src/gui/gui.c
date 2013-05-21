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
	if(events == NULL && widgets == NULL) {
		events = queue_init();
		widgets = list_init();
		Text_Init();	
		//printf("GUI initialized\n");
	}
}

void GUI_Quit()
{
	GUI_Clear();
	Text_Quit();
	list_delete(widgets);
	queue_delete(events);
}

void GUI_DrawAll()
{
	GUI_Draw(0);
}

void GUI_Draw(int level)
{
	Data* d = list_getData(widgets, 0);
	while(d != NULL)
	{
		GUI_Widget* w = (GUI_Widget*)d->value;
		if(level == 0 || (w->level & level)) {		
			switch(w->type) {
				case GUI_BUTTON:
						drawButton(w->w.button);
					break;
				case GUI_TEXT:
						drawText(w->w.text);
					break;
				case GUI_IMAGE:
						drawImage(w->w.image);
					break;
				default:
					break;
			}
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
			case GUI_IMAGE:
					removeImage(w->w.image);
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

void GUI_ClearEvents()
{
	GUI_Event ev;
	while(GUI_PollEvent(&ev));
}

void GUI_RegisterButton(Button* b)
{
	GUI_Widget* w = malloc(sizeof(GUI_Widget));
	w->type = GUI_BUTTON;
	w->w.button = b;
	w->id = 0;
	list_append(widgets, w);
}

Button* GUI_CreateButton(unsigned int id, int level, char* text, char* image, SDL_Color color, int px, int py, int w, int h)
{
	GUI_Widget* wid = malloc(sizeof(GUI_Widget));
	wid->type = GUI_BUTTON;
	wid->level = level;
	wid->id = id;
	wid->w.button = createButton(id, text, image, color, px, py, w, h);
	list_append(widgets, wid);
	return wid->w.button;
}

Text* GUI_CreateText(unsigned int id, int level, char* text, SDL_Color color, int px, int py, FONT_SIZE size)
{
	GUI_Widget* wid = malloc(sizeof(GUI_Widget));
	wid->type = GUI_TEXT;
	wid->level = level;
	wid->id = id;
	wid->w.text = createText(id, text, color, px, py, size);
	list_append(widgets, wid);
	return wid->w.text;
}

Image* GUI_CreateImage(unsigned int id, int level, const char* image, int px, int py, float sizex, float sizey)
{
	GUI_Widget* wid = malloc(sizeof(GUI_Widget));
	wid->type = GUI_IMAGE;
	wid->level = level;
	wid->id = id;
	wid->w.image = createImage(id, image, px, py, sizex, sizey);
	list_append(widgets, wid);
	return wid->w.image;
}

GUI_Widget* GUI_GetWidget(unsigned int id)
{
	int i;
	for(i = 0; i<list_size(widgets); i++)
	{
		GUI_Widget* w = list_get(widgets, i);
		if(w->id == id)
			return w;
	}
	return NULL;
}

void GUI_RemoveWidget(unsigned int id)
{
	int i;
	for(i = 0; i<list_size(widgets); i++)
	{
		GUI_Widget* w = list_get(widgets, i);
		if(w->id == id)
		{
			switch(w->type) {
			case GUI_BUTTON:
					removeButton(w->w.button);
				break;
			case GUI_TEXT:
					removeText(w->w.text);
				break;
			case GUI_IMAGE:
					removeImage(w->w.image);
				break;
			default:
				break;
			}
			list_remove(widgets, i);
			break;
		}
	}
}
