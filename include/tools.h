/*!
 *	\file tools.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *	
 *	\brief Structures de données et fonctions des outils nécessaires
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#define EPSILON 2

#define MAP_WIDTH 600
#define MAP_HEIGHT 550

/**
 * \struct Color3ub
 * \brief Représente une couleur RGB sur 24bits..
 *
 * Comporte 3 canaux pour les 3 composantes de la couleur.
 */
typedef struct _color3ub{
	unsigned char r; /*!< Canal rouge */
	unsigned char g; /*!< Canal vert */
	unsigned char b; /*!< Canal bleu */
} Color3ub;

/**
 * \struct Position
 * \brief Représente une position
 *
 * Comporte une position en x (abscisse) et une position en y (ordonnée)
 */
typedef struct _position{
	float x;
	float y;
} Position;

/**
 * \struct Node
 * \brief Représente une liste de noeuds
 *
 * Comporte une couleur, une position et un pointeur vers son suivant
 */
typedef struct _node{
	Color3ub color, path;
	Position coord;
	struct _node* next;
} Node;

/**
 * \fn void freeList(Node** node)
 * \brief Libère la mémoire utilisée pour la liste de Node
 *
 * \param node Pointeur vers la tête de la liste de node
 */
void freeList(Node** node);

#endif
