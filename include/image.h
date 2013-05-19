/*!
 *	\file image.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *	
 *	\brief Structures de données et fonctions de l'image ppm
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

 #ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "tools.h"

/*!
 * \fn extern GLuint loadTexture(SDL_Surface* tex)
 * \brief Charge une texture
 *
 * \param tex SDL_Surface à partir de laquelle on souhaite charger la texture
 * \return Entier pointant vers un espace mémoire sur la carte graphique
 */
extern GLuint loadTexture(SDL_Surface* tex);

/*!
 * \fn extern SDL_Surface* loadImage(char* image)
 * \brief Charge une image
 *
 * \param image Chemin de l'image que l'on veut charger
 * \return SDL_Surface contenant l'image que l'on a chargé
 */
extern SDL_Surface* loadImage(const char* image);

/*!
 * \fn extern void deleteImage(SDL_Surface* tex)
 * \brief Supprime une Image
 *
 * \param tex Pointeur vers la SDL_Surface à supprimer
 */
extern void deleteImage(SDL_Surface* tex);

/*!
 * \fn extern void deleteTexture(GLuint image)
 * \brief Supprime une texture
 *
 * \param tex Pointeur vers la zone mémoire de la carte graphique à supprimer
 */
extern void deleteTexture(GLuint image);

extern SDL_Surface* filterImage(SDL_Surface* s, SDL_Color filter);

extern SDL_Surface* paintImage(SDL_Surface* s, Color3ub color);

#endif
