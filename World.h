#pragma once

#include "Blob.h"

typedef enum {MODO1, MODO2} modo_t;

class World
{
public:
	Bitmap* texture;
	Blob* listaBlobs;
	Food* listaFood;
	float velMax;
	modo_t modo;
	unsigned int initBlobCount;
	unsigned int foodCount;
	float velPercent;
	float deathProbGOb;
	float deathProbGb;
	float deathProbBb;
	float smellRadius;
	float randomJiggleLimit;

	World();

};

