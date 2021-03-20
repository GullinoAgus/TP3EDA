#include "World.h"

World::World(const char* textureDirectory, ModoType modo, float maxVel, unsigned int initBlobCant, unsigned int initFoodCant)
{
	this->texture = new Bitmap(textureDirectory);
	for (int i = 0; i < initBlobCant; i++)
	{
		this->arrBlobs[i].isAlive = 1;
		this->arrBlobs[i].pos.x = (rand() % (this->texture->width - this->arrBlobs[i].eGroup->texture->width));
		this->arrBlobs[i].pos.y = (rand() % (this->texture->height - this->arrBlobs[i].eGroup->texture->height));
		this->arrBlobs[i].pos.direction = ((rand() % 3600)/10.0F);

	}
	for (int i = 0; i < initFoodCant; i++)
	{
		this->arrFood[i].isNotEaten = 1;
		this->arrFood[i].pos.x = (rand() % (this->texture->width - this->arrFood[i].texture->width));
		this->arrFood[i].pos.y = (rand() % (this->texture->height - this->arrFood[i].texture->height));

	}
	this->arrFood;
	this->velMax = maxVel;
	this->modo = modo;
	this->initBlobCount = initBlobCant;
	this->foodCount = initFoodCant;
	this->velPercent = 1.0F;
	this->deathProbGOb = 0.0F;
	this->deathProbGb = 0.0F;
	this->deathProbBb = 0.0F;
	this->smellRadius = 100;
	this->randomJiggleLimit = 360.0F;
}

World::~World()
{

	delete this->texture;

}



int World::birth()
{


}