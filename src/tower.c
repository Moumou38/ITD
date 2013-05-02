#include "tower.h"

const int Rocket_Dmg = 10;
const int Laser_Dmg = 5;
const int Machinegun_Dmg= 3;
const int Hybride_Dmg = 8;

const int Rocket_Time= 20;
const int Laser_Time = 10;
const int Machinegun_Time = 5;
const int Hybride_Time = 15;

Tower* createTower(Position coord, TYPE_TOWER type){
	Tower* t = malloc(sizeof(Tower));
	t->coord = coord;
	t->type = type;
	t->size = 20;
	t->range = 100;
	t->msecSinceLastShot = 0;
	t->target = NULL;
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
		glVertex2f(t->coord.x, t->coord.y+(float)(t->size));

		glTexCoord2f(1.f,1.f); 
		glVertex2f(t->coord.x+(float)(t->size), t->coord.y+(float)(t->size));

		glTexCoord2f(1.f, 0.f); 
		glVertex2f(t->coord.x+(float)(t->size), t->coord.y);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void updateTower(Tower* t, GLuint elapsed)
{
	t->msecSinceLastShot += elapsed;
	if(t->msecSinceLastShot>Rocket_Time){
		/*if(t->target != NULL){
			//
			t->target->life -= Rocket_Dmg;
			t->msecSinceLastShot=0;
		}*/
		if(t->target != NULL){
			shoot(t, t->target);
			if(isDead(t->target) || outOfRange(t->coord, t->target->coord, t->range));
				t->target = NULL;
			//printf("shoot %p \n", t->target);
			t->msecSinceLastShot = 0;
		}
	}
	/*switch(t->type){
		case ROCKET :{
			if(t->msecSinceLastShot>Rocket_Time){
				if(t->target != NULL){
					//shoot(t, t->target);
					t->target->life -= Rocket_Dmg;
					t->msecSinceLastShot=0;
				}
			}
		}
		break;

		case LASER : {
			if(t->msecSinceLastShot>Laser_Time){
				if(t->target != NULL){
					shoot(t, t->target);
					t->msecSinceLastShot=0;
				}
			}
		}
		break;

		case MACHINEGUN :{
			if(t->msecSinceLastShot>Machinegun_Time){
				if(t->target != NULL){
					shoot(t, t->target);
					t->msecSinceLastShot=0;
				}
			}
		}
		break;

		case HYBRIDE : {
			if(t->msecSinceLastShot>Hybride_Time){
				if(t->target != NULL){
					shoot(t, t->target);
					t->msecSinceLastShot=0;
				}
			}
		}
		break;

		default : 
			break;
	}*/

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
		Monster* m = list_get(monsters, 0);
		float tmp = sqrt((m->coord.x - t->coord.x)*(m->coord.x - t->coord.x)+(m->coord.y - t->coord.y)*(m->coord.y - t->coord.y));
		if(tmp <= t->range && (best == NULL || bestDist > tmp))
		{
			best = m;
			bestDist = tmp;
			//printf("best %p\n", best);
		}
	}
	
	t->target = best;
}

void shoot(Tower* t, Monster* target){
	if(t == NULL || target == NULL)
		return;

	if(t->type == ROCKET)
		target->life -= Rocket_Dmg;
	else if(t->type == LASER)
		target->life -= Laser_Dmg;
	else if(t->type == MACHINEGUN)
		target->life -= Machinegun_Dmg;
	else if(t->type == HYBRIDE)
		target->life -= Hybride_Dmg;

}

int outOfRange(Position p1, Position p2, float range){
	float dist = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	return (dist > range);
}
