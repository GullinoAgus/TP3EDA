#pragma once

#include "Bitmap.h"

typedef enum {
	BABY_BLOB,
	GROWN_BLOB,
	GOOD_OLD_BLOB,
} EtaryGroupType;

class EtaryGroup
{
public:
	Bitmap* texture;
	unsigned int food2Birth;
	EtaryGroupType etaGroup;

	EtaryGroup(EtaryGroupType eGroupID, const char* textureDirectory);

};

