#pragma once

#include "Blob.h"

#define WORLD_TEXTURE ".\\Resources\\background.jpg"

#define MAX_BLOB_CANT 1000
#define MAX_FOOD_CANT 100

typedef enum  {MODO1, MODO2} ModoType;

class World
{
public:
	Bitmap* texture;
	Blob arrBlobs[MAX_BLOB_CANT];
	Food arrFood[MAX_FOOD_CANT];
	float velMax;
	ModoType modo;
	unsigned int initBlobCount;
	unsigned int foodCount;
	float velPercent;
	float deathProbGOb;
	float deathProbGb;
	float deathProbBb;
	float smellRadius;
	float randomJiggleLimit;

	World(const char* textureDirectory, ModoType modo, float maxVel, unsigned int initBlobCant, unsigned int initFoodCant = 0);
	~World();

	void birth(float x, float y, float newDir);
	void blobOutScreen(unsigned int blobIndex);
	void Simulation(); 
};

