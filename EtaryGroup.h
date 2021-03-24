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
	Bitmap texture;
	unsigned int food2Birth;
	EtaryGroupType etaGroupID;

	EtaryGroup(EtaryGroupType eGroupID = BABY_BLOB, const char* textureDirectory = NULL);

};

