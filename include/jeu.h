/*!
 *	\file jeu.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 04/04/13
 *
 *	\brief Fonctions du jeu (menu, déroulement).
 */

#ifndef JEU_H
#define JEU_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <SDL/SDL.h>

#include "gui/gui.h"
#include "list.h"
#include "map.h"
#include "monster.h"
#include "tower.h"
#include "resource.h"

/*!
 * \enum MENU_CHOICE
 * \brief Toutes les options du menu principal
 */
typedef enum {
	MENU_EXIT = 0, /*!< Quitter le jeu */
	MENU_MAP = 1, /*!< Affichage des maps */
	MENU_HELP = 2, /*!< Affichage de l'aide */
	MENU_GAME = 4, /*!< Menu en jeu */
	MENU_GENERAL = 8 /*!< Menu principal */
} MENU_CHOICE;

/*!
 * \fn void launchGameWithMap(const char* map)
 * \brief Lance une partie directement avec la carte map
 *
 * \param map Carte à charger
 */
void launchGameWithMap(const char* map);

/*!
 * \fn List* getMapList()
 * \brief Créer la liste des cartes
 *
 * \return La liste de cartes
 */
List* getMapList();

/*!
 * \fn int startMenu()
 * \brief Lance la boucle de menus
 *
 * \return -1 en cas d'erreur, 0 sinon.
 */
int startMenu();

/*!
 * \fn int showMainMenu()
 * \brief Affiche le menu principal
 *
 * \return Option choisie
 */
MENU_CHOICE showMainMenu();

/*!
 * \fn Map* showMapMenu()
 * \brief Affiche le menu de sélection de map
 * 
 * \return La carte chargée.
 */
Map* showMapMenu();

/*!
 * \fn void showHelpMenu()
 * \brief Affiche le menu d'aide
 */
void showHelpMenu();


/*!
 * \fn int play(Map* map)
 * \brief Boucle de jeu
 *
 * \param map Carte du jeu à afficher
 * \return 1 si victoire, 0 si défaite, -1 si quitte.
 */
int play(Map* map);

/*!
 * \fn void createWave(int level, List* monsters, Map* map)
 * \brief Créé une vague de monstres
 *
 * \param level niveau de la vague à créer
 * \param monsters Liste de monstres à remplir
 * \param map carte du jeu
 */
void createWave(int level, List* monsters, Map* map);

/*!
 * \fn int createWave(int level, List* monsters, Map* map)
 * \brief Créé une vague de monstres
 *
 * \param level niveau de la vague à créer
 * \param monsters Liste de monstres à remplir
 * \param map carte du jeu
 *
 * \return 1 si la tour peut être placée, 0 sinon.
 */
int canPlaceTower(Map* map, List* towers, Position coord, Position size);


void removeTower(List* towers, Tower* tower);

/*!
 * \fn void showEndMenu(int victory)
 * \brief Affiche le menu de victoire/défaite
 *
 * \param victory Entier différent de 0 si victoire.
 */
void showEndMenu(int victory);

#endif
