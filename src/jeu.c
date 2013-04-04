#include "jeu.h"

void launchGameWithMap(const char* mapfile)
{
	if(mapfile == NULL)
		return;

	printf("Map à charger: %s\n", mapfile);
}

int startMenu()
{
	int choice;
	do {
		choice = showMainMenu();
		if(choice == MENU_MAP)
		{
			Map* map = showMapMenu();
			play(map);
		} 
		else if(choice == MENU_HELP)
		{
			showHelpMenu();
		}
	} while(choice != MENU_EXIT);
	return 0;
}

MENU_CHOICE showMainMenu()
{
	int val;
	do {
		printf("--- Menu principal ITD ---\n");
		printf("1 - Maps\n");
		printf("2 - Aide\n");
		printf("0 - Quitter\n");
		printf("choix: ");
		scanf("%d", &val);
	} while(val > 2 || val < 0);
	switch(val)
	{
		case 0:
			return MENU_EXIT;
		case 1:
			return MENU_MAP;
		case 2:
			return MENU_HELP;
	}
	return MENU_EXIT;
}

Map* showMapMenu()
{
	printf("--- Menu Maps ---\n");
	DIR* dir = opendir("./data");
	struct dirent* file;

	if(dir == NULL)
	{
		printf("Impossible d'ouvrir le dossier data!\n");
		exit(-1);
	}
	int i = 1;
	while((file = readdir(dir)) != NULL)
	{
		if(strstr(file->d_name, ".itd") != NULL)
		{
			printf("%d - %s\n", i++, file->d_name);
		}
	}
	printf("0 - Quitter\n");
	closedir(dir);
	int choice;
	do {
		printf("choix: ");
		scanf("%d", &choice);
	} while(choice < 0 || choice >= i);
	return NULL;
}

void showHelpMenu()
{
	printf("--- Help Menu---\n");
	printf("Objectif:\n");
	printf("\tVotre but est d'empêcher les monstres essayant d'atteindre la sortie\n en les détruisant\n");
	printf("\tVous commencez le jeu avec une petite somme d'argent. Utilisez-le pour\n construire des tours!\n");
	printf("\tChaque monstre tué vous rapporte une quantité d'argent que vous pouvez\n investir dans d'autres tours.\n");
	printf("\tSi un monstre arrive à franchir vos défenses, vous avez perdu!\n");
	printf("\n\n");
	printf("Tours:\n");
	printf("\tROCKET\n");
	printf("\tLASER\n");
	printf("\tMACHINEGUN\n");
	printf("\tHYBRID\n");
	return;
}

int play(Map* map)
{
	List* towers = list_init();
	List* monsters = list_init();
	printf("play\n");
	
	list_delete(towers);
	list_delete(monsters);
	return 1;
}
