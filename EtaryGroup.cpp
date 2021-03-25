#include "EtaryGroup.h"
// constructoe de la clase EtaryGroup
EtaryGroup::EtaryGroup(EtaryGroupType eGroupID, const char *textureDirectory)
{
	this->texture = Bitmap(textureDirectory);// se le asigna la imagen correspondiente
	this->etaGroupID = eGroupID;//se le asigna el tipo de blob correspondiente
	//modifica la cantidad de comida necesaria para crecer de un blob
	switch (eGroupID)
	{
	case BABY_BLOB:
		food2Birth = 5;
		break;
	case GROWN_BLOB:
		food2Birth = 4;
		break;
	case GOOD_OLD_BLOB:
		food2Birth = 3;
		break;
	default:
		food2Birth = 0;
		break;
	}
}
