#include "resource.h"

typedef struct {
	char* name;
	GLuint data;
} Resource;

List* textures = NULL;

void deleteResource(Resource* r)
{
	if(r == NULL)
		return;

	printf("Freed: %s\n", r->name);
	free(r->name);
	deleteTexture(r->data);
	free(r);
}

void initResourcesManager()
{
	if(textures == NULL) {
		textures = list_init();
		printf("Resources Manager Initialized\n");
	}
}

void deleteResourcesManager()
{
	while(list_size(textures)) 
	{
		Resource* t = list_get(textures, 0);
		deleteResource(t);
		list_remove(textures, 0);
	}
	list_delete(textures);
	printf("Resources Manager Destroyed\n");
}

Resource* createResource(const char* name)
{
	Resource* r = malloc(sizeof(Resource));
	int len = strlen(name)+1;
	r->name = malloc(sizeof(char)*len);
	strcpy(r->name, name);
	SDL_Surface* tmp = loadImage(name);
	r->data = loadTexture(tmp);
	SDL_FreeSurface(tmp);
	printf("Loaded: %s\n", name);
	return r;
}

GLuint getTexture(const char* name)
{
	if(name == NULL)
		return 0;

	int i;
	for(i = 0; i<list_size(textures); i++)
	{
		Resource* r = list_get(textures, i);
		if(strcmp(name, r->name) == 0)
			return r->data;
	}

	Resource* r = createResource(name);
	list_append(textures, r);
	return r->data;
}
