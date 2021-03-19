#pragma once

#include "Bitmap.h"

typedef enum {BABYBLOB, GROWNBLOB, GOODOLDBLOB} etaryGroup_t;

class EtaryGroup
{
	Bitmap *texture;
	etaryGroup_t etaGroup;

	EtaryGroup(Bitmap* texture = NULL);

};

