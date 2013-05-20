#include "tower.h"

const float Rocket_Range = 200;
const int Rocket_Dmg = 100;
const int Rocket_Time= 500;
const int Rocket_Cost= 80;

const float Laser_Range = 140;
const int Laser_Dmg = 50;
const int Laser_Time = 100;
const int Laser_Cost = 50;

const float Machinegun_Range= 100;
const int Machinegun_Dmg= 10;
const int Machinegun_Time = 100;
const int Machinegun_Cost = 25;

const float Hybrid_Range = 200;
const int Hybrid_Dmg = 20;
const int Hybrid_Time = 200;
const int Hybrid_Cost = 80;

Tower* createTower(Position coord, TYPE_TOWER type){
	Tower* t = malloc(sizeof(Tower));
	t->coord = coord;
	t->type = type;
	t->size = 64;
	t->selected = 0;
	t->lastUpdate = SDL_GetTicks();
	switch(type) {
		case ROCKET:
			t->range = Rocket_Range;
			t->msecSinceLastShot = Rocket_Time;
			t->damages = Rocket_Dmg;
			t->reloadTime = Rocket_Time;
			t->tex = getTexture("images/game/rocket.png");
			break;
		case LASER:
			t->range = Laser_Range;
			t->msecSinceLastShot = Laser_Time;
			t->damages = Laser_Dmg;
			t->reloadTime = Laser_Time;
			t->tex = getTexture("images/game/laser.png");
			break;
		case MACHINEGUN:
			t->range = Machinegun_Range;
			t->msecSinceLastShot = Machinegun_Time;
			t->damages = Machinegun_Dmg;
			t->reloadTime = Machinegun_Time;
			t->tex = getTexture("images/game/machinegun.png");
			break;
		case HYBRID:
			t->range = Hybrid_Range;
			t->msecSinceLastShot = Hybrid_Time;
			t->damages = Hybrid_Dmg;
			t->reloadTime = Hybrid_Time;
			t->tex = getTexture("images/game/hybrid.png");
			break;
		default:
			break;
	}
	
	t->angle = 0.f;
	t->target = NULL;
	return t;
}

void drawTower(Tower* t, Vector3 camPos)
{
	drawTower2(t->type, t->coord, t->angle, t->selected, camPos);
	if(t->msecSinceLastShot < 100 && t->target != NULL)
	{
		glColor3ub(255,0,0);
		glBegin(GL_LINES);
			glVertex2f(t->coord.x-camPos.x, t->coord.y-camPos.y);
			glVertex2f(t->target->coord.x+5.f -camPos.x, t->target->coord.y+5.f-camPos.y);
		glEnd();
	}
}

void drawTower2(TYPE_TOWER type, Position pos, float angle, int selected, Vector3 camPos)
{
	if(pos.x-camPos.x  < 0 || pos.x-camPos.x > MAP_WIDTH || pos.y-camPos.y-50.f < 0 || pos.y-camPos.y-50.f > MAP_HEIGHT)
		return;

	Position size = getTowerSize(type);
	float range = getTowerRange(type);
	glPushMatrix();
	glColor3ub(255,255,255);//pour le moment
	glTranslatef(pos.x-camPos.x, pos.y-camPos.y, 0);
	
	glPushMatrix();
	glScalef(size.x, size.y, 1.f);
	
	glPushMatrix();
	glRotatef(angle, 0,0,1.f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTowerTexture(type));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f);
		glVertex2f(-0.5f, -0.5f);

		glTexCoord2f(0.f,1/4.f);
		glVertex2f(-0.5f, 0.5f);

		glTexCoord2f(1/4.f,1/4.f); 
		glVertex2f(0.5f, 0.5f);

		glTexCoord2f(1/4.f, 0.f); 
		glVertex2f(0.5f, -0.5f);
	glEnd();
	

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	/*if(selected) {
		glBegin(GL_LINE_LOOP);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(-0.5f, 0.5f);
			glVertex2f(0.5f, 0.5f);
			glVertex2f(0.5f, -0.5f);
		glEnd();
	}*/
	glPopMatrix();

	if(selected) {
		int i;
		float angle = 2.0*M_PI/(32*1.0f);
		float currangle = 0.0;
		
		glColor3ub(255,255,255);
		glBegin(GL_LINE_LOOP);
		for(i = 0; i<32; ++i) {
			glVertex2d(cos(currangle)*range,sin(currangle)*range);
			currangle += angle;
		}
		glEnd();
		
	}
	glPopMatrix();
}

