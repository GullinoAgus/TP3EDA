#include "EtaryGroup.h"

EtaryGroup::EtaryGroup(EtaryGroupType eGroupID, const char *textureDirectory)
{
	this->texture = new Bitmap(textureDirectory);
	this->etaGroupID = eGroupID;
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

EtaryGroup::~EtaryGroup() 
{
	delete this->texture;
}