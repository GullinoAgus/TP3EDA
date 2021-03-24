#pragma once

#include "Blob.h"
#include "allegro.h"



#define WORLD_TEXTURE ".\\Resources\\background.jpg"

#define MAX_BLOB_CANT 500
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

	World(ModoType modo = MODO1, float maxVel = 10.0f, unsigned int initBlobCant = 10, unsigned int initFoodCant = 0);
	~World();

	void birth(float x, float y, float newDir);
	void blobOutScreen(unsigned int blobIndex);
	void Simulation(); 
	void preGame();
	void printBlobs();
	void printFood();
	void gamePrint();
};

