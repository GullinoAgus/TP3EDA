#include "Blob.h"

static const EtaryGroup GoodOldBlob(GOOD_OLD_BLOB, GOB_TEXTURE);
static const EtaryGroup GrownBlob(GROWN_BLOB, GB_TEXTURE);
static const EtaryGroup BabyBlob(BABY_BLOB, BB_TEXTURE);

Blob::Blob(EtaryGroupType tipo)
{
	switch (tipo)
	{
		case BABY_BLOB:
			this->eGroup = &BabyBlob;
			break;
		case GROWN_BLOB:
			this->eGroup = &GrownBlob;
			break;
		case GOOD_OLD_BLOB:
			this->eGroup = &GoodOldBlob;
			break;
		default:
			this->eGroup = NULL;
			break;
	}
	this->foodCount = 0;
	this->isAlive = 0;
	this->vel = 0;
	this->pos = { 0 , 0, 0 };
}


void Blob::move(float vmaxPercent)
{
    // TODO: Add your implementation code here.
}


void Blob::smell(Food* foodList)
{
    // TODO: Add your implementation code here.
}


void Blob::grow()
{
    // TODO: Add your implementation code here.
}



void Blob::die()
{
     //TODO: add your implementation code here.
}

