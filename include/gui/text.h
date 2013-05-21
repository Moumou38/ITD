/*!
 *	\file text.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 24/04/13
 *	
 *	\brief Structures de données et fonctions du text
 */

#ifndef TEXT_H
#define TEXT_H

#if defined __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "tools.h"
#include "image.h"
#include "gui/enums.h"

/*!
 * \enum FONT_SIZE
 * \brief Différentes tailles de police
 */
typedef enum {
	FONT_8,		/*!< Taille 8 */
	FONT_12,	/*!< Taille 12 */
	FONT_24,	/*!< Taille 24 */
	FONT_32,	/*!< Taille 32 */
	FONT_48,	/*!< Taille 48 */
	MAX_FONTS	/*!< nombre max de polices */
} FONT_SIZE;

/**
 * \struct Text
 * \brief Représente un texte
 * 
 */
typedef struct {
	unsigned int id;	/*!< identifiant */
	unsigned int type;	/*!< GUI_TEXT */
	char* text;			/*!< texte */
	GLuint tex[1];		/*!< texture */
	Position pos;		/*!< position */
	Position size;		/*!< taille */
	SDL_Color color;	/*!< Couleur  */
	TTF_Font* font;		/*!< Police */
} Text;


TTF_Font *polices[MAX_FONTS];

/*!
 * \fn void Text_Init()
 * \brief Initialise le module d'écriture de texte.
 *
 */
void Text_Init();

/*!
 * \fn void Text_Quit()
 * \brief ferme le module d'écriture de texte.
 *
 */
void Text_Quit();

/*!
 * \fn Text* createText(unsigned int id, char* text, SDL_Color color, int px, int py, FONT_SIZE size)
 * \brief Créé un widget de texte.
 *
 * \param id	identifiant du nouveau texte
 * \param text	texte affiché
 * \param color	couleur du texte
 * \param px	position x du texte
 * \param py	position y du texte
 * \param size	taille de la police
 * \return Pointeur vers un widget de texte valide.
 */
Text* createText(unsigned int id, char* text, SDL_Color color, int px, int py, FONT_SIZE size);

/*!
 * \fn void setText(Text* t, const char* text)
 * \brief Modifie un texte
 *
 * \param t Pointeur vers le texte à modifier
 * \param text Nouveau texte
 */
void setText(Text* t, const char* text);

/*!
 * \fn void drawText(Text* t)
 * \brief Dessine un texte
 *
 * \param t Pointeur vers le texte à dessiner
 */
void drawText(Text* t);

/*!
 * \fn void removeText(Text* t)
 * \brief Supprime un texte
 *
 * \param t Pointeur vers le texte à supprimer
 */
void removeText(Text* t);

#endif
