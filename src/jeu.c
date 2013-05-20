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
	BTN_LEAVE_HELP,
	BTN_SELL,
	TXT_CASH,
	TXT_WAVE,
	TXT_TOWERNAME,
	TXT_COST,
	TXT_FIELD3,
	TXT_FIELD4,
	TXT_FIELD5
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
	GUI_CreateText(TXT_CASH, MENU_GAME, "", textColor, 110,0, FONT_32);
	GUI_CreateText(TXT_WAVE, MENU_GAME, "", textColor, 380,0, FONT_32);
	GUI_CreateText(TXT_TOWERNAME, MENU_GAME, "", textColor, 625,300, FONT_24);
	GUI_CreateText(TXT_COST, MENU_GAME, "", textColor, 625,330, FONT_24);
	GUI_CreateText(TXT_FIELD3, MENU_GAME, "", textColor, 625,360, FONT_24);
	GUI_CreateText(TXT_FIELD4, MENU_GAME, "", textColor, 625,390, FONT_24);
	GUI_CreateText(TXT_FIELD5, MENU_GAME, "", textColor,680,420, FONT_24);
	GUI_CreateButton(BTN_SELL, MENU_GAME, "Sell", NULL, textColor2, 625,420,50,30);

	GUI_CreateButton(BTN_ROCKET, MENU_GAME, NULL, "images/menus/rocket.png", textColor, 625,110,50,50);
	GUI_CreateButton(BTN_LASER, MENU_GAME, NULL, "images/menus/laser.png", textColor, 700,110,50,50);
	GUI_CreateButton(BTN_MACHINEGUN, MENU_GAME, NULL, "images/menus/machinegun.png", textColor, 625,185,50,50);
	GUI_CreateButton(BTN_HYBRID, MENU_GAME, NULL, "images/menus/hybrid.png", textColor, 700,185,50,50);
	GUI_CreateButton(BTN_EXIT_GAME, MENU_GAME, "Quitter", NULL, textColor, 610,500,180,70);
	GUI_CreateText(0, MENU_HELP, "HELP", textColor2, 10,10, FONT_48);
	GUI_CreateText(0, MENU_HELP, "Votre but est d'empecher les monstres essayant d'atteindre la sortie. ", textColor, 10,60, FONT_24);
	GUI_CreateText(0, MENU_HELP, "en les detruisant. ", textColor, 10,90, FONT_24);
	GUI_CreateText(0, MENU_HELP, "Vous commencez le jeu avec une petite somme d'argent. ", textColor, 10,120, FONT_24);
	 GUI_CreateText(0, MENU_HELP, "Utilisez-le pour construire des tours! ", textColor, 10,150, FONT_24);

	GUI_CreateText(0, MENU_HELP, "Chaque monstre tue vous rapporte une quantite d'argent que vous pouvez ", textColor, 10,180, FONT_24);

	GUI_CreateText(0, MENU_HELP, "investir dans d'autres tours. ", textColor, 10,210, FONT_24);
	GUI_CreateText(0, MENU_HELP, "Si un monstre arrive a franchir vos defenses, vous avez perdu. ", textColor, 10,240, FONT_24);

	GUI_CreateText(0, MENU_HELP, "Tours Rocket : Ces tours infligent beaucoup de degats mais ", textColor, 50,300, FONT_24);

	GUI_CreateText(0, MENU_HELP, "ont une cadence de feu faible. ", textColor, 10,330, FONT_24);

	GUI_CreateText(0, MENU_HELP, "Tours Laser: Elles tirent tres rapidement mais ont une faible portee ", textColor, 50,360, FONT_24);

	GUI_CreateText(0, MENU_HELP, "et occasionnent des dommages moyens. ", textColor, 10,390, FONT_24);

	GUI_CreateText(0, MENU_HELP, "Tours Machinegun: Elles occasionnent peu de degats, ont une portee ", textColor, 50,420, FONT_24);

	GUI_CreateText(0, MENU_HELP, "tres limitee mais une bonne cadence de tir et tirent sur tous les ", textColor, 10,450, FONT_24);
	 GUI_CreateText(0, MENU_HELP, "monstres a leur portee. ", textColor, 10,480, FONT_24);
	GUI_CreateText(0, MENU_HELP, "Tours Hybrides: Elles ont une tres bonne portee ", textColor, 50,510, FONT_24);

	GUI_CreateText(0, MENU_HELP, "et une bonne cadence de tir mais occasionnent peu de degats. ", textColor, 10,540, FONT_24);

	GUI_CreateButton(BTN_LEAVE_HELP, MENU_HELP, "Ok", NULL, textColor2, 680,480,100,100);
}

