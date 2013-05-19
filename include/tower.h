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

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <SDL/SDL.h>

#include "list.h"
#include "tools.h"
#include "monster.h"
#include "resource.h"

/*!
 * \enum TYPE_TOWER
 * \brief Tous les types de Tours
 */
typedef enum{
	ROCKET,
	LASER,
	MACHINEGUN,
	HYBRID
} TYPE_TOWER;

extern const int Rocket_Dmg;
extern const int Laser_Dmg;
extern const int Machinegun_Dmg;
extern const int Hybrid_Dmg;

extern const int Rocket_Time;
extern const int Laser_Time;
extern const int Machinegun_Time;
extern const int Hybrid_Time;

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
	float damages;
	float range;
	TYPE_TOWER type;
	int msecSinceLastShot;
	int lastUpdate;
	int reloadTime;
	int selected;
	float angle;
	Monster* target;
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
extern void drawTower(Tower* t, Position camPos);

extern void drawTower2(TYPE_TOWER type, Position pos, float angle, int selected, Position camPos);
/*!
 * \fn extern void updateTower(Tower* t))
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

/*!
 * \fn extern void lookForBestTarget(Tower* t,  List* monsters)
 * \brief Cherche la cible la plus proche
 *
 * \param t Pointeur vers la tour qui cherche une cible
 * \param monsters Liste de monstres présents dans le jeu
 */
extern void lookForBestTarget(Tower* t, List* monsters);

/*!
 * \fn extern void shoot(Tower* t, Monster* target)
 * \brief 
 *
 * \param t Pointeur vers la tour qui tire
 * \param target Pointeur vers le monstre ciblé
 */
extern void shoot(Tower* t, Monster* target);

extern int outOfRange(Position p1, Position p2, float range);

extern void onResumeTower(Tower* t);

extern int getTowerCost(TYPE_TOWER type);

extern void selectTower(Tower* t, Position coord);

extern Position getTowerSize(TYPE_TOWER type);

extern float getTowerRange(TYPE_TOWER type);

extern GLuint getTowerTexture(TYPE_TOWER type);

/*!
 * \fn extern int collideWithTower(Tower* t, Position p, Position s)
 * \brief Vérifie si une tour de coordonnée p et taille s est en collision avec t.
 *
 * \param t Tour à tester
 * \param p position de la tour
 * \param s taille de la tour
 *
 * \return 1 si la tour est en collision avec t, 0 sinon.
 */
extern int collideWithTower(Tower* t, Position p, Position s);

#endif
