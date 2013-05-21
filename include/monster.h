/*!
 *	\file monster.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *	
 *	\brief Structures de données et fonctions des monstres
 */

#ifndef MONSTER_H
#define MONSTER_H

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <SDL/SDL.h>

#include "tools.h"
#include "resource.h"

/*!
 * \enum TYPE_MONSTER
 * \brief Tous les types de Monstres
 */
typedef enum{
	NORMAL,
	FAST,
	SLOW,
	FLYER
} TYPE_MONSTER;

const float Normal;
const float Fast;
const float Slow;
const float Flyer;

/**
 * \struct ResistTower
 * \brief Représente la résistance d'un monstre pour chaque type de tour
 *
 * Comporte la résistance pour la tour Rocket, pour la tour Hybrid, pour la tour Machinegun et pour la tour Laser.
 */
typedef struct 
{
	float resistRocket;		/*!< Coefficient de résistance aux rockets */
	float resistHybrid;		/*!< Coefficient de résistance aux hybrids */
	float resistMachinegun;	/*!< Coefficient de résistance aux machineguns */
	float resistLaser;		/*!< Coefficient de résistance aux lasers */
}ResistTower;

/**
 * \struct Monster
 * \brief Représente un monstre ennemi
 *
 * Comporte des points de vie, une texture, un type, des coordonnées, une direction et le temps écoulé depuis le dernier mouvement
 */
typedef struct {
	int life;				/*!< Vie */
	int life_max;			/*!< Vie max */
	GLuint tex;				/*!< Texture */
	TYPE_MONSTER type;		/*!< Type */
	Position coord;			/*!< Position */
	Position size;			/*!< Taille*/
	Node* direction;		/*!< Direction */
	int msecSinceLastMvt;	/*!< Temps depuis la dernière update*/
	int deltaOnPause;		/*!< Temps à la pause */
	int invulnerable;		/*!< Booléen invulnérabilité*/
	float mvtTime;			/*!< Vitesse de mouvement */
	ResistTower resist;		/*!< Résistance aux tours */
	float animOffset;		/*!< Offset de texture */
	Uint32 animTimer;		/*!< Temps d'animation */
	int animUp;				/*!< Direction d'animation */
} Monster;

/*!
 * \fn Monster* createMonster(TYPE_MONSTER type, Node* start)
 * \brief Création d'un monstre
 *
 * \param type Type du monstre à créer
 * \param start Noeud de départ du monstre
 * \return Pointeur vers le monstre si la création a réussi, NULL sinon.
 */
Monster* createMonster(TYPE_MONSTER type, float life, Node* start, GLint timer);

/*!
 * \fn void drawMonster(Monster* m, Position camPos)
 * \brief Dessine un monstre
 *
 * \param m Pointeur vers le monstre à créer
 */
void drawMonster(Monster* m, Vector3 camPos);

/*!
 * \fn void updateMonster(Monster* m)
 * \brief Met à jour un monstre
 *
 * \param m Pointeur vers le monstre à mettre à jour
 */
 void updateMonster(Monster* m);

/*!
 * \fn int hasFinishedMonster(Monster* m)
 * \brief Détermine si un monstre a terminé le parcours
 *
 * \param m Pointeur vers le monstre
 */
int hasFinishedMonster(Monster* m);

/*!
 * \fn void onPauseMonster(Monster* m)
 * \brief Met en pause un monstre
 *
 * \param m Pointeur vers le monstre
 */
void onPauseMonster(Monster* m);

/*!
 * \fn void onResumeMonster(Monster* m)
 * \brief Fait reprendre le monstre
 *
 * \param m Pointeur vers le monstre
 */
void onResumeMonster(Monster* m);

/*!
 * \fn void deleteMonster(Monster* m)
 * \brief Supprime un monstre
 *
 * \param m Pointeur vers le monstre à supprimer
 */
void deleteMonster(Monster* m);

/*!
 * \fn int isDead(Monster* m)
 * \brief Défini si le monstre est vivant ou non
 *
 * \param m Pointeur vers le monstre à supprimer
 * \return 1 si le monstre est mort, 0 sinon
 */
int isDead(Monster* m);

#endif