void updateTower(Tower* t)
{
	int now = SDL_GetTicks();
	t->msecSinceLastShot += now - t->lastUpdate;
	if(t->msecSinceLastShot>t->reloadTime){
		if(t->target != NULL){
			shoot(t, t->target);
			t->msecSinceLastShot = 0;
			if(isDead(t->target) || outOfRange(t->coord, t->target->coord, t->range)) {
				t->target = NULL;
			}
		}
	}

	t->lastUpdate = now;

}

void lookForBestTarget(Tower* t, List* monsters)
{
	if(t->target != NULL)
		return;

	Monster* best = NULL;
	float bestDist = 0;
	int i;
	for(i = 0; i<list_size(monsters); i++)
	{
		Monster* m = list_get(monsters, i);
		float tmp = sqrt((m->coord.x - t->coord.x)*(m->coord.x - t->coord.x)+(m->coord.y - t->coord.y)*(m->coord.y - t->coord.y));
		if(tmp <= t->range && (best == NULL || bestDist > tmp))
		{
			best = m;
			bestDist = tmp;
			
		}
	}
	
	t->target = best;
}

void shoot(Tower* t, Monster* target){
	if(t == NULL || target == NULL)
		return;

	if(t->type == ROCKET)
		target->life -= ((100-target->resist.resistRocket)*Rocket_Dmg)/100;
	else if(t->type == LASER)
		target->life -= ((100-target->resist.resistRocket)*Laser_Dmg)/100;
	else if(t->type == MACHINEGUN)
		target->life -= ((100-target->resist.resistRocket)*Machinegun_Dmg)/100;
	else if(t->type == HYBRID)
		target->life -= ((100-target->resist.resistRocket)*Hybrid_Dmg)/100;

}

int outOfRange(Position p1, Position p2, float range){
	float dist = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	return (dist > range);
}

void onResumeTower(Tower* t)
{
	t->msecSinceLastShot = SDL_GetTicks();
}

int getTowerCost(TYPE_TOWER type)
{
	switch(type) {
		case ROCKET:
			return Rocket_Cost;
		case LASER:
			return Laser_Cost;
		case MACHINEGUN:
			return Machinegun_Cost;
		case HYBRID:
			return Hybrid_Cost;
		default:
			return 10;
	}
}

float getTowerRange(TYPE_TOWER type)
{
	switch(type) {
		case ROCKET:
			return Rocket_Range;
		case LASER:
			return Laser_Range;
		case MACHINEGUN:
			return Machinegun_Range;
		case HYBRID:
			return Hybrid_Range;
		default:
			return 0;
	}
}

void selectTower(Tower* t, Position coord)
{
	if(coord.x >= t->coord.x-t->size/2.f && coord.x <= t->coord.x+t->size/2.f && coord.y >= t->coord.y-t->size/2.f && coord.y <= t->coord.y+t->size/2.f)
		t->selected = 1;
	else
		t->selected = 0;
}

Position getTowerSize(TYPE_TOWER type)
{
	Position p = {64.f, 64.f};
	return p;
}

GLuint getTowerTexture(TYPE_TOWER type)
{
	switch(type) {
		case ROCKET:
			return getTexture("images/game/rocket.png");
		case LASER:
			return getTexture("images/game/laser.png");
		case MACHINEGUN:
			return getTexture("images/game/machinegun.png");
		case HYBRID:
			return getTexture("images/game/hybrid.png");
		default:
			return 0;
	}
}

const char* getTowerName(TYPE_TOWER type)
{
	switch(type) {
		case ROCKET:
			return "Rocket";
		case LASER:
			return "Laser";
		case MACHINEGUN:
			return "Machinegun";
		case HYBRID:
			return "Hybrid";
		default:
			return 0;
	}
}

int collideWithTower(Tower* t, Position pos, Position size)
{
	if(pos.x+size.x/2.f  <=  t->coord.x-t->size/2.f || 
		pos.x-size.x/2.f >= t->coord.x+t->size/2.f || 
		pos.y+size.y/2.f <=  t->coord.y-t->size/2.f || 
		pos.y-size.y/2.f >= t->coord.y+t->size/2.f)
		return 0;
 	
	return 1;
}
