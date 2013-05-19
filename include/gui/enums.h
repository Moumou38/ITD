#ifndef GUI_ENUMS
#define GUI_ENUMS


typedef enum {
	GUI_NONE,
	GUI_ET_BUTTON,
	GUI_ET_TEXT,
	GUI_ET_TEXTAREA
} GUI_EventType;

typedef enum {
	GUI_BUTTON,
	GUI_TEXT,
	GUI_TEXTAREA,
	GUI_IMAGE
} GUI_WidgetType;

/* Buttons */
typedef enum {
	GUI_BTEV_HOVER,
	GUI_BTEV_LEFTHOVER,
	GUI_BTEV_PRESSED,
	GUI_BTEV_RELEASED,
	GUI_BTEV_MOVED,
	GUI_BTEV_NONE
} GUI_EventButtonAction;

typedef struct {
	GUI_EventType type;
	unsigned int id;
	GUI_EventButtonAction action;
} GUI_ButtonEvent;

/* Text */
typedef enum {
	GUI_TXEV_HOVER,
	GUI_TXEV_LEFTHOVER,
	GUI_TXEV_PRESSED,
	GUI_TXEV_RELEASED,
	GUI_TXEV_MOVED,
	GUI_TXEV_NONE
} GUI_EventTextAction;

typedef struct {
	GUI_EventType type;
	unsigned int id;
	GUI_EventTextAction action;
} GUI_TextEvent;

typedef union {
	GUI_EventType type;
	GUI_ButtonEvent button;
	GUI_TextEvent text;
} GUI_Event;

#endif
