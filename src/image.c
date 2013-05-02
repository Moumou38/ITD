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
			format = GL_BGRA;
			break;
		default:
			fprintf(stderr, "Format des pixels de l’image non pris en charge\n");
			exit(-1);
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, format, GL_UNSIGNED_BYTE, tex->pixels); 
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return textures;
}

SDL_Surface* loadImage(char* image){
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
/*
void SDL_GetRGBA(SDL_Surface* s, int x, int y, char* red, char* green, char* blue, char* alpha)
{
	switch(s->format->BytesPerPixel)
	{
		case 4:
			{
				int color = s->pixels[y*s->w+y];
				*red = color << 16;
				*green = color << 8;
				*blue = color;
				*alpha = color << 24;
			}
			break;
		default:
			break;
	}
}*/

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

SDL_Surface* paintImage(SDL_Surface* s, Color3ub color)
{
	SDL_Surface* tmp = SDL_ConvertSurface(s, s->format, s->flags);
	Uint8 r,g,b,a;
	int i, j;
	Uint8* p = (Uint8*)tmp->pixels;
	int bpp = s->format->BytesPerPixel;
    
    
	for(i = 0; i<s->h; i++)
		for(j = 0; j<s->w; j++)
		{
			Uint8 c = p[i* tmp->pitch+j*bpp];
			SDL_GetRGBA(c, tmp->format,&r,&g,&b,&a);
			if(r == 120 && g == 120 && b == 120)
				PutPixel(tmp, j,i, SDL_MapRGB(tmp->format, color.r, color.g, color.b));
		}

	return tmp;
}
