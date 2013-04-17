#include "monster.h"

Monster* createMonster(TYPE_MONSTER type, Node* start){
	Monster* m = malloc(sizeof(Monster));
	m->type = type;
	m->direction = start;
	m->coord.x = 0;
	m->coord.y = 0;
	m->life = 50;

	return m;
}

void drawMonster(Monster* m)
{
	glColor3ub(0,0,255);//pour le moment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m->tex);

	glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f);
		glVertex2f(m->coord.x, m->coord.y);

		glTexCoord2f(0.f,1.f);
		glVertex2f(m->coord.x, m->coord.y+10.f);

		glTexCoord2f(1.f,1.f); 
		glVertex2f(m->coord.x+10.f, m->coord.y+10.f);

		glTexCoord2f(1.f, 0.f); 
		glVertex2f(m->coord.x+10.f, m->coord.y);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void updateMonster(Monster* t, GLuint elapsed)
{
	
}

int hasFinishedMonster(Monster* m)
{
	return (m->direction == NULL);
}
