#include "gui/gui.h"

Queue* events = NULL;
List* widgets = NULL;

void GUI_Init()
{
	events = queue_init();
	widgets = list_init();
}

void GUI_Quit()
{
	/*list_destroy(widgets);
	queue_destroy(events);*/
}

void GUI_ProceedEvents(SDL_Event* event)
{
	Data* d = list_getData(widgets, 0);
	while(d != NULL)
	{
		d = d->next;
	}
}

int GUI_PollEvent(SDL_Event* event, GUI_Event* gui)
{
	
	GUI_ProceedEvents(event);
	if(!queue_size(events))
		return 0;
	else {
		*gui = *(GUI_Event*)queue_peek(events);
		queue_pop(events);
		return 1;
	}
}
