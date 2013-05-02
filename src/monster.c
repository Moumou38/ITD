#include "monster.h"

const int Normal = 3;
const int Fast = 1;
const int Slow  =4;
const int Flyer = 2;

Monster* createMonster(TYPE_MONSTER type, Node* start, GLuint timer){
	Monster* m = malloc(sizeof(Monster));
	m->type = type;
	m->direction = start;
	m->coord.x = 0;
	m->coord.y = 0;
	m->life = 51;
	m->life_max = 100;
	m->msecSinceLastMvt = timer;
	return m;
}

void drawMonster(Monster* m)
{
	int size = 10.f;
	glColor3ub(0,0,255);//pour le moment
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m->tex);

	glBegin(GL_QUADS);
		//Monstre
		glTexCoord2f(0.f, 0.f);
		glVertex2f(m->coord.x, m->coord.y);

		glTexCoord2f(0.f,1.f);
		glVertex2f(m->coord.x, m->coord.y+size);

		glTexCoord2f(1.f,1.f); 
		glVertex2f(m->coord.x+size, m->coord.y+size);

		glTexCoord2f(1.f, 0.f); 
		glVertex2f(m->coord.x+size, m->coord.y);

		//Vie
		
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
		glColor3ub(0,255,0);
		if(m->life <= 75*m->life_max/100 && m->life > 50*m->life_max/100)
			glColor3ub(255,255,0);
		else if(m->life <= 50*m->life_max/100 && m->life > 25*m->life_max/100)
			glColor3ub(255,165,0);
		else if(m->life <= 25*m->life_max/100)
			glColor3ub(255,0,0);
		
		glTexCoord2f(0.f, 0.f);
		glVertex2f(m->coord.x, m->coord.y-6.f);

		glTexCoord2f(0.f,1.f);
		glVertex2f(m->coord.x, m->coord.y-3.f);

		glTexCoord2f(1.f,1.f); 
		glVertex2f(m->coord.x+(size*m->life/m->life_max), m->coord.y-3.f);

		glTexCoord2f(1.f, 0.f); 
		glVertex2f(m->coord.x+(size*m->life/m->life_max), m->coord.y-6.f);
	glEnd();
}

void updateMonster(Monster* m, GLuint elapsed)
{
	m->msecSinceLastMvt += elapsed;
	if(m->direction==NULL)
		return;
	//printf("%f %f %f %f\n", m->coord.x, m->coord.y, fabs(m->coord.x- m->direction->coord.x), fabs(m->coord.y-m->direction->coord.y));
	
	if(fabs(m->coord.x- m->direction->coord.x) < EPSILON && fabs(m->coord.y-m->direction->coord.y) < EPSILON)
		m->direction = m->direction->next;

	if(m->direction==NULL)
		return;

	switch(m->type){
		case NORMAL : {
			if(m->msecSinceLastMvt> Normal){
				float dx = m->direction->coord.x - m->coord.x;
				float dy = m->direction->coord.y - m->coord.y;
				float dist = sqrt(dx*dx + dy*dy);
				dx = dx/dist;
				dy = dy/dist;
				m->coord.x += dx;
				m->coord.y += dy;
				
				m->msecSinceLastMvt = 0;
			}
		}
		break;

		case FAST : {
			if(m->msecSinceLastMvt> Fast){
				float dx = m->direction->coord.x - m->coord.x;
				float dy = m->direction->coord.y - m->coord.y;
				float dist = sqrt(dx*dx + dy*dy);
				dx = dx/dist;
				dy = dy/dist;
				m->coord.x += dx*2;
				m->coord.y += dy*2;
				
				m->msecSinceLastMvt = 0;
			}
		}
		break;

		case SLOW : {
			if(m->msecSinceLastMvt> Slow){
				float dx = m->direction->coord.x - m->coord.x;
				float dy = m->direction->coord.y - m->coord.y;
				float dist = sqrt(dx*dx + dy*dy);
				dx = dx/dist;
				dy = dy/dist;
				m->coord.x += dx;
				m->coord.y += dy;
				
				m->msecSinceLastMvt = 0;
			}
		}
		break;

		case FLYER : {
			if(m->msecSinceLastMvt> Flyer){
				float dx = m->direction->coord.x - m->coord.x;
				float dy = m->direction->coord.y - m->coord.y;
				float dist = sqrt(dx*dx + dy*dy);
				dx = dx/dist;
				dy = dy/dist;
				m->coord.x += dx;
				m->coord.y += dy;
				
				m->msecSinceLastMvt = 0;
			}
		}
		break;
	}
	
}

int hasFinishedMonster(Monster* m)
{
	return (m->direction == NULL);
}
