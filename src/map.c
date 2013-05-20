#include "map.h"

Map* loadMap(char const* map){
	Map* m = malloc(sizeof(Map));
	Node* tete = malloc(sizeof(Node));
	FILE* f = NULL;
	char img[64];
	int num, r, g, b, energie, i;
	Color3ub chemin, noeud, construct, in, out;


	if (map == NULL)
		return NULL;
	
	f = fopen(map, "rb");

	if(f == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier %s. Fin du programme.\n", map);
		return NULL;
	}else{
		printf("Fichier bien chargé !\n");
	}

	//Nom de l'image représentant la carte
	fscanf(f, "%s", img);
	if (strcmp(img, "@ITD") != 0){
		fprintf(stderr, "Le fichier n'est pas une carte valide. Fin du programme.\n");
		return NULL;
	}
	fscanf(f, "%d", &num);
	if (num != 1){
		fprintf(stderr, "La version du fichier n'est pas valide. Fin du programme.\n");
		return NULL;
	}

	int full =0, cnt = 0;

	while(full == 0){
		cnt = fscanf(f, "%s", img);

		if (strcmp(img, "carte") == 0){
			fscanf(f, "%s", img);
			char* tmp = malloc(sizeof(char)*(7+strlen(img)+1));
			sprintf(tmp,"images/%s", img);
			m->ppm = loadImage(tmp);
			free(tmp);
		}else if (strcmp(img, "energie") == 0){
			fscanf(f, "%d", &num);
			energie = num;
		}else if (strcmp(img, "chemin") == 0){
			fscanf(f, "%d %d %d",&r, &g, &b);
			tete->path.r = r;
			tete->path.g = g;
			tete->path.b = b;
		}else if (strcmp(img, "noeud") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			tete->color.r = r;
			tete->color.g = g;
			tete->color.b = b;
		}else if (strcmp(img, "construct") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			construct.r = r;
			construct.g = g;
			construct.b = b;
		}else if (strcmp(img, "in") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			in.r = r;
			in.g = g;
			in.b = b;
		}else if (strcmp(img, "out") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			out.r = r;
			out.g = g;
			out.b = b;
		}else {
			long int longnum = strtol(img,NULL, 10);
			if(longnum != 0 && longnum != LONG_MAX && longnum != LONG_MIN){
				full=1;
				num = (int)longnum;
			}else{
				printf("La carte n'a pas un format valide.\n");
				exit(-1);
			}
		}

	}

	Node* tmp = tete;
	fscanf(f, "%f %f", &(tete->coord.x), &(tete->coord.y));
	tete->coord.y += 50.f;
	for(i=1; i<num; i++){
		Node* n = malloc(sizeof(Node));
		n->next = NULL;
		n->color = tete->color;
		n->path = tete->path;
		fscanf(f, "%f %f", &(n->coord.x), &(n->coord.y));
		n->coord.y += 50.f;
		tmp->next = n;
		tmp = n;
	}
	m->nodes = tete;
	m->camPos.x = 0; m->camPos.y = 0;
	m->camDir.x = 0; m->camDir.y = 0;

	Color3ub old = {120,120,120};
	SDL_Surface* image = swapColorsImage(m->ppm, old, construct);	
	m->tex = loadTexture(image);
	SDL_FreeSurface(image);

	return m;

}

int nodeOnMap(Node* n, Position camPos)
{
	if(n == NULL)
		return 0;

	if(n->coord.x-camPos.x < 0 
		|| n->coord.y-camPos.y - 50.f < 0 
		|| n->coord.x-camPos.x > MAP_WIDTH 
		|| n->coord.y-camPos.y - 50.f > MAP_HEIGHT)
		return 0;
	return 1;
}

void nodeXYCoordinates(Node* n, Position camPos, float* x, float* y)
{
	if(n->coord.x-camPos.x < 0)
		*x = 0;
	else if(n->coord.x-camPos.x > MAP_WIDTH)
		*x = MAP_WIDTH;
	else
		*x = n->coord.x-camPos.x;

	if(n->coord.y-camPos.y -50.f < 0)
			*y = 0;
	else if(n->coord.y-camPos.y-50.f > MAP_HEIGHT)
			*y = MAP_HEIGHT;
	else
			*y = n->coord.y-camPos.y;
}

