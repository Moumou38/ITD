/*!
 *	\file tower.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *	
 *	\brief Structures de données et fonctions des tours
 */

#ifndef TOWER_H
#define TOWER_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "tools.h"
#include "monster.h"

/*!
 * \enum TYPE_TOWER
 * \brief Tous les types de Tours
 */
typedef enum{
	ROCKET,
	LASER,
	MISTRALLETTES,
	HYBRIDES
} TYPE_TOWER;


/**
 * \struct Tower
 * \brief Représente une tour de défense
 *
 * Comporte une texture, des coordonnées, une taille, un type, le temps écoulé depuis le dernier tir et le monstre ciblé
 */
typedef struct _tower{
	GLuint tex;
	Position coord;
	int size;
	TYPE_TOWER type;
	GLuint msecSinceLastShot;
	Monster target;
} Tower;

/*!
 * \fn extern Tower* createTower(Position coord, TYPE_TOWER type)
 * \brief Création d'une tour
 *
 * \param coord Coordonnées de la tour
 * \param type Type de la tour à créer
 * \return Pointeur vers la tour si la création a réussi, NULL sinon.
 */
extern Tower* createTower(Position coord, TYPE_TOWER type);

/*!
 * \fn extern void drawTower(Tower* t)
 * \brief Dessine une tour
 *
 * \param t Pointeur vers la tour à créer
 */
extern void drawTower(Tower* t);

/*!
 * \fn extern void updateTower(Tower* t)
 * \brief Met à jour une tour
 *
 * \param t Pointeur vers la tour à mettre à jour
 */
extern void updateTower(Tower* t);

/*!
 * \fn extern void deleteTower(Tower* t)
 * \brief Supprime une tour
 *
 * \param t Pointeur vers la tour à supprimer
 */
extern void deleteTower(Tower* t);


#endif