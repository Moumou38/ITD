/*!
 *	\file projectile.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 20/05/13
 *	
 *	\brief Structures de données et fonctions des projectiles
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "resource.h"
#include "monster.h"
#include "tools.h"

/**
 * \struct Projectile
 * \brief Représente un projectile infligeant des dégâts
 */
typedef struct {
	Position pos; 	/*!< Position du projectile */
	Position size; 	/*!< Taille du projectile */
	GLuint tex; 	/*!< Texture du projectile */
	int line; 		/*!< Ligne d'animation */
	int offset; 	/*!< Colonne d'animation */
	int hit; 		/*!< 1 si le projectile a touché la cible, 0 sinon */
	int animTimer; 	/*!< Temps local d'animation */
	int lastUpdate; /*!< Temps local d'update */
	float damages; 	/*!< Dégâts du projectile */
	float speed; 	/*!< Vitesse du projectile */
	Monster* target;/*!< Cible du projectile */
} Projectile;

/*!
 * \fn Projectile* createProjectile(Position pos, Position size, float damages, int line, float speed, Monster* target)
 * \brief Création d'une tour
 *
 * \param pos Position initiale du projectile
 * \param size Taille du projectile
 * \param damages Dégâts infligés par le projectile
 * \param line Offset texture
 * \param speed Vitesse du projectile
 * \param target pointeur vers la cible
 * \return Pointeur vers le nouveau projectile.
 */
Projectile* createProjectile(Position pos, Position size, float damages, int line, float speed, Monster* target);

/*!
 * \fn void deleteProjectile(Projectile* p)
 * \brief Supprime un projectile
 *
 * \param p Pointeur vers le projectile
 */
void deleteProjectile(Projectile* p);

/*!
 * \fn void drawProjectile(Projectile* p, Vector3 camPos)
 * \brief Dessine un projectile
 *
 * \param p Pointeur vers le projectile
 * \param camPos position de la caméra
 */
void drawProjectile(Projectile* p, Vector3 camPos);

/*!
 * \fn void updateProjectile(Projectile* p)
 * \brief Mise à jour d'un projectile
 *
 * \param p pointeur vers le projectile à mettre à jour
 */
void updateProjectile(Projectile* p);

#endif
