#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"

int main(int argc, char** argv)
{
	if(argc > 1) 
	{
		launchGameWithMap(argv[1]);
	}

	return startMenu();
}

/*! \mainpage Imac Tower Defense Documentation
 *
 * \section intro_sec Introduction
 *
 * Documentation du projet Imac tower defense
 *
 * \section copyright Copyright and License
 * Copyright Landrau Laury et Sochard André | 2013
 *
 * <BR><BR>
 *
 */
