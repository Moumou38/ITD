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

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <limits.h>

#include "tools.h"
#include "image.h"

/**
 * \struct Map
 * \brief Représente une carte de jeu
 *
 * Comporte une texture, la couleur du noeud et une image ppm
 */
typedef struct {
	GLuint tex; 		/*!< Texture */
	Node* nodes;		/*!< Liste de nodes */
	SDL_Surface* ppm;	/*!< Image */
	Vector3 camPos;		/*!< Position de la caméra */
	Position camDir;	/*!< Mouvement de la caméra */
	int drawNodes;		/*!< Booléen de débogage. */
} Map;

/*!
 * \fn Map* loadMap(char const* map)
 * \brief Charge une carte de jeu
 *
 * \param map Chemin de la carte que l'on souhaite charger
  * \return Pointeur vers la carte si le chargement a réussi, NULL sinon.
 */
Map* loadMap(char const* map);

/*!
 * \fn void drawNode(Node* n, Vector3 camPos)
 * \brief Dessine un noeud sur la carte
 *
 * \param n Noeud que l'on souhaite dessiner
 */
void drawNode(Node* n, Vector3 camPos);

/*!
 * \fn void drawMap(Map* m)
 * \brief Dessine une carte de jeu
 *
 * \param m Carte que l'on souhaite dessiner
 */
void drawMap(Map* m);

/*!
 * \fn void deleteMap(Map* m)
 * \brief Supprime une carte de jeu
 *
 * \param m Carte que l'on souhaite supprimer
 */
void deleteMap(Map* m);

/*!
 * \fn int collideWithMap(Map* m, Position p, Position s)
 * \brief Vérifie si une tour de coordonnée p et taille s peut être placée
 *
 * \param m Carte du jeu
 * \param p position de la tour
 * \param s taille de la tour
 *
 * \return 1 si la tour est en collision avec la map, 0 sinon.
 */
int collideWithMap(Map* m, Position p, Position s, Vector3 camPos);

/*!
 * \fn void updateMap(Map* m)
 * \brief Met à jour une carte de jeu
 *
 * \param m Carte que l'on souhaite mettre à jour
 */
void updateMap(Map* m);

/*!
 * \fn void addCameraDirection(Map* m, Position pos)
 * \brief Ajoute une direction de mouvement à la caméra
 *
 * \param m Carte courante
 * \param pos Direction du mouvement de la caméra
 */
void addCameraDirection(Map* m, Position pos);

/*!
 * \fn void moveCamera(Map* m, Position pos)
 * \brief Déplace la caméra
 *
 * \param m Carte courante
 * \param pos Direction de déplacement de la caméra
 */
void moveCamera(Map* m, Position pos);

#endif
