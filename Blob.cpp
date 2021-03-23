#include "Blob.h"
#define _USE_MATH_DEFINES
#include <cmath>

#define DEG2RAD(x) ((x)*( M_PI /180.0F))

static const EtaryGroup goodOldBlob(GOOD_OLD_BLOB, GOB_TEXTURE);
static const EtaryGroup grownBlob(GROWN_BLOB, GB_TEXTURE);
static const EtaryGroup babyBlob(BABY_BLOB, BB_TEXTURE);

Blob::Blob(EtaryGroupType tipo)
{
	switch (tipo)
	{
		case BABY_BLOB:
			this->eGroup = &babyBlob;
			break;
		case GROWN_BLOB:
			this->eGroup = &grownBlob;
			break;
		case GOOD_OLD_BLOB:
			this->eGroup = &goodOldBlob;
			break;
		default:
			this->eGroup = NULL;
			break;
	}
	this->foodCount = 0;
	this->isAlive = 0;
	this->vel = 0;
}


void Blob::move(float vmaxPercent)
{
	this->pos.x += this->vel * vmaxPercent * cosf(DEG2RAD(this->pos.direction));
	this->pos.y += this->vel * vmaxPercent * sinf(DEG2RAD(this->pos.direction));
}


void Blob::smell(float smellRadius, Food *foodArr, unsigned int foodCant)
{
	Position blobCenter;
	Position foodCenter;
	int nearestFood = -1;											//Guarda el indice a la comida masa cercana
	float distance;													//VAriable temporal para guardar la distancia
	float closestDist = smellRadius + 1;							//Variable para almacenar la distancia mas corta encontrada
	blobCenter.x = this->pos.x + this->eGroup->texture->width / 2;	//Inicializo el ponto central del blob
	blobCenter.y = this->pos.y + this->eGroup->texture->height / 2;

	

	for (unsigned int i = 0; i < foodCant; i++)											//Recorro la lista de alimento viendo cuales estan dentro del radio de olfato( x^2+y^2=smellRadiun^2 )
	{
		if (foodArr[i].isNotEaten)
		{
			foodCenter.x = foodArr[i].pos.x + foodArr[i].texture->width / 2;			//Calculo el punto central de la comida
			foodCenter.y = foodArr[i].pos.y + foodArr[i].texture->height / 2;
			distance = blobCenter.dist2(foodCenter);									//Calculo la distancia desde el centro del blob a lcentro de la comida
			if (distance <= smellRadius && distance < closestDist)						//Si la distancia es menor o igual a smellRadius y menor que la mas chica hasta ahora
			{
				closestDist = distance;													//La guardamos como la mas corta
				nearestFood = i;														//Guardamos el indice
			}
		}
	}

	blobCenter.point2(foodCenter);														//Apuntamos el centro a la comida y lo pasamos al blob
	this->pos.direction = blobCenter.direction;
}


void Blob::grow(float newDir)
{
	switch (this->eGroup->etaGroupID)			//De acuerdo a su grupo etario lo avanzamos al siguiente
	{
	case BABY_BLOB:
		this->eGroup = &grownBlob;
		break;
	case GROWN_BLOB:
		this->eGroup = &goodOldBlob;
		break;
	default:
		break;
	}
	this->pos.direction = newDir;				//Actualizo la direccion y el contador de comida
	this->foodCount = 0;
}



void Blob::die()
{
	this->isAlive = false;
}


void Blob::revive(float x, float y, float newDir)
{
	this->isAlive = 1;
	this->eGroup = &babyBlob;
	this->foodCount = 0;
	this->pos.x = x;
	this->pos.y = y;
	this->pos.direction = newDir;
}
