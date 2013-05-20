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

extern const float Normal;
extern const float Fast;
extern const float Slow;
extern const float Flyer;

typedef struct _resist
{
	float resistRocket;
	float resistHybrid;
	float resistMachinegun;
	float resistLaser;
}ResistTower;
/**
 * \struct Monster
 * \brief Représente un monstre ennemi
 *
 * Comporte des points de vie, une texture, un type, des coordonnées, une direction et le temps écoulé depuis le dernier mouvement
 */
typedef struct _monster{
	int life;
	int life_max;
	GLuint tex;
	TYPE_MONSTER type;
	Position coord;
	Position size;
	Node* direction;
	int msecSinceLastMvt;
	int deltaOnPause;
	int invulnerable;
	float mvtTime;
	ResistTower resist;
	float animOffset;
	Uint32 animTimer;
	int animUp;
} Monster;

/*!
 * \fn extern Monster* createMonster(TYPE_MONSTER type, Node* start)
 * \brief Création d'un monstre
 *
 * \param type Type du monstre à créer
 * \param start Noeud de départ du monstre
 * \return Pointeur vers le monstre si la création a réussi, NULL sinon.
 */
extern Monster* createMonster(TYPE_MONSTER type, float life, Node* start, GLint timer);

/*!
 * \fn extern void drawMonster(Monster* m, Position camPos)
 * \brief Dessine un monstre
 *
 * \param m Pointeur vers le monstre à créer
 */
extern void drawMonster(Monster* m, Vector3 camPos);

/*!
 * \fn extern void updateMonster(Monster* m)
 * \brief Met à jour un monstre
 *
 * \param m Pointeur vers le monstre à mettre à jour
 */
extern void updateMonster(Monster* m);

/*!
 * \fn extern int hasFinishedMonster(Monster* m)
 * \brief Détermine si un monstre a terminé le parcours
 *
 * \param m Pointeur vers le monstre
 */
extern int hasFinishedMonster(Monster* m);

extern void onPauseMonster(Monster* m);

extern void onResumeMonster(Monster* m);

/*!
 * \fn extern void deleteMonster(Monster* m)
 * \brief Supprime un monstre
 *
 * \param m Pointeur vers le monstre à supprimer
 */
extern void deleteMonster(Monster* m);

extern int isDead(Monster* m);

#endif
