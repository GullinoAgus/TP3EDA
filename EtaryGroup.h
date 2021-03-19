#pragma once

#include "Bitmap.h"

typedef enum {BABYBLOB, GROWNBLOB, GOODOLDBLOB} etaryGroup_t;

class EtaryGroup
{
public:
	Bitmap* texture;
	etaryGroup_t etaGroup;

	EtaryGroup(etaryGroup_t eGroupID, Bitmap* texture = NULL);

};

