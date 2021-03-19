#pragma once

#include "Food.h"
#include "EtaryGroup.h"

class Blob
{
public:

	Position pos;
	int foodCount;
	EtaryGroup* eGroup;
	float vel;
	Blob* next;

	Blob(EtaryGroup* etaryGroup = NULL);
	void move(float vmaxPercent);
	void smell(Food* foodList);
	void grow();
	void birth(Blob*& blobList);
	void destroy(Blob*& blobList);
	void merge(Blob*& blobList, Blob* colidingBlob);
};

