#include "gui/gui_image.h"

Image* createImage(unsigned int id, const char* image, int px, int py, float sizex, float sizey)
{    
	if(image == NULL) {
		return NULL;
	}	

	Image* t = malloc(sizeof(Image));

	SDL_Surface* tmptext = IMG_Load(image);
	if(tmptext == NULL)
	{
		fprintf(stderr,"Erreur au chargement de l'image %s", image);
		exit(-1);
	}
	t->tex[0] = loadTexture(tmptext);

	t->id = id;
	t->pos.x = px;
	t->pos.y = py;
	t->size.x = tmptext->w*sizex;
	t->size.y = tmptext->h*sizey;
	SDL_FreeSurface(tmptext);
	return t;
}

void drawImage(Image* t)
{
	if(t == NULL)
		return;

	//glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, t->tex[0]);
	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(t->pos.x, t->pos.y);
		glTexCoord2f(0,0.99); glVertex2f(t->pos.x, t->pos.y+t->size.y);
		glTexCoord2f(0.99,0.99); glVertex2f(t->pos.x+t->size.x, t->pos.y+t->size.y);
		glTexCoord2f(0.99,0); glVertex2f(t->pos.x+t->size.x, t->pos.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//printf("dessin!\n");
}

void removeImage(Image* t)
{
	if(t == NULL)
		return;
	
	free(t);
}
