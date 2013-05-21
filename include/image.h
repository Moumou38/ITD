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
 * \fn GLuint loadTexture(SDL_Surface* tex)
 * \brief Charge une texture
 *
 * \param tex SDL_Surface à partir de laquelle on souhaite charger la texture
 * \return Entier pointant vers un espace mémoire sur la carte graphique
 */
GLuint loadTexture(SDL_Surface* tex);

/*!
 * \fn SDL_Surface* loadImage(char* image)
 * \brief Charge une image
 *
 * \param image Chemin de l'image que l'on veut charger
 * \return SDL_Surface contenant l'image que l'on a chargé
 */
SDL_Surface* loadImage(const char* image);

/*!
 * \fn void deleteImage(SDL_Surface* tex)
 * \brief Supprime une Image
 *
 * \param tex Pointeur vers la SDL_Surface à supprimer
 */
void deleteImage(SDL_Surface* tex);

/*!
 * \fn void deleteTexture(GLuint image)
 * \brief Supprime une texture
 *
 * \param tex Pointeur vers la zone mémoire de la carte graphique à supprimer
 */
void deleteTexture(GLuint image);

/*!
 * \fn void GetPixel(SDL_Surface* surface, int x, int y, Uint8* r, Uint8* g, Uint8* b, Uint8* a)
 * \brief Récupère le pixel
 *
 * \param surface Surface dont on veut récupérer le pixel
 * \param x Position en x du pixel
 * \param y Position en y du pixel
 * \param r Composante rouge du pixel
 * \param g Composante vert du pixel
 * \param b Composante bleu du pixel
 * \param a Composante alpha(transparence) du pixel
 */
void GetPixel(SDL_Surface* surface, int x, int y, Uint8* r, Uint8* g, Uint8* b, Uint8* a);

/*!
 * \fn SDL_Surface* filterImage(SDL_Surface* s, SDL_Color filter)
 * \brief Ajout d'un filtre de couleur sur une image
 *
 * \param s SDL_Surface à partir de laquelle on veut filtrer l'image
 * \param filter La couleur du filtre
 * \return La SDL_Surface résultante
 */
SDL_Surface* filterImage(SDL_Surface* s, SDL_Color filter);

/*!
 * \fn SDL_Surface* swapColorsImage(SDL_Surface* s, Color3ub old, Color3ub color)
 * \brief Echange les couleurs d'une image
 *
 * \param s SDL_Surface à partir de laquelle on souhaite échanger des couleurs
 * \param old Ancienne couleur
 * \param color Nouvelle couleur
 * \return La SDL_Surface résultante
 */
SDL_Surface* swapColorsImage(SDL_Surface* s, Color3ub old, Color3ub color);

#endif
