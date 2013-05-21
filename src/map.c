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
		fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", map);
		return NULL;
	}else{
	}

	//Nom de l'image représentant la carte
	fscanf(f, "%s", img);
	if (strcmp(img, "@ITD") != 0){
		fprintf(stderr, "Le fichier %s n'est pas une carte valide.\n", map);
		fclose(f);
		return NULL;
	}
	fscanf(f, "%d", &num);
	if (num != 1){
		fprintf(stderr, "La version du fichier %s n'est pas valide.\n", map);
		fclose(f);
		return NULL;
	}

	int full =0, cnt = 0;

	unsigned int flag = 0;

	while(full == 0){
		cnt = fscanf(f, "%s", img);

		if (strcmp(img, "carte") == 0){
			fscanf(f, "%s", img);
			char* tmp = malloc(sizeof(char)*(7+strlen(img)+1));
			sprintf(tmp,"images/%s", img);
			m->ppm = loadImage(tmp);
			free(tmp);
			flag |= 0x00000001;
			//printf("carte %d\n", flag);
		}else if (strcmp(img, "energie") == 0){
			fscanf(f, "%d", &num);
			energie = num;
			flag |= 0x00000010;//printf("energie %d\n", flag);
		}else if (strcmp(img, "chemin") == 0){
			fscanf(f, "%d %d %d",&r, &g, &b);
			tete->path.r = r;
			tete->path.g = g;
			tete->path.b = b;
			flag |= 0x00000100;//printf("chemin %d\n", flag);
		}else if (strcmp(img, "noeud") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			tete->color.r = r;
			tete->color.g = g;
			tete->color.b = b;
			flag |= 0x00001000;//printf("noeud %d\n", flag);
		}else if (strcmp(img, "construct") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			construct.r = r;
			construct.g = g;
			construct.b = b;
			flag |= 0x00010000;//printf("construct %d\n", flag);
		}else if (strcmp(img, "in") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			in.r = r;
			in.g = g;
			in.b = b;
			flag |= 0x00100000;//printf("in %d\n", flag);
		}else if (strcmp(img, "out") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			out.r = r;
			out.g = g;
			out.b = b;
			flag |= 0x01000000;//printf("out %d\n", flag);
		}else {
			long int longnum = strtol(img,NULL, 10);
			if(longnum != 0 && longnum != LONG_MAX && longnum != LONG_MIN){
				full=1;
				num = (int)longnum;
				flag |= 0x10000000;//printf("num %d\n", flag);
			}else{
				break;
			}
		}
	}
	//printf("flag %d %d %d\n", flag, 0x11111111, flag & 0x11111111);
	if(flag != 0x11111111)
	{
		if(flag & 0x00000001)
		{
			deleteImage(m->ppm);
		}
		free(m);
		free(tete);
		printf("Impossible de charger la map!\n");
		fclose(f);
		return NULL;
	}

	Node* tmp = tete;
	fscanf(f, "%f %f", &(tete->coord.x), &(tete->coord.y));
	tete->coord.y += 50.f;

	int nOk = 1;
	for(i=1; i<num; i++){
		Node* n = malloc(sizeof(Node));
		n->next = NULL;
		n->color = tete->color;
		n->path = tete->path;
		cnt = fscanf(f, "%f %f", &(n->coord.x), &(n->coord.y));
		if(cnt != 2)
		{
			free(n);
			nOk = 0;
			break;
		}
		n->coord.y += 50.f;
		tmp->next = n;
		tmp = n;
	}
	if(!nOk) {
		freeList(&tete);
		deleteImage(m->ppm);
		free(m);
		printf("Erreur lors de la lecture des nodes.\nImpossible de charger la map!\n");
		fclose(f);
		return NULL;
	} else {
		m->nodes = tete;
		m->camPos.x = 0; m->camPos.y = 0; m->camPos.z = .5f;
		m->camDir.x = 0; m->camDir.y = 0;
		m->drawNodes = 0;

		Color3ub old = {120,120,120};
		SDL_Surface* image = swapColorsImage(m->ppm, old, construct);	
		m->tex = loadTexture(image);
		SDL_FreeSurface(image);
		fclose(f);
	}
	return m;

}

int nodeOnMap(Node* n, Vector3 camPos)
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

void nodeXYCoordinates(Node* n, Vector3 camPos, float* x, float* y)
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

void drawNode(Node* n, Vector3 camPos){
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
				glVertex2f((n->coord.x-camPos.x), (n->coord.y-camPos.y));
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
					glVertex2f((n->coord.x-camPos.x), (n->coord.y-camPos.y));
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
	float texX = MAP_WIDTH/(m->ppm->w*1.0f);//*m->camPos.z));
	float deltaX = 0.f;
	if(m->camPos.x != 0)
		deltaX = m->camPos.x/(m->ppm->w*1.0f);//*m->camPos.z);

	float texY = MAP_HEIGHT/(m->ppm->h*1.0f);//*m->camPos.z));
	float deltaY = 0.f;

	if(m->camPos.y != 0)
		deltaY = m->camPos.y /(m->ppm->h*1.0f);//*m->camPos.z);
	
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

	if(m->drawNodes)
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

int collideWithMap(Map* m, Position pos, Position size, Vector3 camPos)
{
	pos.x -= size.x/2;
	//pos.x /= camPos.z;
	pos.y -= size.y/2;
	pos.y -= 50.f;
	//pos.y /= 

	if(pos.x-m->camPos.x < 0 || (pos.x+size.x)-m->camPos.x >= MAP_WIDTH || pos.y- m->camPos.y < 0 || (pos.y+size.y)- m->camPos.y >= MAP_HEIGHT)
		return 1;



	int h, w;
	for(w = (pos.x+2); w<(pos.x+size.x -2); w++)
		for(h = (pos.y+2); h<(pos.y+size.y -2); h++)
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
		m->camPos.x = (m->ppm->w-MAP_WIDTH);

	m->camPos.y += pos.y;
	if(m->camPos.y < 0)
		m->camPos.y = 0;
	else if(m->camPos.y+MAP_HEIGHT >= m->ppm->h)
		m->camPos.y = (m->ppm->h-MAP_HEIGHT);

}
