#include "map.h"

Map* loadMap(char const* map){
	Map* m = malloc(sizeof(Map));
	FILE* f = NULL;
	char img[64];
	int num, r, g, b;
	Color3ub chemin, noeud, construct, in, out;


	if (map == NULL)
		return NULL;
	
	f = fopen(src, "rb");
	if(f == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier %s. Fin du programme.\n", src);
		return NULL;
	}else{
		printf("Fichier bien chargé !\n");
	}

	//Nom de l'image représentant la carte
	fscanf(f, "%s", img);
	printf("%s\n", img);
	if (strcmp(img, "@ITD") != 0){
		fprintf(stderr, "Le fichier n'est pas une carte valide. Fin du programme.\n");
		return NULL;
	}
	fscanf(f, "%d", num);
	printf("Vous utilisez la version du fichier %d\n", num);
	if (num != 1){
		fprintf(stderr, "La version du fichier n'est pas valide. Fin du programme.\n");
		return NULL;
	}

	int full =0;
	int cnt =0;

	while(full == 0){
		cnt = fscanf(f, "%s", img);
		printf("%s\n", img);

		if (strcmp(img, "carte") == 0){
			fscanf(f, "%s", img);
			printf("%s\n", img);
			m->ppm = openImage(img);
		}else if (strcmp(img, "energie") == 0){
			fscanf(f, "%d", &num);
			printf("%d\n", num);

		}else if (strcmp(img, "chemin") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			printf("%d %d %d\n", r, g, b);
			chemin.r = r;
			chemin.g = g;
			chemin.b = b;
		}else if (strcmp(img, "noeud") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			printf("%d %d %d\n", r, g, b);
			noeud.r = r;
			noeud.g = g;
			noeud.b = b;
		}else if (strcmp(img, "construct") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			printf("%d %d %d\n", r, g, b);
			construct.r = r;
			construct.g = g;
			construct.b = b;
		}else if (strcmp(img, "in") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			printf("%d %d %d\n", r, g, b);
			in.r = r;
			in.g = g;
			in.b = b;
		}else if (strcmp(img, "out") == 0){
			fscanf(f, "%d %d %d", &r, &g, &b);
			printf("%d %d %d\n", r, g, b);
			out.r = r;
			out.g = g;
			out.b = b;
		}else{
			printf("%s\n", img);
		}
	}

}

void drawMap(Map* m){

}

void deleteMap(Map* m){

}