void initSDL(){
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		exit(-1);
	}
	TTF_Init();
	setVideoMode();
	SDL_WM_SetCaption("ITD", NULL);

	initGUI();
	initResourcesManager();
}

void launchGameWithMap(const char* mapfile)
{
	if(mapfile == NULL)
		return;
	initSDL();
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
		fprintf(stderr, "Impossible d'ouvrir le dossier data!\n");
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
	int running = 1;
	while(running) {
		Uint32 start = SDL_GetTicks();

		// dessin
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		GUI_Draw(MENU_HELP);
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
								if(gui.button.id == BTN_LEAVE_HELP)  {
									running = 0;
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
	int wave = 0, state = 0, left = 0, right = 0, up = 0, down = 0;
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
	tmp = GUI_GetWidget(TXT_FIELD3);
	Text* field3txt = tmp->w.text;
	tmp = GUI_GetWidget(TXT_FIELD4);
	Text* field4txt = tmp->w.text;
	tmp = GUI_GetWidget(TXT_FIELD5);
	Text* field5txt = tmp->w.text;
	tmp = GUI_GetWidget(BTN_SELL);
	Button* sellbtn = tmp->w.button;

	Tower* selectedTower = NULL;

	sprintf(buff, "%d", cash);
	setText(cashtxt, buff);
	sprintf(buff, "Appuyer sur 'P' pour lancer ");
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
			canPlaceTower(map, towers, cursor, size);
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
							if(gui.button.action == GUI_BTEV_RELEASED) {
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
								else if(gui.button.id == BTN_SELL) {
									if(selectedTower != NULL)
									{
										int give = (int)(getTowerCost(selectedTower->type)*3/4.f);
										cash += give;
										sprintf(buff, "%d", cash);
										setText(cashtxt, buff);
										removeTower(towers, selectedTower);
										selectedTower = NULL;
									}
								}
							} else if(gui.button.action == GUI_BTEV_HOVER) { 
								if(gui.button.id == BTN_ROCKET) {
									if(placer_tour != 1 && hover_type != ROCKET) {
										hover_type = ROCKET;
										setText(nametxt, "Rocket ");
										sprintf(buff,"Cost: %d ", getTowerCost(ROCKET));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
								else if(gui.button.id == BTN_LASER) {
									if(placer_tour != 1 && hover_type != LASER) {
										hover_type = LASER;
										setText(nametxt, "Laser ");
										sprintf(buff,"Cost: %d ", getTowerCost(LASER));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
								else if(gui.button.id == BTN_MACHINEGUN) {
									if(placer_tour != 1 && hover_type != MACHINEGUN) {
										hover_type = MACHINEGUN;
										setText(nametxt, "Machinegun ");
										sprintf(buff,"Cost: %d ", getTowerCost(MACHINEGUN));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
								else if(gui.button.id == BTN_HYBRID) {
									if(placer_tour != 1 && hover_type != HYBRID) {
										hover_type = HYBRID;
										setText(nametxt, "Hybrid ");
										sprintf(buff,"Cost: %d ", getTowerCost(HYBRID));
										setText(costtxt, buff);
									}
									//placer_tour = 1;
								}
							}
							else if(gui.button.action == GUI_BTEV_LEFTHOVER) {
								if(gui.button.id == BTN_ROCKET || gui.button.id == BTN_LASER || gui.button.id == BTN_MACHINEGUN || gui.button.id == BTN_HYBRID) {
									if(placer_tour != 1 && hover_type != -1) {
										hover_type = -1;
										setText(nametxt, "");
										setText(costtxt, "");
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
								sprintf(buff, "Appuyer sur 'P' pour reprendre ");
								setText(wavetxt, buff);
								list_foreach(monsters, onPauseMonster);
							} else {
								sprintf(buff, "%d", wave);
								setText(wavetxt, buff);
								list_foreach(monsters, onResumeMonster);
								list_foreach(towers, onResumeTower);
							}
							break;
						case SDLK_n:
							map->drawNodes = 1-map->drawNodes;
							break;
						case SDLK_LEFT:
							if(!left) {
								Position p = {-10.f, 0};
								addCameraDirection(map, p);
								left = 1;
							}
							break;
						case SDLK_RIGHT:
							if(!right) {
								Position p = {10.f, 0};
								addCameraDirection(map, p);
								right = 1;							
							}
							break;
						case SDLK_UP:
							if(!up) { up = 1;
								Position p = {0,-10.f};
								addCameraDirection(map, p);
							}
							break;
						case SDLK_DOWN:
							if(!down) { down = 1;
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
								if(left) { left = 0;
									Position p = {10.f, 0};
									addCameraDirection(map, p);
								}
								break;
							case SDLK_RIGHT:
								if(right) { right = 0;
									Position p = {-10.f, 0};
									addCameraDirection(map, p);
								}
								break;
							case SDLK_UP:
								if(up) { up = 0;
									Position p = {0,10.f};
									addCameraDirection(map, p);
								}
								break;
							case SDLK_DOWN:
								if(down) { down = 0;
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
								coord.x -= ((int)coord.x)%32 - 33;
								coord.y -= ((int)coord.y)%32 - 18;
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
								setText(nametxt, "");
								setText(costtxt, "");
								setText(field3txt, "");
								setText(field4txt, "");
								setText(field5txt, "");
								for(i = 0; i<list_size(towers); i++)
								{
									Tower* t = list_get(towers, i);
									selectTower(t, coord);
									if(t->selected) {
										sprintf(buff, "%s", getTowerName(t->type));
										setText(nametxt, buff);
										sprintf(buff, "Portee: %d ", (int)t->range);
										setText(costtxt, buff);
										sprintf(buff, "Degats: %d ", (int)t->damages);
										setText(field3txt, buff);
										sprintf(buff, "Cooldowns: %d ", t->reloadTime);
										setText(field4txt, buff);
										sprintf(buff, "pour %d ", (int)(getTowerCost(t->type)*3/4.f));
										setText(field5txt, buff);
										selectedTower = t;
									}
								}
							}

							break;
						case SDL_BUTTON_RIGHT:
							placer_tour = 0;
							break;
						case SDL_BUTTON_WHEELUP:
								map->camPos.z += 0.1f;
								if(map->camPos.z > 1.f)
									map->camPos.z = 1.f;
							break;
						case SDL_BUTTON_WHEELDOWN:
								map->camPos.z -= 0.1f;
								if(map->camPos.z < .5f)
									map->camPos.z = .5f;
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					cursor.x = event.motion.x + map->camPos.x;
					cursor.y = event.motion.y + map->camPos.y;
					cursor.x -= ((int)cursor.x)%32 - 33;//*map->camPos.z;
					cursor.y -= ((int)cursor.y)%32 - 18;//*map->camPos.z;
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
					cash += 5+2*(wave-1);
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
		}
		Uint32 elapsed = SDL_GetTicks() - startTime;
		if(elapsed < FRAMERATE_MILLISECONDS)
		{
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsed);
		}
	}
	
	list_delete(towers);
	list_delete(monsters);
	return state;
}

void createWave(int level, List* monsters, Map* map){
	TYPE_MONSTER type;
	float life = level*100;
	switch(level){
		case 1:
			type = NORMAL;
			break;
		case 2:
			type = NORMAL;
			break;
		case 3:
			type = FAST;
			break;

		case 4:
			type = NORMAL;
			break;

		case 5:
			type = SLOW;
			break;

		case 6:
			type = FLYER;
			break;

		case 7:
			type = FAST;
			break;

		case 8:
			type = NORMAL;
			break;

		case 9:
			type = SLOW;
			break;

		case 10:
			type = FAST;
			break;

		case 11:
			type = FLYER;
			break;

		case 12:
			type = NORMAL;
			break;

		case 13:
			type = SLOW;
			break;

		case 14:
			type = FLYER;
			break;

		case 15:
			type = NORMAL;
			break;

		case 16:
			type = FAST;
			break;

		case 17:
			type = NORMAL;
			break;

		case 18:
			type = SLOW;
			break;

		case 19:
			type = FLYER;
			break;

		case 20:
			type = FLYER;
			break;
		default:
			return;
	}
	int delay = 2000;
	switch(type)
	{
		case NORMAL:
			delay = 1500;
			break;
		case SLOW:
			delay = 2000;
			break;
		case FAST:
			delay = 1000;
			break;
		case FLYER:
			delay = 2000;
			break;
	}
	int i = 0;
	for(i = 0; i<10; i++){
		Monster* m = createMonster(type, life, map->nodes, (i+1)*delay);
		//printf("%p\n", m);
		list_append(monsters, m);
	}
}

int canPlaceTower(Map* map, List* towers, Position coord, Position size)
{
	if(collideWithMap(map, coord, size, map->camPos))
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

void removeTower(List* towers, Tower* tower)
{
	int i;
	for(i = 0; i<list_size(towers); ++i)
	{
		Tower* t = list_get(towers, i);
		if(t == tower)
		{
			list_remove(towers, i);
			return;
		}
	}
}

void showEndMenu(int victory)
{
	if(victory)
		printf("Victoire\n");
	else
		printf("Défaite!\n");
}
