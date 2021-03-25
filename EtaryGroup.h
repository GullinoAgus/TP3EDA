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
	Bitmap texture;//Textura del blob en base a su grupo etario 
	unsigned int food2Birth;//Cant de comida necesaria para dar a luz
	EtaryGroupType etaGroupID;//Grupo etario

	EtaryGroup(EtaryGroupType eGroupID = BABY_BLOB, const char* textureDirectory = NULL);//Constructor

};

