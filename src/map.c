#include "map.h"

const static float MAP_WIDTH = 600.f;
const static float MAP_HEIGHT = 550.f;

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
	//printf("%s\n", img);
	if (strcmp(img, "@ITD") != 0){
		fprintf(stderr, "Le fichier n'est pas une carte valide. Fin du programme.\n");
		return NULL;
	}
	fscanf(f, "%d", &num);
	//printf("Vous utilisez la version du fichier %d\n", num);
	if (num != 1){
		fprintf(stderr, "La version du fichier n'est pas valide. Fin du programme.\n");
		return NULL;
	}

	int full =0;
	int cnt =0;

	while(full == 0){
		cnt = fscanf(f, "%s", img);
		//printf("%s\n", img);

		if (strcmp(img, "carte") == 0){
			fscanf(f, "%s", img);
			//printf("%s\n", img);
			char* tmp = malloc(sizeof(char)*(7+strlen(img)+1));
			sprintf(tmp,"images/%s", img);
			m->ppm = loadImage(tmp);
			free(tmp);
			//printf("juste après\n");
		}else if (strcmp(img, "energie") == 0){
			fscanf(f, "%d", &num);
			//printf("%d\n", num);
			energie = num;
		}else if (strcmp(img, "chemin") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			//printf("%d %d %d\n", r, g, b);
			chemin.r = r;
			chemin.g = g;
			chemin.b = b;
		}else if (strcmp(img, "noeud") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			//printf("%d %d %d\n", r, g, b);
			tete->color.r = r;
			tete->color.g = g;
			tete->color.b = b;
		}else if (strcmp(img, "construct") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			//printf("%d %d %d\n", r, g, b);
			construct.r = r;
			construct.g = g;
			construct.b = b;
		}else if (strcmp(img, "in") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			//printf("%d %d %d\n", r, g, b);
			in.r = r;
			in.g = g;
			in.b = b;
		}else if (strcmp(img, "out") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			//printf("%d %d %d\n", r, g, b);
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
	//printf("nombre de node %d\n", num);
	Node* tmp = tete;
	fscanf(f, "%f %f", &(tete->coord.x), &(tete->coord.y));
	tete->coord.x = (tete->coord.x/m->ppm->w)*MAP_WIDTH;
	tete->coord.y = (tete->coord.y/m->ppm->h)*MAP_HEIGHT +50.f;

	for(i=1; i<num; i++){
		Node* n = malloc(sizeof(Node));
		n->next = NULL;
		n->color = tete->color;
		fscanf(f, "%f %f", &(n->coord.x), &(n->coord.y));
		n->coord.x = (n->coord.x/m->ppm->w)*MAP_WIDTH;
		n->coord.y = (n->coord.y/m->ppm->h)*MAP_HEIGHT +50.f;
		//printf("%f %f\n", n->coord.x, n->coord.y);
		tmp->next = n;
		tmp = n;
	}
	m->nodes = tete;
	SDL_Surface* image = paintImage(m->ppm, construct);	
	m->tex = loadTexture(image);
	SDL_FreeSurface(image);

	printf("map loaded\n");
//	exit(0);
	return m;

}

void drawNode(Node* n){
		glBegin(GL_LINE_STRIP);
			while(n != NULL){
				glColor3ub(n->color.r, n->color.g, n->color.b);
				glVertex2f(n->coord.x, n->coord.y);
				//printf("%f %f\n", n->coord.x/100.f, n->coord.y/100.f);
				n = n->next;
				
			}
		glEnd();
//	printf("end\n");
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
	//printf("begin\n");
	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m->tex);

	glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f);
		glVertex2f(0.f, 50.f);

		glTexCoord2f(0.f,1);
		glVertex2f(0.f, MAP_HEIGHT+50.f);

		glTexCoord2f(1,1); 
		glVertex2f(MAP_WIDTH, MAP_HEIGHT+50.f);

		glTexCoord2f(1, 0.f); 
		glVertex2f(MAP_WIDTH, 50.f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	drawNode(m->nodes);
}

void deleteMap(Map* m){
	deleteImage(m->ppm);
	deleteTexture(m->tex);
	freeNode(&(m->nodes));
}
