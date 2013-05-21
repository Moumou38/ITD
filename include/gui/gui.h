/*!
 *	\file gui.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 10/04/13
 *	
 *	\brief 
 */

#ifndef GUI_H
#define GUI_H

#include <SDL/SDL.h>
#include "list.h"
#include "queue.h"
#include "gui/button.h"
#include "gui/text.h"
#include "gui/gui_image.h"

/**
 * \struct GUI_Widget
 * \brief Représente un widget
 *
 */
typedef struct {
	GUI_WidgetType type; 	/*!< type du widget */
	int level;				/*!< Niveau de dessin */
	int id;					/*!< Identifiant du widget */
	union {
		Button *button;		/*!< Pointeur vers un bouton */
		Text *text;			/*!< Pointeur vers un texte */
		Image *image;		/*!< Pointeur vers une image */
	} w;
} GUI_Widget;

/*!
 * \fn GUI_Event* createGuiEvent()
 * \brief Créé un évènement de gui.
 *
 * \return pointeur vers un GUI_Event valide
 */
GUI_Event* createGuiEvent();

/*!
 * \fn void GUI_Init()
 * \brief initialise le module GUI
 *
 */
void GUI_Init();

/*!
 * \fn void GUI_Quit()
 * \brief détruit le module GUI
 *
 */
void GUI_Quit();

/*!
 * \fn void GUI_DrawAll()
 * \brief dessine l'intégralité des widgets enregistrés
 *
 */
void GUI_DrawAll();

/*!
 * \fn void GUI_Draw(int level)
 * \brief dessine le niveau de widgets demandé
 *
 * \param level niveau à dessiner, 0 pour tous les dessiner.
 */
void GUI_Draw(int level);

/*!
 * \fn void GUI_Clear()
 * \brief détruit tous les widgets enregistés.
 *
 */
void GUI_Clear();

/*!
 * \fn void GUI_ProceedEvents(SDL_Event* event)
 * \brief Teste si l'évènement event déclenche un évènement GUI.
 *
 * \param event évènement SDL à vérifier
 */
void GUI_ProceedEvents(SDL_Event* event);

/*!
 * \fn int GUI_PollEvent(GUI_Event* gui)
 * \brief Remplis un GUI_Event des informations du premier évènement GUI dans la file.
 *
 * \param gui évènement GUI à remplir
 * \return 1 si un évènement GUI a eu lieu, 0 sinon
 */
int GUI_PollEvent(GUI_Event* gui); 

void GUI_ClearEvents();

/*!
 * \fn Button* GUI_CreateButton(unsigned int id, int level, char* text, char* image, SDL_Color color, int px, int py, int w, int h)
 * \brief Créé un bouton cliquable.
 *
 * \param id		identifiant
 * \param level		niveau de dessin
 * \param text		texte
 * \param image		image 
 * \param color		couleur du texte
 * \param px		position x
 * \param py		position y
 * \param w			taille w
 * \param h			taille h
 * \return Pointeur vers le bouton créé.
 */
Button* GUI_CreateButton(unsigned int id, int level, char* text, char* image, SDL_Color color, int px, int py, int w, int h);

/*!
 * \fn Text* GUI_CreateText(unsigned int id, int level, char* text, SDL_Color color, int px, int py, FONT_SIZE size)
 * \brief Créé un widget Texte
 *
 * \param id		identifiant
 * \param level		niveau de dessin
 * \param text		texte
 * \param color		couleur du texte
 * \param px		position x
 * \param py		position y
 * \param size		taille de la police
 * \return Pointeur vers le texte créé.
 */
Text* GUI_CreateText(unsigned int id, int level, char* text, SDL_Color color, int px, int py, FONT_SIZE size);

/*!
 * \fn Image* GUI_CreateImage(unsigned int id, int level, const char* image, int px, int py, float sizex, float sizey)
 * \brief Créé un widget Image.
 *
 * \param id		identifiant
 * \param level		niveau de dessin
 * \param text		texte
 * \param px		position x
 * \param py		position y
 * \param sizex		taille de l'image en largeur (1 = 100%)
 * \param sizey		taille de l'image en hauteur(1 = 100%)
 * \return Pointeur vers l'image créée.
 */
Image* GUI_CreateImage(unsigned int id, int level, const char* image, int px, int py, float sizex, float sizey);

/*!
 * \fn GUI_Widget* GUI_GetWidget(unsigned int id)
 * \brief récupère le widget ayant l'identifiant id.
 *
 * \param id	identifiant du widget 
 * \return Pointeur vers le widget demandé.
 */
GUI_Widget* GUI_GetWidget(unsigned int id);

/*!
 * \fn void GUI_RemoveWidget(unsigned int id)
 * \brief supprime le widget ayant l'identifiant id.
 *
 * \param id	identifiant du widget
 */
void GUI_RemoveWidget(unsigned int id);

#endif
