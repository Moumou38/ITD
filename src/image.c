#include "image.h"

GLuint loadTexture(SDL_Surface* tex){

	GLuint textures;
	glGenTextures(1, &textures);
	
	glBindTexture(GL_TEXTURE_2D, textures);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	GLenum format;
	switch(tex->format->BytesPerPixel) {
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			if(tex->format->Rshift == 16)
				format = GL_BGRA;
			else
				format = GL_RGBA;
			break;
		default:
			fprintf(stderr, "Format des pixels de l’image non pris en charge\n");
			exit(-1);
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, format, GL_UNSIGNED_BYTE, tex->pixels); 
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return textures;
}

SDL_Surface* loadImage(const char* image){
	SDL_Surface* tex = IMG_Load(image);
	if (tex == NULL){
		fprintf(stderr, "Impossible d'afficher l'image. Fin du programme.\n");
		exit(-1);
	} else {
		return tex;
	}

}	

void deleteImage(SDL_Surface* tex){
	SDL_FreeSurface(tex);
}

void deleteTexture(GLuint image){
	glDeleteTextures(1, &image);
}


void GetPixel(SDL_Surface* surface, int x, int y, Uint8* r, Uint8* g, Uint8* b, Uint8* a) {
    int bpp = surface->format->BytesPerPixel;
    
    Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        
        break;

    case 2:

        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            *r = p[0];
            *g = p[1];
            *b = p[2];
        } else {
            *r = p[2];
            *g = p[1];
            *b = p[0];
        }
        break;

    case 4:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            *r = p[0];
            *g = p[1];
            *b = p[2];
			*a = p[3];
        } else {
            *r = p[3];
            *g = p[2];
            *b = p[1];
			*a = p[0];
        }
        break;
    }
}

void PutPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    
    Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16*)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32*)p = pixel;
        break;
    }
}

SDL_Surface* filterImage(SDL_Surface* s, SDL_Color filter)
{
	SDL_Surface* tmp = SDL_ConvertSurface(s, s->format, s->flags);
	Uint8 r,g,b,a;
	int i, j;
	Uint8* p = (Uint8*)tmp->pixels;
	int bpp = s->format->BytesPerPixel;
    
    
	for(i = 0; i<s->h; i++)
		for(j = 0; j<s->w; j++)
		{
			Uint8 color = p[i* tmp->pitch+j*bpp];
			SDL_GetRGBA(color, tmp->format,&r,&g,&b,&a);
			int r1 = (r+filter.r), g1 = (g+filter.g), b1=(g+filter.b);
			PutPixel(tmp, j,i, SDL_MapRGB(tmp->format, r1/2,g1/2,b1/2));
		}

	return tmp;
}

SDL_Surface* swapColorsImage(SDL_Surface* s, Color3ub old, Color3ub color)
{
	SDL_Surface* tmp = SDL_ConvertSurface(s, s->format, s->flags);
	Uint8 r,g,b,a;
	int i, j;
	for(i = 0; i<s->h; i++)
		for(j = 0; j<s->w; j++)
		{
			GetPixel(tmp, j,i, &r,&g,&b,&a);
			if(r == old.r && g == old.g && b == old.b)
				PutPixel(tmp, j,i, SDL_MapRGB(tmp->format, color.r, color.g, color.b));
		}

	return tmp;
}
