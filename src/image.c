#include "image.h"

GLuint loadTexture(SDL_Surface* tex){

	GLuint textures;
	printf("Entrée\n");
	glGenTextures(1, &textures);
	
	glBindTexture(GL_TEXTURE_2D, textures);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	GLenum format;
	printf("juste avant celui là\n");
	printf("Format : %d\n", tex->format->BytesPerPixel);
	switch(tex->format->BytesPerPixel) {
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			fprintf(stderr, "Format des pixels de l’image non pris en charge\n");
			exit(-1);
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, format, GL_UNSIGNED_BYTE, tex->pixels); 
	printf("Tout est OK ! :D\n");
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return textures;
}

SDL_Surface* loadImage(char* image){
	SDL_Surface* tex = IMG_Load(image);
	if (tex == NULL){
		fprintf(stderr, "Impossible d'afficher l'image. Fin du programme.\n");
		exit(-1);
	} else {
		printf("L'image a été chargée correctement\n");
		return tex;
	}

}	

void deleteImage(SDL_Surface* tex){
	SDL_FreeSurface(tex);
}

void deleteTexture(GLuint image){
	glDeleteTextures(1, &image);
}