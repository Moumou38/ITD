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
#include <SDL/SDL_image.h>

#include "tools.h"
#include "image.h"
#include "gui/enums.h"

/*!
 * \enum ButtonState
 * \brief Différents états des boutons
 */
typedef enum {
	BS_DEFAULT = 0,
	BS_HOVER = 1,
	BS_PRESSED = 2,
	BS_DISABLED = 3
} ButtonState;

/*!
 * \enum ButtonFlags
 * \brief 
 */
typedef enum {
	BF_NONE = 0x0000,
	BF_MOVABLE = 0x0001,
	BF_ENABLED = 0x0010,
} ButtonFlags;

/**
 * \struct Button
 * \brief Représente un bouton
 *
 * 
 */
typedef struct {
	unsigned int id;
	unsigned int type;
	char* text;
	GLuint tex[4];
	Position pos, size;
	ButtonState state;
	ButtonFlags flags;
} Button;

/*!
 * \fn Button* createButton(unsigned int id, char* text, char* image, SDL_Color color, int px, int py, int w, int h)
 * \brief Créer un bouton
 *
 * \param id
 * \param text
 * \param image
 * \param color
 * \param px
 * \param py
 * \param w
 * \param h
 * \return Le bouton créé
 */
Button* createButton(unsigned int id, char* text, char* image, SDL_Color color, int px, int py, int w, int h);

/*!
 * \fn Button* createEmptyButton(GLuint color)
 * \brief Créer un bouton vide
 *
 * \param color Couleur du bouton
 * \return Le bouton créé
 */
Button* createEmptyButton(GLuint color);

/*!
 * \fn void drawButton(Button* b)
 * \brief Dessine un bouton
 *
 * \param b Pointeur vers le bouton à dessiner
 */
void drawButton(Button* b);

/*!
 * \fn int injectEventToButton(Button* b, SDL_Event* event, GUI_ButtonEvent* guiEv)
 * \brief Ajoute un événement sur un bouton
 *
 * \param b Bouton sur lequel on veut ajouter un événement 
 * \param event Evénement à ajouter au bouton
 * \param guiEv
 * \return 
 */
int injectEventToButton(Button* b, SDL_Event* event, GUI_ButtonEvent* guiEv);

/*!
 * \fn int hoverButton(Button* b, Position p)
 * \brief Action au survol du bouton
 *
 * \param b Bouton cible
 * \param p 
 * \return 
 */
int hoverButton(Button* b, Position p);

/*!
 * \fn int clickedButton(Button* b, Position p, int pressed)
 * \brief 
 *
 * \param b 
 * \param p 
 * \param pressed 
 * \return 
 */
int clickedButton(Button* b, Position p, int pressed);

/*!
 * \fn int isButtonClicked(Button* b)
 * \brief 
 *
 * \param b
 * \return 
 */
int isButtonClicked(Button* b);

/*!
 * \fn void removeButton(Button* b)
 * \brief Supprimer un bouton
 *
 * \param b Pointeur vers le bouton à supprimer
 */
void removeButton(Button* b);

/*!
 * \fn int mouseInButton(Button* b, Position p)
 * \brief 
 *
 * \param b
 * \param p
 * \return 
 */
int mouseInButton(Button* b, Position p);

/*!
 * \fn void enableButtonFlag(Button* b, ButtonFlags flags)
 * \brief
 *
 * \param b
 * \param flags
 */
void enableButtonFlag(Button* b, ButtonFlags flags);

/*!
 * \fn void disableButtonFlag(Button* b, ButtonFlags flags)
 * \brief
 *
 * \param b
 * \param flags
 */
void disableButtonFlag(Button* b, ButtonFlags flags);

#endif