void drawNode(Node* n, Position camPos){
		Node* tmp = n;
		glBegin(GL_LINE_STRIP);
			while(n != NULL){
				glColor3ub(n->path.r, n->path.g, n->path.b);
				/*if(nodeOnMap(n, camPos))
				{
					glVertex2f(n->coord.x-camPos.x, n->coord.y-camPos.y);
				} else {
					//if(nodeOnMap(n->next, camPos))	
					//{
						float x,y;
						nodeXYCoordinates(n, camPos, &x, &y);
						glVertex2f(x, y);
					//}
					//glEnd();
					//glBegin(GL_LINE_STRIP);
					
				}
				*/
				glVertex2f(n->coord.x-camPos.x, n->coord.y-camPos.y);
				n = n->next;
				
			}
		glEnd();
		n = tmp;
		glPointSize(5);
		glBegin(GL_POINTS);
			while(n != NULL){
				if(!(n->coord.x-camPos.x < 0 || 
						n->coord.y-camPos.y -50.f < 0 || 
						n->coord.x-camPos.x > MAP_WIDTH || 
						n->coord.y-camPos.y -50.f > MAP_HEIGHT)) {
					glColor3ub(n->color.r, n->color.g, n->color.b);
					glVertex2f(n->coord.x-camPos.x, n->coord.y-camPos.y);
				}
				n = n->next;
				
			}
		glEnd();
		glPointSize(1);
}

void dessinRepere(){
	glBegin(GL_LINES);
		glColor3ub(0, 255 ,0);
		glVertex2f(0,0);
		glVertex2f(0,1);
		glColor3ub(255, 0 ,0);
		glVertex2f(0,0);
		glVertex2f(1,0);
	glEnd();
}

void drawMap(Map* m){
	
	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m->tex);
	float texX = (MAP_WIDTH/(m->ppm->w*1.f));
	float deltaX = 0.f;
	if(m->camPos.x != 0)
		deltaX = m->camPos.x/(m->ppm->w*1.f);

	float texY = (MAP_HEIGHT/(m->ppm->h*1.f));
	float deltaY = 0.f;

	if(m->camPos.y != 0)
		deltaY = m->camPos.y /(m->ppm->h*1.f);
	
	glBegin(GL_QUADS);
		glTexCoord2f(deltaX, deltaY);
		glVertex2f(0.f, 50.f);

		glTexCoord2f(deltaX,texY+deltaY);
		glVertex2f(0.f, MAP_HEIGHT+50.f);

		glTexCoord2f(texX+deltaX,texY+deltaY); 
		glVertex2f(MAP_WIDTH, MAP_HEIGHT+50.f);

		glTexCoord2f(texX+deltaX,deltaY); 
		glVertex2f(MAP_WIDTH, 50.f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	drawNode(m->nodes, m->camPos);
}

void deleteMap(Map* m)
{
	if(m == NULL)
		return;

	deleteImage(m->ppm);
	deleteTexture(m->tex);
	freeList(&(m->nodes));
}

int collideWithMap(Map* m, Position pos, Position size, Position camPos)
{
	pos.x -= size.x/2;
	pos.y -= size.y/2;
	pos.y -= 50.f;
	if(pos.x-m->camPos.x < 0 || (pos.x+size.x)-m->camPos.x >= MAP_WIDTH || pos.y- m->camPos.y < 0 || (pos.y+size.y)- m->camPos.y >= MAP_HEIGHT)
		return 1;

	int h, w;
	for(w = pos.x+2; w<pos.x+size.x -2; w++)
		for(h = pos.y+2; h<pos.y+size.y -2; h++)
		{
			Uint8 r,g,b,a;
			GetPixel(m->ppm, w,h,&r,&g,&b,&a);
			if(r != 120 || g != 120 || b != 120) {
				return 1; 
			}
		} 

	
	return 0;
}

void updateMap(Map* m)
{
	if(m == NULL)
		return;

	moveCamera(m, m->camDir);
}

void addCameraDirection(Map* m, Position pos)
{
	if(m == NULL)
		return;

	m->camDir.x += pos.x;
	m->camDir.y += pos.y;
}

void moveCamera(Map* m, Position pos)
{
	if(m == NULL)
		return;

	m->camPos.x += pos.x;

	if(m->camPos.x < 0)
		m->camPos.x = 0;
	else if(m->camPos.x+MAP_WIDTH >= m->ppm->w)
		m->camPos.x = m->ppm->w-MAP_WIDTH;

	m->camPos.y += pos.y;
	if(m->camPos.y < 0)
		m->camPos.y = 0;
	else if(m->camPos.y+MAP_HEIGHT >= m->ppm->h)
		m->camPos.y = m->ppm->h-MAP_HEIGHT;

}
