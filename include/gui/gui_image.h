/*!
 *	\file gui_image.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 10/04/13
 *	
 *	\brief 
 */

#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#if defined __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "tools.h"
#include "image.h"
#include "gui/enums.h"

/**
 * \struct Image
 * \brief Element image.
 *
 */
typedef struct {
	unsigned int id;	/*!< identifiant */
	unsigned int type;	/*!< GUI_IMAGE */
	GLuint tex[1];		/*!< texture */
	Position pos;		/*!< Position */
	Position size;		/*!< Taille */
} Image;

/*!
 * \fn Image* createImage(unsigned int id, const char* image, int px, int py, float sizex, float sizey)
 * \brief Créer une image
 *
 * \param id		identifiant
 * \param image		chemin de l'image
 * \param px		position x
 * \param py		position y
 * \param sizex		taille en largeur (1 = 100%)
 * \param sizey		taille en hauteur (1 = 100%)
 * \return 
 */
Image* createImage(unsigned int id, const char* image, int px, int py, float sizex, float sizey);

/*!
 * \fn void drawImage(Image* t)
 * \brief Dessine une image
 *
 * \param t Pointeur vers l'image à dessiner
 */
void drawImage(Image* t);

/*!
 * \fn void removeImage(Image* t)
 * \brief Supprime une image
 *
 * \param t Pointeur vers l'image à supprimer
 */
void removeImage(Image* t);

#endif
