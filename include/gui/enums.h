/*!
 *	\file enums.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 10/04/13
 *	
 *	\brief Enumération et structures de données de la GUI
 */

#ifndef GUI_ENUMS
#define GUI_ENUMS

/*!
 * \enum GUI_EventType
 * \brief Type d'évènement GUI.
 */
typedef enum {
	GUI_NONE,
	GUI_ET_BUTTON,
	GUI_ET_TEXT,
	GUI_ET_TEXTAREA
} GUI_EventType;

/*!
 * \enum GUI_WidgetType
 * \brief Type de widget
 */
typedef enum {
	GUI_BUTTON,
	GUI_TEXT,
	GUI_TEXTAREA,
	GUI_IMAGE
} GUI_WidgetType;

/*!
 * \enum GUI_EventButtonAction
 * \brief Type d'évènement déclenché par un bouton
 */
typedef enum {
	GUI_BTEV_HOVER,
	GUI_BTEV_LEFTHOVER,
	GUI_BTEV_PRESSED,
	GUI_BTEV_RELEASED,
	GUI_BTEV_MOVED,
	GUI_BTEV_NONE
} GUI_EventButtonAction;


/**
 * \struct GUI_ButtonEvent
 * \brief Evènement déclenché par un bouton
 *
 */
typedef struct {
	GUI_EventType type;
	unsigned int id;
	GUI_EventButtonAction action;
} GUI_ButtonEvent;

/* Text */
/*!
 * \enum GUI_EventTextAction
 * \brief Type d'évènement déclenché par un texte
 */
typedef enum {
	GUI_TXEV_HOVER,
	GUI_TXEV_LEFTHOVER,
	GUI_TXEV_PRESSED,
	GUI_TXEV_RELEASED,
	GUI_TXEV_MOVED,
	GUI_TXEV_NONE
} GUI_EventTextAction;

/**
 * \struct GUI_TextEvent
 * \brief Evènement déclenché par un texte
 */
typedef struct {
	GUI_EventType type;
	unsigned int id;
	GUI_EventTextAction action;
} GUI_TextEvent;

/*!
 * \union GUI_Event
 * \brief Evènement déclenché par l'interface utilisateur.
 */
typedef union {
	GUI_EventType type;
	GUI_ButtonEvent button;
	GUI_TextEvent text;
} GUI_Event;

#endif
