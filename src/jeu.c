#include "jeu.h"
#include "gui/button.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 66;

enum {
	BTN_MAPS,
	BTN_HELP,
	BTN_EXIT,
	BTN_ROCKET,
	BTN_LASER,
	BTN_MACHINEGUN,
	BTN_HYBRID,
	BTN_EXIT_GAME,
	TXT_CASH,
	TXT_WAVE,
	TXT_TOWERNAME,
	TXT_COST
};

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
	SDL_Color textColor = {255,255,255};
	SDL_Color textColor2 = {127,0,0};
	SDL_Color textColor3 = {0,0, 127};
	GUI_CreateImage(0, MENU_GENERAL, "images/menus/background.png", 0, 0, 1.f, 1.f);
	GUI_CreateButton(BTN_MAPS, MENU_GENERAL, "Maps", NULL, textColor2,250,60,150,70);
	GUI_CreateButton(BTN_HELP, MENU_GENERAL, "Aide", NULL, textColor2,250,160,150,70);
	GUI_CreateButton(BTN_EXIT, MENU_GENERAL, "Quitter", NULL, textColor3,10,500,150,70);
	GUI_CreateText(0, MENU_GAME, "Argent: ", textColor, 0,0, FONT_32);
	GUI_CreateText(0, MENU_GAME, "Wave: ", textColor, 300,0, FONT_32);
	GUI_CreateText(TXT_CASH, MENU_GAME, "a", textColor, 110,0, FONT_32);
	GUI_CreateText(TXT_WAVE, MENU_GAME, "a", textColor, 380,0, FONT_32);
	GUI_CreateText(TXT_TOWERNAME, MENU_GAME, "None", textColor, 625,250, FONT_32);
	GUI_CreateText(TXT_COST, MENU_GAME, "Cost: 0", textColor, 625,300, FONT_32);
	GUI_CreateButton(BTN_ROCKET, MENU_GAME, NULL, "images/menus/rocket.png", textColor, 625,110,50,50);
	GUI_CreateButton(BTN_LASER, MENU_GAME, NULL, "images/menus/laser.png", textColor, 700,110,50,50);
	GUI_CreateButton(BTN_MACHINEGUN, MENU_GAME, NULL, "images/menus/machinegun.png", textColor, 625,185,50,50);
	GUI_CreateButton(BTN_HYBRID, MENU_GAME, NULL, "images/menus/hybrid.png", textColor, 700,185,50,50);
	GUI_CreateButton(BTN_EXIT_GAME, MENU_GAME, "Quitter", NULL, textColor, 610,500,180,70);
}

void initSDL(){
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		exit(-1);
	}
	TTF_Init();
	setVideoMode();
	initGUI();
	initResourcesManager();
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
			deleteMap(map);
		} 
		else if(choice == MENU_HELP)
		{
			showHelpMenu();
		}
	} while(choice != MENU_EXIT);
	while(list_size(map_list))
	{
		char* t = list_get(map_list, 0);
		free(t);
		list_remove(map_list, 0);
	}
	list_delete(map_list);

	deleteResourcesManager();
	GUI_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}

