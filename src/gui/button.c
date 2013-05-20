#include "gui/button.h"

Button* createButton(unsigned int id, char* text, char* imagefile, SDL_Color color, int px, int py, int w, int h)
{    
	
	SDL_Color hovered = {180, 180, 180};
	SDL_Color pressed = {120, 120, 120};
	SDL_Color gris = {50, 50, 50};
	TTF_Font *police = TTF_OpenFont("Ketchum.ttf", 65);
	if(police == NULL)
	{
		fprintf(stderr,"Erreur au chargement de la police Ketchum.ttf");
		exit(-1);
	}

	Button* b = malloc(sizeof(Button));
	if(text == NULL)
		b->text = NULL;
	else {
		int len = strlen(text);
		b->text = malloc(sizeof(char)*(len+1));
		strcpy(b->text, text);
		SDL_Surface* tmptext = TTF_RenderText_Blended(police, text, color);
		if(tmptext == NULL)
		{
			fprintf(stderr,"Erreur au chargement du bouton %s\n", text);
			exit(-1);
		}
		b->tex[0] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);

		tmptext = TTF_RenderText_Blended(police, text, hovered);
		b->tex[1] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);

		tmptext = TTF_RenderText_Blended(police, text, pressed);
		b->tex[2] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);

		tmptext = TTF_RenderText_Blended(police, text, gris);
		b->tex[3] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);
	}

	if(imagefile != NULL)
	{
		SDL_Surface* image = IMG_Load(imagefile);
		b->tex[0] = loadTexture(image);

		SDL_Surface* tmptext = filterImage(image, hovered);
		b->tex[1] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);

		tmptext = filterImage(image, pressed);
		b->tex[2] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);

		tmptext = filterImage(image, gris);
		b->tex[3] = loadTexture(tmptext);
		SDL_FreeSurface(tmptext);
		SDL_FreeSurface(image);
	}
	b->id = id;
	b->pos.x = px;
	b->pos.y = py;
	b->size.x = w;
	b->size.y = h;
	b->state = BS_DEFAULT;
	b->flags = BF_ENABLED;
	TTF_CloseFont(police);
	return b;
}

void drawButton(Button* b)
{
	if(b == NULL)
		return;

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, b->tex[b->state]);

	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(b->pos.x, b->pos.y);
		glTexCoord2f(0,0.99); glVertex2f(b->pos.x, b->pos.y+b->size.y);
		glTexCoord2f(0.99,0.99); glVertex2f(b->pos.x+b->size.x, b->pos.y+b->size.y);
		glTexCoord2f(0.99,0); glVertex2f(b->pos.x+b->size.x, b->pos.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//printf("dessin!\n");
}

int injectEventToButton(Button* b, SDL_Event* event, GUI_ButtonEvent* guiev)
{
	GUI_ButtonEvent btnEv = { GUI_ET_BUTTON, b->id, GUI_BTEV_NONE};
	if(b->flags & BF_ENABLED) 
	{
		switch(event->type)
		{
			case SDL_MOUSEMOTION:
				{
					Position p = {event->motion.x, event->motion.y};
					ButtonState old = b->state;
					if(mouseInButton(b,p)) {
						int x = event->motion.xrel;
						int y = event->motion.yrel;
						if(b->flags & BF_MOVABLE && isButtonClicked(b))
						{
							b->pos.x += x;
							b->pos.y += y;
							btnEv.action = GUI_BTEV_MOVED;
							*guiev = btnEv;
							break;
						} else if(hoverButton(b,p)){
							btnEv.action = GUI_BTEV_HOVER;
							*guiev = btnEv;
							break;
						}
					} else {
						
						b->state = BS_DEFAULT;
						if(b->state == BS_DEFAULT && old == BS_HOVER)
						{
							//printf("toto\n");
							btnEv.action = GUI_BTEV_LEFTHOVER;
							*guiev = btnEv;
						}
					}
				}					
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					if(b->state != BS_PRESSED) {
						Position p;
						p.x = event->button.x;
						p.y = event->button.y;
						if(clickedButton(b, p, 1))
						{
							btnEv.action = GUI_BTEV_PRESSED;
							*guiev = btnEv;
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				{
					if(b->state == BS_PRESSED) {
						Position p;
						p.x = event->motion.x;
						p.y = event->motion.y;
						p.y = event->button.y;
						if(clickedButton(b, p, 0))
						{
							btnEv.action = GUI_BTEV_RELEASED;
							*guiev = btnEv;
						}
					}
				}
				break;
			default:
				break;
		}
	}
	return 0;
}

void removeButton(Button* b)
{
	int i;
	for(i = 0; i<4; ++i)
		deleteTexture(b->tex[i]);
	free(b->text);
	free(b);
}

int hoverButton(Button* b, Position c) 
{
	if(!isButtonClicked(b)) {
		if(mouseInButton(b,c)) {
			b->state = BS_HOVER;
			return 1;
		}
		else {
			if(b->state != BS_DEFAULT)
			{
				b->state = BS_DEFAULT;
				return 1;
			}
		}
	}
	return 0;
}

int isButtonClicked(Button* b)
{
	return b->state == BS_PRESSED;
}

int clickedButton(Button* b, Position c, int pressed)
{
	if(pressed) {
		if(b->state != BS_PRESSED && mouseInButton(b, c))
		{
			b->state = BS_PRESSED;
			return 1;
		}
	} else {
		if(b->state == BS_PRESSED && mouseInButton(b, c)) {
			b->state = BS_HOVER;
			return 1;
		}
		else {
			b->state = BS_DEFAULT;
		}	
	}
	return 0;
}

int mouseInButton(Button* b, Position c)
{
	if(b != NULL && 
		(b->pos.x > c.x ||	
		b->pos.x+b->size.x < c.x ||
		b->pos.y > c.y ||	
		b->pos.y+b->size.y < c.y))
		return 0;
	
	return 1;
}

void enableButtonFlag(Button* b, ButtonFlags flags)
{
	b->flags |= flags;
	if(b->flags & BF_ENABLED)
		b->state = BS_DEFAULT;
}

void disableButtonFlag(Button* b, ButtonFlags flags)
{
	b->flags &= ~flags;
	if(!(b->flags & BF_ENABLED))
		b->state = BS_DISABLED;
	
}
