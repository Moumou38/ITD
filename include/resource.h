/*!
 *	\file resource.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 13/05/13
 *	
 *	\brief Structures de données et fonctions du gestionnaire de ressources
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <string.h>

#include "list.h"
#include "image.h"

/**
 * \struct Resource
 * \brief Stocke un identifiant de texture et le chemin de l'image.
 *
 */
typedef struct {
	char* name;		/*!< nom de la resource */
	GLuint data;	/*!< identifiant de texture */
} Resource;

/*!
 * \fn GLuint getTexture(const char* name)
 * \brief Donne la texture en fonction de son nom
 *
 * \param type Nom de la texture
 * \return L'identifiant de la texture
 */
GLuint getTexture(const char* name);

/*!
 * \fn void initResourcesManager()
 * \brief Initialise le gestionnaire de ressources
 */
void initResourcesManager();

/*!
 * \fn void deleteResourcesManager()
 * \brief Supprime le gestionnaire de ressources
 */
void deleteResourcesManager();

#endif
