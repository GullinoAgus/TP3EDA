#pragma once

#include "Food.h"
#include "EtaryGroup.h"

#define GOB_TEXTURE ".\\Resources\\goodoldblob.png"
#define GB_TEXTURE ".\\Resources\\grownblob.png"
#define BB_TEXTURE ".\\Resources\\babyblob.png"

class Blob
{
public:

	Position pos;
	int foodCount;
	const EtaryGroup* eGroup;
	float vel;
	bool isAlive;

	Blob(EtaryGroupType tipo = BABY_BLOB);
	void move(float vmaxPercent);
	void smell(float smellRadius, Food* FoodArr, unsigned int foodCant);
	void grow();
	void die();
	void revive();
};


