#include "jeu.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape() {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 600, 0);
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

void initSDL(){
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		exit(-1);
	}

	setVideoMode();
}

void launchGameWithMap(const char* mapfile)
{
	if(mapfile == NULL)
		return;
	initSDL();
	printf("Map à charger: %s\n", mapfile);
	Map* m = loadMap(mapfile);
	int a = play(m);
	if(a != -1)
		showEndMenu(a);
}

List* getMapList(){
	DIR* dir = opendir("./data");
	struct dirent* file;
	List* list_map = list_init();

	if(dir == NULL)
	{
		printf("Impossible d'ouvrir le dossier data!\n");
		exit(-1);
	}
	//int i = 1;
	while((file = readdir(dir)) != NULL)
	{
		if(strstr(file->d_name, ".itd") != NULL)
		{
			char* map = malloc(sizeof(char)*(strlen(file->d_name)+1));
			list_append(list_map, map);
			strcpy(map, file->d_name);
			//printf("%d - %s\n", i++, file->d_name);
		}
	}
	closedir(dir);

	return list_map;
}

int startMenu()
{
	initSDL();
	List* map_list = getMapList();
	SDL_WM_SetCaption("ITD", NULL);
	
	int choice;
	do {
		choice = showMainMenu();
		if(choice == MENU_MAP)
		{
			Map* map = showMapMenu(map_list);
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

Map* showMapMenu(List* map_list)
{
	int i, size;
	char* map;
	printf("--- Menu Maps ---\n");
	size = list_size(map_list);
	for(i=0; i<size; i++){
		map =list_get(map_list, i);
		printf("%d - %s\n", i+1, map);
	}
	printf("0 - Quitter\n");
	int choice;
	do {
		printf("choix: ");
		scanf("%d", &choice);
	} while(choice < 0 || choice >= i);
	if(choice == 0)
		return NULL;
	else{
		map = list_get(map_list, choice-1);
		char* tmp = malloc(sizeof(char)*(7+strlen(map)+1));
		sprintf(tmp,"data/%s", map);
		//printf("%s\n", map);
		Map* m= loadMap(tmp);
		free(tmp);
		return m;
	}

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

void dessinCarre(){
	glColor3ub(255,0,0);
	glBegin(GL_QUADS);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
		glVertex2f(-0.5,-0.5);
		glVertex2f(-0.5,0.5);
	glEnd();
}

int play(Map* map)
{
	int a =0;
	List* towers = list_init();
	List* monsters = list_init();
	int cash = 100;
	int wave = 0, state = 0;
	int running = 1;
	Position pos;
	pos.x = 200;
	pos.y = 500;
	printf("%f %f\n",pos.x, pos.y );
	Tower* t = createTower(pos, ROCKET);
	list_append(towers, t);
	Monster* m = createMonster(NORMAL, map->nodes);
	list_append(monsters, m);
	Monster* m2 = createMonster(FAST, map->nodes);
	list_append(monsters, m2);
	Monster* m3 = createMonster(SLOW, map->nodes);
	list_append(monsters, m3);


	while(running)
	{
		Uint32 startTime = SDL_GetTicks();

		// dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* dessin des composantes de jeu */
		drawMap(map);
		//drawTower(t);
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
						case 't' : 
						{
							a =1;
							
						}
							break;


						case SDLK_ESCAPE : 
							running = 0;
							state = -1;
							break;
						default : 
							break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
						{
							if(a == 1){
								Position position;
								position.x = event.button.x;
								position.y = event.button.y;
								Tower* tour = createTower(position, ROCKET);
								list_append(towers, tour);
								printf("%f %f\n", position.x, position.y);
								a=0;
							}
						}
							break;

						default:
							break;

					}
				  
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
