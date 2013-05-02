#include "jeu.h"
#include "gui/button.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int BTN_MAPS = 2, BTN_HELP = 3, BTN_EXIT = 4;

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

void initGUI()
{
	GUI_Init();
	GUI_CreateButton(BTN_MAPS, MENU_GENERAL, "Maps", NULL,300,110,150,70);
	GUI_CreateButton(BTN_HELP, MENU_GENERAL, "Aide", NULL,300,210,150,70);
	GUI_CreateButton(BTN_EXIT, MENU_GENERAL, "Quitter", NULL,300,410,150,70);
}

void initSDL(){
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		exit(-1);
	}
	TTF_Init();
	setVideoMode();
	initGUI();
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

	GUI_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}

MENU_CHOICE showMainMenu()
{
	int val = 0;
	int running = 1;
	while(running) {
		Uint32 start = SDL_GetTicks();

		// dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		GUI_Draw(MENU_GENERAL);
		SDL_GL_SwapBuffers();

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) {
				running = 0;
				break;
			} 
			GUI_ProceedEvents(&event);
			GUI_Event gui;				
			while(GUI_PollEvent(&gui)) {
				switch(gui.type) {
					case GUI_ET_BUTTON:
							if(gui.button.action == GUI_BTEV_RELEASED) {
								if(gui.button.id == BTN_EXIT)  {
									return MENU_EXIT;
								} else if(gui.button.id == BTN_HELP) {
									return MENU_HELP;
								} else if(gui.button.id == BTN_MAPS) {
									return MENU_MAP;
								}
							}
						break;
					default:
						break;
				}
			}
			
			
			switch(event.type) {
				case SDL_KEYDOWN:
			  		switch(event.key.keysym.sym){
						case 'q' : 
						case SDLK_ESCAPE : 
							running = 0;
							break;
						default : 
							break;
					}
					break;
				  
				default:
					break;
			}
		}

		Uint32 elapsed = SDL_GetTicks() - start;
		if(elapsed < FRAMERATE_MILLISECONDS)
		{
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsed);
		}
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

int play(Map* map)
{
	List* towers = list_init();
	List* monsters = list_init();
	SDL_Color textColor = {255,255,255};
	int cash = 100;
	int wave = 0, state = 0;
	int running = 1;
	char buff[64];
	sprintf(buff, "Argent: %d", cash);
	printf("%s\n", buff);
	Text* cashtxt = GUI_CreateText(0, MENU_GAME, buff, textColor, 0,0, 150, 50);
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
		GUI_Draw(MENU_GAME);
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
				createWave(wave, monsters, map);
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

void createWave(int level, List* monsters, Map* map){
	int i = 0;
	for(i = 0; i<10; i++){
		Monster* m = createMonster(NORMAL, map->nodes, -(i*1000*2));
		list_append(monsters, m);
	}
	
}


void showEndMenu(int victory)
{
	if(victory)
		printf("Victoire\n");
	else
		printf("Défaite!\n");
}
