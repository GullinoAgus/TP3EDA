#include "World.h"

World::World(Bitmap* texture, Blob* listaBlobs, Food* listaFood)
{
	this->texture = texture;
	this->listaBlobs = listaBlobs;
	this->listaFood = listaFood;
	this->velMax = 100.0F;
	this->modo = MODO1;
	this->initBlobCount = 10;
	this->foodCount = 10;
	this->velPercent = 1.0F;
	this->deathProbGOb = 0.0F;
	this->deathProbGb = 0.0F;
	this->deathProbBb = 0.0F;
	this->smellRadius = 100;
	this->randomJiggleLimit = 360.0F;
}

int World::initBlobList(EtaryGroup* eGroup)
{
	Blob* aux = NULL;


	for (unsigned int i = 0; i < this->initBlobCount ; i++)
	{
		this->listaBlobs = (Blob*)calloc(1, sizeof(Blob));
		this->listaBlobs->eGroup = eGroup;
		this->listaBlobs->next = aux;
		aux = this->listaBlobs;

	}

	return 0;
}


int World::initFoodList(Bitmap* texture)
{
	Food* aux = NULL;

	for (unsigned int i = 0; i < this->foodCount; i++)
	{
		this->listaFood = (Food*)calloc(1, sizeof(Food));
		this->listaFood->texture = texture;
		this->listaFood->next = aux;
		aux = this->listaFood;

	}

	return 0;
}
