#include "jeu.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape() {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1., -1., 1.);
}

void setVideoMode() {
	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
	reshape();

	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}

void launchGameWithMap(const char* mapfile)
{
	if(mapfile == NULL)
		return;

	printf("Map à charger: %s\n", mapfile);
	Map* m = NULL;//loadMap(mapfile);
	int a = play(m);
	if(a != -1)
		showEndMenu(a);
}

int startMenu()
{
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	setVideoMode();

	SDL_WM_SetCaption("ITD", NULL);
	
	int choice;
	do {
		choice = showMainMenu();
		if(choice == MENU_MAP)
		{
			Map* map = showMapMenu();
			if(map != NULL)
				play(map);
		} 
		else if(choice == MENU_HELP)
		{
			showHelpMenu();
		}
	} while(choice != MENU_EXIT);

	SDL_Quit();
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
	int cash = 100;
	int wave = 0, state = 0;
	int running = 1;

	while(running)
	{
		Uint32 startTime = SDL_GetTicks();

		// dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* dessin des composantes de jeu */
		drawMap(map);
		list_foreach(monsters, drawMonster);
		list_foreach(towers, drawTower);
		
		/* dessin de l'UI */


		SDL_GL_SwapBuffers();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) {
				running = 0;
				break;
			} 
			switch(event.type) {
				case SDL_KEYDOWN:
			  		switch(event.key.keysym.sym){
						case 's' :
							if(wave == 0)
								wave = 1;
							break;
						case 'q' : 
						case SDLK_ESCAPE : 
							running = 0;
							state = -1;
							break;
						default : 
							break;
					}
					break;
				  
				default:
					break;
			}

			
		}

		if(wave > 0)
		{
			if(list_size(monsters) == 0)
			{
				if(wave < 20)
					wave++;
				else
				{
					state = 1;
					running = 0;
				}
				//createWave(wave, monsters);
			}
			Data* t = list_getData(towers,0);
			while(t != NULL)
			{	
				Tower* tow = t->value;
				if(tow->target == NULL)
					tow->target = NULL;//lookForBestTarget(tow, monsters);

				updateTower(tow, SDL_GetTicks() - startTime);
				
				t = t->next;
			}

			t = list_getData(monsters,0);
			while(t != NULL)
			{	
				Monster* mons = t->value;
				updateMonster(mons, SDL_GetTicks() - startTime);
				if(hasFinishedMonster(mons))
				{
					state = 0;
					running = 0;
				}
				t = t->next;
			}
		}
	}
	
	list_delete(towers);
	list_delete(monsters);
	//deleteMap(map);
	return state;
}

void showEndMenu(int victory)
{
	if(victory)
		printf("Victoire\n");
	else
		printf("Défaite!\n");
}
