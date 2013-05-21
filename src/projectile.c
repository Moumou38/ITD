#include "projectile.h"

Projectile* createProjectile(Position pos, Position size, float damages, int line, float speed, Monster* target)
{
	Projectile* p = malloc(sizeof(Projectile));
	p->tex = getTexture("images/game/shoot.png");
	p->pos = pos;
	p->size = size;
	p->damages = damages;
	p->target = target;
	p->animTimer = SDL_GetTicks();
	p->lastUpdate = p->animTimer;
	p->offset = 0;
	p->line = line;
	p->hit = 0;
	p->speed = speed;
	return p;
}

void deleteProjectile(Projectile* p)
{
	if(p == NULL)
		return;

	free(p);
}

void drawProjectile(Projectile* p, Vector3 camPos)
{
	if(p == NULL)
		return;

	
	if(p->pos.x-camPos.x < 0 || p->pos.x-camPos.x > MAP_WIDTH || p->pos.y-camPos.y-50.f < 0 || p->pos.y-camPos.y-50.f > MAP_HEIGHT)
		return;

	glPushMatrix();
	glColor3ub(255,255,255);
	glTranslatef(p->pos.x-camPos.x, p->pos.y-camPos.y, 0);
	
	glScalef(p->size.x, p->size.y, 1.f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, p->tex);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
		glTexCoord2f(p->offset/2.f, p->line/4.f);
		glVertex2f(-0.5f, -0.5f);

		glTexCoord2f(p->offset/2.f,(p->line+1)/4.f);
		glVertex2f(-0.5f, 0.5f);

		glTexCoord2f((p->offset+1)/2.f,(p->line+1)/4.f); 
		glVertex2f(0.5f, 0.5f);

		glTexCoord2f((p->offset+1)/2.f,(p->line)/4.f); 
		glVertex2f(0.5f, -0.5f);
	glEnd();
	

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void updateProjectile(Projectile* p)
{
	if(p == NULL || p->hit == 1)
		return;


	Uint32 now = SDL_GetTicks();

	if(now-p->animTimer > 75)
	{
		p->offset++;
		if(p->offset > 1)
			p->offset = 0;

		p->animTimer = now;
	}

	if(p->target == NULL) {
		p->hit = 1;	
		return;
	}

	if(fabs(p->pos.x- p->target->coord.x) < EPSILON && fabs(p->pos.y-p->target->coord.y) < EPSILON) {
		p->hit = 1;
		p->target->life -= p->damages;	
	} else {
		float dx = p->target->coord.x - p->pos.x;
		float dy = p->target->coord.y - p->pos.y;
		float dist = sqrt(dx*dx + dy*dy);
		dx = dx/dist;
		dy = dy/dist;
		p->pos.x += dx*p->speed;
		p->pos.y += dy*p->speed;
	}
}
