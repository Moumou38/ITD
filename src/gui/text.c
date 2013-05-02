#include "gui/text.h"

TTF_Font *police;

void Text_Init()
{
	
}

void Text_Quit()
{

}

Text* createText(unsigned int id, char* text, SDL_Color color, int px, int py, int w, int h)
{    
	if(text == NULL) {
		return NULL;
	}	

	
	

	Text* t = malloc(sizeof(Text));
	t->text = NULL;
	int len = strlen(text);
	t->text = malloc(sizeof(char)*(len+1));
	strcpy(t->text, text);
	SDL_Surface* tmptext = SDL_DisplayFormatAlpha(TTF_RenderText_Solid(police, text, color));
	if(tmptext == NULL)
	{
		fprintf(stderr,"Erreur au chargement du texte %s", text);
		exit(-1);
	}
	t->tex[0] = loadTexture(tmptext);
	SDL_FreeSurface(tmptext);


	t->id = id;
	t->pos.x = px;
	t->pos.y = py;
	t->size.x = w;
	t->size.y = h;
	t->color = color;
	
	return t;
}

void setText(Text* t, const char* text)
{
	if(text == NULL || strcmp(t->text, text) == 0)
		return;

	deleteTexture(t->tex[0]);
	free(t->text);

	int len = strlen(text);
	t->text = malloc(sizeof(char)*(len+1));
	strcpy(t->text, text);

	SDL_Surface* tmptext = SDL_DisplayFormatAlpha(TTF_RenderText_Solid(police, text, t->color));
	if(tmptext == NULL)
	{
		fprintf(stderr,"Erreur au chargement du texte %s", text);
		exit(-1);
	}
	t->tex[0] = loadTexture(tmptext);
	SDL_FreeSurface(tmptext);
	//printf("edit\n");
}

void drawText(Text* t)
{
	if(t == NULL)
		return;

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	glDisable(GL_BLEND);
	//printf("dessin!\n");
}
/*
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
						}
					}

					if(hoverButton(b, p))
					{
						btnEv.action = GUI_BTEV_MOVED;
						*guiev = btnEv;
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
*/
void removeText(Text* t)
{
	if(t == NULL)
		return;

	//deleteTexture(t->tex[0]);
	if(t->text != NULL)
		free(t->text);
	
	free(t);
}

/*
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
		b->state = BS_DEFAULT;
		hoverButton(b,c);
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
*/