MENU_CHOICE showMainMenu()
{
	//int val = 0;
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
	} while(choice < 0 || choice > i);
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
	int placer_tour=0;
	TYPE_TOWER placer_type = ROCKET;
	int hover_type = -1;
	List* towers = list_init();
	List* monsters = list_init();
	SDL_Color textColor = {255,255,255};
	int cash = 100;
	int pause = 1;
	int wave = 0, state = 0;
	int running = 1;
	char buff[64];

	GUI_Widget* tmp = GUI_GetWidget(TXT_CASH);
	Text* cashtxt = tmp->w.text;
	tmp = GUI_GetWidget(TXT_WAVE);
	Text* wavetxt = tmp->w.text;
	tmp = GUI_GetWidget(TXT_COST);
	Text* costtxt = tmp->w.text;
	tmp = GUI_GetWidget(TXT_TOWERNAME);
	Text* nametxt = tmp->w.text;

	sprintf(buff, "%d", cash);
	setText(cashtxt, buff);
	sprintf(buff, "Appuyer sur 'P' pour lancer");
	setText(wavetxt, buff);
	
	Position cursor;
	int tmpint = 0;
	while(running)
	{
		Uint32 startTime = SDL_GetTicks();
		// dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* dessin des composantes de jeu */
		drawMap(map);
		int i;
		for(i = 0; i<list_size(monsters); i++)
		{
			Monster* m = list_get(monsters, i);
			drawMonster(m, map->camPos);
		}
		for(i = 0; i<list_size(towers); i++)
		{
			Tower* t = list_get(towers, i);
			drawTower(t, map->camPos);
		}
		
		/* dessin de l'UI */
		GUI_Draw(MENU_GAME);

		if(placer_tour) {
			Position size = getTowerSize(placer_type);
			drawTower2(placer_type, cursor, 0.f, 1, map->camPos);
		}

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
							if(gui.button.action == GUI_BTEV_PRESSED) {
								if(gui.button.id == BTN_EXIT_GAME)
									running = 0;
								else if(gui.button.id == BTN_ROCKET) {
									placer_tour = 1; placer_type = ROCKET;
								}
								else if(gui.button.id == BTN_LASER) {
									placer_tour = 1; placer_type = LASER;
								}
								else if(gui.button.id == BTN_MACHINEGUN) {
									placer_tour = 1; placer_type = MACHINEGUN;
								}
								else if(gui.button.id == BTN_HYBRID) {
									placer_tour = 1; placer_type = HYBRID;
								}
							} else if(gui.button.action == GUI_BTEV_HOVER) {
								if(gui.button.id == BTN_ROCKET) {
									if(hover_type != ROCKET) {
										hover_type = ROCKET;
										setText(nametxt, "Rocket");
										sprintf(buff,"Cost: %d", getTowerCost(ROCKET));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
								else if(gui.button.id == BTN_LASER) {
									if(hover_type != LASER) {
										hover_type = LASER;
										setText(nametxt, "Laser");
										sprintf(buff,"Cost: %d", getTowerCost(LASER));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
								else if(gui.button.id == BTN_MACHINEGUN) {
									if(hover_type != MACHINEGUN) {
										hover_type = MACHINEGUN;
										setText(nametxt, "Machinegun");
										sprintf(buff,"Cost: %d", getTowerCost(MACHINEGUN));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
								else if(gui.button.id == BTN_HYBRID) {
									if(hover_type != HYBRID) {
										hover_type = HYBRID;
										setText(nametxt, "Hybrid");
										sprintf(buff,"Cost: %d", getTowerCost(HYBRID));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
							}
							else if(gui.button.action == GUI_BTEV_LEFTHOVER) {
								if(gui.button.id == BTN_ROCKET || gui.button.id == BTN_LASER || gui.button.id == BTN_MACHINEGUN || gui.button.id == BTN_HYBRID) {
									if(hover_type != -1) {
										hover_type = -1;
										setText(nametxt, "None");
										sprintf(buff,"No cost");
										setText(costtxt, buff);
									}
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
						case SDLK_p:
							pause = 1-pause;
							if(pause) {
								sprintf(buff, "Appuyer sur 'P' pour reprendre");
								setText(wavetxt, buff);
								list_foreach(monsters, onPauseMonster);
							} else {
								sprintf(buff, "%d", wave);
								setText(wavetxt, buff);
								//list_foreach(monsters, onResumeMonster);
								//list_foreach(towers, onResumeTower);
							}
							break;
						case SDLK_LEFT:
							{
								Position p = {-10.f, 0};
								addCameraDirection(map, p);
							}
							break;
						case SDLK_RIGHT:
							{
								Position p = {10.f, 0};
								addCameraDirection(map, p);
							}
							break;
						case SDLK_UP:
							{
								Position p = {0,-10.f};
								addCameraDirection(map, p);
							}
							break;
						case SDLK_DOWN:
							{
								Position p = {0, 10.f};
								addCameraDirection(map, p);
							}
							break;
						default : 
							break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_LEFT:
								{
									Position p = {10.f, 0};
									addCameraDirection(map, p);
								}
								break;
							case SDLK_RIGHT:
								{
									Position p = {-10.f, 0};
									addCameraDirection(map, p);
								}
								break;
							case SDLK_UP:
								{
									Position p = {0,10.f};
									addCameraDirection(map, p);
								}
								break;
							case SDLK_DOWN:
								{
									Position p = {0,-10.f};
									addCameraDirection(map, p);
								}
								break;
							default: 
								break;
						}
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							if(placer_tour == 1){
								Position size = getTowerSize(placer_type);
								Position coord = {event.button.x+map->camPos.x, event.button.y+map->camPos.y};
								int cost = getTowerCost(placer_type);
								if(cash >= cost && canPlaceTower(map, towers, coord, size))
								{
									Tower* t = createTower(coord, placer_type);
									list_append(towers, t);
									cash -= getTowerCost(placer_type);

									sprintf(buff, "%d", cash);
									setText(cashtxt, buff);
									placer_tour = 0;
								}
							}
							else {
								Position coord = {event.button.x+map->camPos.x, event.button.y+map->camPos.y};
								int i;
								for(i = 0; i<list_size(towers); i++)
								{
									Tower* t = list_get(towers, i);
									selectTower(t, coord);
								}
							}

							break;

						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					cursor.x = event.motion.x + map->camPos.x;
					cursor.y = event.motion.y + map->camPos.y;
					break;
				  
				default:
					break;
			}

			
		}
		updateMap(map);
		if(pause != 1)
		{
			if(list_size(monsters) == 0)
			{
				if(wave < 20)
				{
					wave++;
					createWave(wave, monsters, map);
					sprintf(buff, "%d", wave);
					setText(wavetxt, buff);
				}
				else
				{
					state = 1;
					running = 0;
				}
				
			}
			Data* t = list_getData(towers,0);
			while(t != NULL)
			{	
				//Uint32 e = SDL_GetTicks() - startTime;
				Tower* tow = t->value;
				if(tow->target == NULL)
					lookForBestTarget(tow,monsters);

				updateTower(tow);
				
				t = t->next;
			}

			int i;
			for(i=0;i<list_size(towers);i++)
			{	
				Tower* tow = list_get(towers, i);
				if(tow->target != NULL && (isDead(tow->target) || outOfRange(tow->coord, tow->target->coord, tow->range)))
					tow->target = NULL;
			}

			for(i=0;i<list_size(monsters);i++)
			{	
				Monster* mons = list_get(monsters, i);
				if(mons == NULL)
					continue;

				if(isDead(mons)){
					list_remove(monsters, i--);
					cash += 10;
					sprintf(buff, "%d", cash);
					setText(cashtxt, buff);
					deleteMonster(mons);
				} else {
					//Uint32 e = SDL_GetTicks() - startTime;
					updateMonster(mons);

					if(hasFinishedMonster(mons))
					{
						state = 0;
						running = 0;
					}
				}
				
			}
			//if(tmpint++ > 0)
			//	exit(0);
		}
		Uint32 elapsed = SDL_GetTicks() - startTime;
		if(elapsed < FRAMERATE_MILLISECONDS)
		{
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsed);
		}
		//printf("elapsed: %dmsec %d %d\n", SDL_GetTicks() - startTime, elapsed, FRAMERATE_MILLISECONDS);
		//exit(0);
	}
	
	list_delete(towers);
	list_delete(monsters);
	return state;
}

void createWave(int level, List* monsters, Map* map){
	TYPE_MONSTER type;
	if(level % 4 == 0)
		type = NORMAL;
	else if(level % 4 == 1)
		type = FAST;
	else if(level % 4 == 2)
		type = SLOW;
	else
		type = FLYER;

	int i = 0;
	for(i = 0; i<10; i++){
		Monster* m = createMonster(type, map->nodes, (i*3000));
		//printf("%p\n", m);
		list_append(monsters, m);
	}
}

int canPlaceTower(Map* map, List* towers, Position coord, Position size)
{
	if(collideWithMap(map, coord, size))
		return 0;

	int i;
	for(i = 0; i<list_size(towers); ++i)
	{
		Tower* t = list_get(towers, i);
		if(collideWithTower(t, coord, size))
			return 0;
	}
	return 1;
}

void showEndMenu(int victory)
{
	if(victory)
		printf("Victoire\n");
	else
		printf("Défaite!\n");
}
