#include "monster.h"

// number of movements every 1/10 sec.
const float Normal = 4;
const float Fast = 8;
const float Slow  = 2;
const float Flyer = 4;

Monster* createMonster(TYPE_MONSTER type, float life, Node* start, GLint timer){
	Monster* m = malloc(sizeof(Monster));
	m->type = type;
	m->direction = start;
	m->coord.x = start->coord.x;
	m->coord.y = start->coord.y;
	m->life = life;
	m->life_max = life;
	m->msecSinceLastMvt = SDL_GetTicks()+timer;
	m->deltaOnPause = -timer;
	m->invulnerable = 1;
	Position norm = {18.f, 43.f}, fly = {51.f, 45.f};
	m->size = norm;
	switch(type) {
		case NORMAL:
			m->tex = getTexture("images/game/pokeball.png");
			m->mvtTime = 100/Normal;
			break;
		case FLYER:
			m->tex = getTexture("images/game/flyer.png");
			m->size = fly;
			while(m->direction->next != NULL)
				m->direction = m->direction->next;
			m->mvtTime = 100/Flyer;
			break;
		case FAST:
			m->tex = getTexture("images/game/pokeballY.png");
			m->mvtTime = 100/Fast;
			break;
		case SLOW:
			m->tex = getTexture("images/game/pokeballB.png");
			m->mvtTime = 100/Slow;
			break;
		default:
			m->tex = 0;
			break;
	}
	
	m->animOffset = 0;
	m->animTimer = SDL_GetTicks();
	m->animUp = 1;

	return m;
}

void drawMonster(Monster* m, Vector3 camPos)
{
	if(m->invulnerable)
		return;

	if(m->coord.x-camPos.x < 0 || m->coord.x-camPos.x > MAP_WIDTH || m->coord.y-camPos.y-50.f < 0 || m->coord.y-camPos.y-50.f > MAP_HEIGHT)
		return;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m->tex);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(m->coord.x-camPos.x, m->coord.y-camPos.y, 0.f);
	glPushMatrix();
	glScalef(m->size.x, m->size.y, 1.f);
	glBegin(GL_QUADS);
		//Monstre
		glColor3ub(255,255,255);
		glTexCoord2f((m->animOffset+0.01f)/5.f,1.f);
		glVertex2f(-0.5, 0.5);

		glTexCoord2f((m->animOffset+0.01f)/5.f, 0.01f);
		glVertex2f(-0.5, -0.5);

		glTexCoord2f((m->animOffset+0.98f)/5.f, 0.01f);
		glVertex2f(0.5, -0.5);

		glTexCoord2f((m->animOffset+0.98f)/5.f,1.f);
		glVertex2f(0.5, 0.5);
	glEnd();
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();

	glBegin(GL_QUADS);
		glColor3ub(0,255,0);
		if(m->life <= 75*m->life_max/100 && m->life > 50*m->life_max/100)
			glColor3ub(255,255,0);
		else if(m->life <= 50*m->life_max/100 && m->life > 25*m->life_max/100)
			glColor3ub(255,165,0);
		else if(m->life <= 25*m->life_max/100)
			glColor3ub(255,0,0);
		
		glTexCoord2f(0.f, 0.f);
		glVertex2f(-m->size.x/2.f, m->size.y/2.f+6.f);

		glTexCoord2f(0.f,1.f);
		glVertex2f(-m->size.x/2.f, m->size.y/2.f+3.f);

		glTexCoord2f(1.f,1.f); 
		glVertex2f((m->size.x*m->life/m->life_max)-m->size.x/2.f, m->size.y/2.f+3.f);

		glTexCoord2f(1.f, 0.f); 
		glVertex2f((m->size.x*m->life/m->life_max)-m->size.x/2.f, m->size.y/2.f+6.f);
	glEnd();
	glPopMatrix();
}

void updateMonster(Monster* m)
{
	//printf("toto\n");
	//m->msecSinceLastMvt += elapsed;
	int now = SDL_GetTicks();

	if(now-m->animTimer > 75)
	{
		m->animTimer = now;
		if(m->animUp && m->animOffset == 4)
		{
			m->animOffset--;
			m->animUp = 0;
		} else if(m->animUp)
			m->animOffset++;
		else if(!m->animUp && m->animOffset == 0)
		{
			m->animOffset++;
			m->animUp = 1;
		} else if(!m->animUp)
			m->animOffset--;

	}
	//printf("%d %d %d\n", m->msecSinceLastMvt, now, now-m->msecSinceLastMvt);
	
	if(m->direction==NULL)
		return;
	//printf("%f %f %f %f\n", m->coord.x, m->coord.y, fabs(m->coord.x- m->direction->coord.x), fabs(m->coord.y-m->direction->coord.y));
	
	if(fabs(m->coord.x- m->direction->coord.x) < EPSILON && fabs(m->coord.y-m->direction->coord.y) < EPSILON)
		m->direction = m->direction->next;

	if(m->direction==NULL)
		return;

	
	
	if((now-m->msecSinceLastMvt)> m->mvtTime){
		m->invulnerable = 0;
		float dx = m->direction->coord.x - m->coord.x;
		float dy = m->direction->coord.y - m->coord.y;
		float dist = sqrt(dx*dx + dy*dy);
		dx = dx/dist;
		dy = dy/dist;		
		m->coord.x += dx;
		m->coord.y += dy;
		//printf("move\n");
		m->msecSinceLastMvt = now;
	}
}

int isDead(Monster* m){
	return (m->life <= 0);
}

int hasFinishedMonster(Monster* m)
{
	return (m->direction == NULL);
}

void onPauseMonster(Monster* m)
{
	m->deltaOnPause = m->msecSinceLastMvt-SDL_GetTicks();
	printf("delta: %d\n", m->deltaOnPause);
}

void onResumeMonster(Monster* m)
{
	m->msecSinceLastMvt = SDL_GetTicks()+m->deltaOnPause;
	printf("delta: %d\n", m->deltaOnPause);
}

void deleteMonster(Monster* m){
	free(m);
}
