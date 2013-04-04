/*!
 *	\file map.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *	
 *	\brief Structures de données et fonctions de la carte
 */

#ifndef MAP_H
#define MAP_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "tools.h"
#include "image.h"

/**
 * \struct Map
 * \brief Représente une carte de jeu
 *
 * Comporte une texture, la couleur du noeud et une image ppm
 */
typedef struct _map{
	GLuint tex;
	Color3ub noeud;
	Image* ppm;
} Map;

/*!
 * \fn extern Map* loadMap(char const* map)
 * \brief Charge une carte de jeu
 *
 * \param map Chemin de la carte que l'on souhaite charger
  * \return Pointeur vers la carte si le chargement a réussi, NULL sinon.
 */
extern Map* loadMap(char const* map);

/*!
 * \fn extern void drawMap(Map* m)
 * \brief Dessine une carte de jeu
 *
 * \param m Carte que l'on souhaite dessiner
 */
extern void drawMap(Map* m);

/*!
 * \fn extern void deleteMap(Map* m)
 * \brief Supprime une carte de jeu
 *
 * \param m Carte que l'on souhaite supprimer
 */
extern void deleteMap(Map* m);


#endif