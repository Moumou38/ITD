#include "tower.h"

Tower* createTower(Position coord, TYPE_TOWER type){
	Tower* t = malloc(sizeof(Tower));
	t->coord = coord;
	t->type = type;
	t->size = 20;
	return t;
}

void drawTower(Tower* t)
{
	glColor3ub(255,0,0);//pour le moment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, t->tex);

	glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f);
		glVertex2f(t->coord.x, t->coord.y);

		glTexCoord2f(0.f,1.f);
		glVertex2f(t->coord.x, t->coord.y+(t->size));

		glTexCoord2f(1.f,1.f); 
		glVertex2f(t->coord.x+(t->size), t->coord.y+(t->size));

		glTexCoord2f(1.f, 0.f); 
		glVertex2f(t->coord.x+(t->size), t->coord.y);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void updateTower(Tower* t, GLuint elapsed)
{

}

void lookForBestTarget(Tower* t, List* monsters)
{

}
