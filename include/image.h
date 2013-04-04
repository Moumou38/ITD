/*!
 *	\file image.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *	
 *	\brief Structures de données et fonctions de l'image ppm
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * \struct Image
 * \brief Représente un tableau de pixels
 *
 * Comporte la taille de l'image (h,w) et un tableau de pixels de taille h*w
 */
typedef struct {
	unsigned int h; /*!< Hauteur de l'image */
	unsigned int w; /*!< Largeur de l'image */
	Pixel* pixels; /*!< Données de l'image */
	char* name; /*!< Chemin de l'image */
} Image;

/*!
 * \fn extern Image* openImage(const char* src)
 * \brief Ouvre une Image
 *
 * \param src Chemin de l'Image que l'on souhaite ouvrir
 */
extern Image* openImage(const char* src);

/*!
 * \fn extern void saveImage(Image* img, const char* file)
 * \brief Sauvegarde une Image
 *
 * \param img Pointeur vers l'Image
 * \param file Chemin du fichier où l'on veut sauvegarder
 */
extern void saveImage(Image* img, const char* file);

/*!
 * \fn extern void deleteImage(Image* img)
 * \brief Supprime une Image
 *
 * \param img Pointeur vers l'Image à supprimer
 */
extern void deleteImage(Image* img);

/*!
 * \fn extern Image* createBlankImage(int w, int h)
 * \brief Créé une Image blanche
 *
 * \param w Largeur de l'Image
 * \param h Hauteur de l'Image
 * \return Pointeur vers l'image blanche si la création a réussi, NULL sinon.
 */
extern Image* createBlankImage(int w, int h);

/*!
 * \fn extern Image* imageCopy(Image* from)
 * \brief Copie une Image
 *
 * \param from Pointeur vers l'Image à copier
 * \return Pointeur vers l'image copié si la copie a réussi, NULL sinon.
 */
extern Image* imageCopy(Image* from);

#endif
