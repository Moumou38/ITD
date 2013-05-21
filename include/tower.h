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
#include "projectile.h"

/*!
 * \enum TYPE_TOWER
 * \brief Tous les types de Tours
 */
typedef enum{
	ROCKET,
	LASER,
	MACHINEGUN,
	HYBRID,
	DISABLED
} TYPE_TOWER;

const int Rocket_Dmg;
const int Laser_Dmg;
const int Machinegun_Dmg;
const int Hybrid_Dmg;

const int Rocket_Time;
const int Laser_Time;
const int Machinegun_Time;
const int Hybrid_Time;

/**
 * \struct Tower
 * \brief Représente une tour de défense
 *
 * Comporte une texture, des coordonnées, une taille, un type, le temps écoulé depuis le dernier tir et le monstre ciblé
 */
typedef struct {
	TYPE_TOWER type; 		/*!< Type */
	Position coord;  		/*!< Position */
	int size;				/*!< Taille*/
	float damages;			/*!< Dégâts */
	float range;			/*!< Portée */
	Monster* target;		/*!< Cible */
	Projectile* projectile; /*!< Projectile */
	GLuint tex;				/*!< Texture */
	int msecSinceLastShot;	/*!< Temps depuis le dernier tir*/
	int lastUpdate;			/*!< Temps depuis la dernière update*/
	int reloadTime;			/*!< Temps de rechargement de la tour*/
	int selected;			/*!< 1 si la tour est sélectionnée, 0 sinon */
	
	int offset;				/*!< Offset texture */
	int line;				/*!< Offset texture*/
	int animTimer;			/*!< Temps depuis la dernière animation */
	
} Tower;

/*!
 * \fn Tower* createTower(Position coord, TYPE_TOWER type)
 * \brief Création d'une tour
 *
 * \param coord Coordonnées de la tour
 * \param type Type de la tour à créer
 * \return Pointeur vers la tour si la création a réussi, NULL sinon.
 */
Tower* createTower(Position coord, TYPE_TOWER type);

/*!
 * \fn void drawTower(Tower* t)
 * \brief Dessine une tour
 *
 * \param t Pointeur vers la tour à créer
 */
void drawTower(Tower* t, Vector3 camPos);

/*!
 * \fn void drawTower2(TYPE_TOWER type, Position pos, float angle, int selected, Vector3 camPos, int offset, int line)
 * \brief Dessine une tour sans pointeur valide
 *
 * \param type Type de la tour
 * \param pos Position de la tour
 * \param selected 1 si la tour est sélectionnée, 0 sinon
 * \param camPos Vecteur représentant la position de la caméra
 * \param offset colonne de la texture
 * \param line ligne de la texture
 */
void drawTower2(TYPE_TOWER type, Position pos, int selected, Vector3 camPos, int offset, int line);

/*!
 * \fn void updateTower(Tower* t))
 * \brief Met à jour une tour
 *
 * \param t Pointeur vers la tour à mettre à jour
 */
void updateTower(Tower* t);

/*!
 * \fn void deleteTower(Tower* t)
 * \brief Supprime une tour
 *
 * \param t Pointeur vers la tour à supprimer
 */
void deleteTower(Tower* t);

/*!
 * \fn void lookForBestTarget(Tower* t,  List* monsters)
 * \brief Cherche la cible la plus proche
 *
 * \param t Pointeur vers la tour qui cherche une cible
 * \param monsters Liste de monstres présents dans le jeu
 */
void lookForBestTarget(Tower* t, List* monsters);

/*!
 * \fn Projectile* hasShot(Tower* t)
 * \brief Fait tirer la tour
 *
 * \param t Pointeur vers la tour qui tire
 *
 * \return Pointeur vers le projectile créé
 */
Projectile* hasShot(Tower* t);

/*!
 * \fn float damagesShot(Tower* t, Monster* target)
 * \brief Calcul les dégâts infligés par la tour
 *
 * \param t Pointeur vers la tour qui tire
 * \param target Pointeur vers le monstre ciblé.
 *
 * \return dégâts infligés.
 */
float damagesShot(Tower* t, Monster* target);

/*!
 * \fn int outOfRange(Position p1, Position p2, float range)
 * \brief Cherche si un élément est dans la portée d'un autre élément
 *
 * \param p1 Position du premier élément (par exemple la tour)
 * \param p2 Position du deuxième élément (par exemple le monstre)
 * \param range Portée de la tour
 * \return 1 si il est hors de la portée, 0 sinon.
 */
int outOfRange(Position p1, Position p2, float range);

/*!
 * \fn void onResumeTower(Tower* t)
 * \brief Fait reprendre la tour
 *
 * \param t Pointeur vers la tour
 */
void onResumeTower(Tower* t);

/*!
 * \fn int getTowerCost(TYPE_TOWER type)
 * \brief Donne le prix de la tour en fonction de son type
 *
 * \param type Type de la tour
 * \return Le prix de la tour
 */
int getTowerCost(TYPE_TOWER type);

/*!
 * \fn void selectTower(Tower* t, Position coord)
 * \brief Sélectionner une tour
 *
 * \param t Pointeur vers la tour
 * \param coord Position de la tour (coordonnées x et y)
 */
void selectTower(Tower* t, Position coord);

/*!
 * \fn Position getTowerSize(TYPE_TOWER type)
 * \brief Donne la taille de la tour en fonction de son type
 *
 * \param type Type de la tour
 * \return La taille en x et en y
 */
Position getTowerSize(TYPE_TOWER type);

/*!
 * \fn float getTowerRange(TYPE_TOWER type)
 * \brief Donne la portée de la tour en fonction de son type
 *
 * \param type Type de la tour
 * \return La portée de la tour
 */
float getTowerRange(TYPE_TOWER type);

/*!
 * \fn GLuint getTowerTexture(TYPE_TOWER type)
 * \brief Donne la texture de la tour en fonction de son type
 *
 * \param type Type de la tour
 * \return L'identifiant de la texture
 */
GLuint getTowerTexture(TYPE_TOWER type);

/*!
 * \fn const char* getTowerName(TYPE_TOWER type)
 * \brief Donne le nom de la tour en fonction de son type
 *
 * \param type Type de la tour
 * \return Le nom de la tour
 */
const char* getTowerName(TYPE_TOWER type);

/*!
 * \fn int collideWithTower(Tower* t, Position p, Position s)
 * \brief Vérifie si une tour de coordonnée p et taille s est en collision avec t.
 *
 * \param t Tour à tester
 * \param p position de la tour
 * \param s taille de la tour
 *
 * \return 1 si la tour est en collision avec t, 0 sinon.
 */
int collideWithTower(Tower* t, Position p, Position s);

#endif
