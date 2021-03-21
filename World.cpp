#include "World.h"

World::World(const char* textureDirectory, ModoType modo, float maxVel, unsigned int initBlobCant, unsigned int initFoodCant)
{
	this->texture = new Bitmap(textureDirectory);
	for (int i = 0; i < initBlobCant; i++)
	{
		switch (this->modo)//En base al modo le asinamos una velocidad al blob
		{
		case MODO1: this->arrBlobs[i].vel = this->velMax; break; 
		case MODO2: this->arrBlobs[i].vel = ( rand() % this->velMax); break; 
		}
		
		this->arrBlobs[i].isAlive = 1;
		this->arrBlobs[i].pos.x = (rand() % (this->texture->width - this->arrBlobs[i].eGroup->texture->width));
		this->arrBlobs[i].pos.y = (rand() % (this->texture->height - this->arrBlobs[i].eGroup->texture->height));
		this->arrBlobs[i].pos.direction = ((rand() % 3600)/10.0F);

	}
	for (int i = 0; i < initFoodCant; i++)
	{
		this->arrFood[i].isNotEaten = 1;
		this->arrFood[i].pos.x = (rand() % (this->texture->width - this->arrFood[i].texture->width));
		this->arrFood[i].pos.y = (rand() % (this->texture->height - this->arrFood[i].texture->height));

	}
	this->arrFood;
	this->velMax = maxVel;
	this->modo = modo;
	this->initBlobCount = initBlobCant;
	this->foodCount = initFoodCant;
	this->velPercent = 1.0F;
	this->deathProbGOb = 0.0F;
	this->deathProbGb = 0.0F;
	this->deathProbBb = 0.0F;
	this->smellRadius = 100;
	this->randomJiggleLimit = 360.0F;
}

World::~World()
{

	delete this->texture;

}



int World::birth()
{


}

int World::Simulation()
{
	//
	

	for (int i = 0; i < MAX_BLOB_CANT; i++)//Para cada blob vemos ...
	{

		//Vemos las coliciones de los blobs con las comidas
		for(int j=0; j< MAX_FOOD_CANT ; j++)
		{
			if ((this->arrBlobs[i].pos.x == this->arrFood->pos.x) && (this->arrBlobs[i].pos.y == this->arrFood->pos.y))// Si el blob colisiono con comida//Falta tomar en cuenta el ancho y alto de food y blob
			{
				this->arrBlobs[i].foodCount += 1;//Si se choco con la comida incrementamos su contador de comida
				this->arrFood[i].isNotEaten = false;// Destruimos lo que fue comido
				switch (this->arrBlobs->eGroup->etaGroup)//Si el contador de comida del blob es sufiente para crecer lo hacemos crecer
				{
				case BABY_BLOB:
					if (this->arrBlobs[i].foodCount == 5)
					{				
						this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y); // Si ya comio suficiente da a luz
					}

					; break;
				case GROWN_BLOB:
					if (this->arrBlobs[i].foodCount == 4)
					{				
						this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y);//Si ya comio suficiente da a luz
					}
					; break;
				case GOOD_OLD_BLOB:
					if (this->arrBlobs[i].foodCount == 3)
					{				
						this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y);//Si ya comio suficiente da a luz
					}
					; break;
				}
			}
		}

		//Vemos las coliciones entre blobs
		for (int j = 0, int flag=0; j < MAX_BLOB_CANT; j++ )//Aca debemos hacer que el blob ignore compararse consigo mismo
		{
			if( (this->arrBlobs[i].pos.x == this->arrBlobs[j].pos.x) && (this->arrBlobs[i].pos.y == this->arrBlobs[j].pos.y) && (this->arrBlobs[i] != this->arrBlobs[j]))//Falta tomar en cuenta el ancho y alto de los blobs
			{
				if (this->arrBlobs[i].eGroup->etaGroup == this->arrBlobs[j].eGroup->etaGroup)//Si son del mismo tamaño
				{
					this->arrBlobs[j].die();//Matamos al blob con el que choco
					flag = 1; //Marcamos el flag para saber que el blob va a crecer
				}
			}
			if ((j == (MAX_BLOB_CANT - 1)) && (flag > 0))//Si ya revisamos toda la lista y se chocaron dos blobs
			{
				this->arrBlobs[i].grow();//Hacemos que el blob crezca 
			}
		}
		

		//Vemos si hay comida serca del blob 
		this->arrBlobs[i].smell();//Cambiamos la orientacion de los blobs si hay comida serca

		//Actualizamos las posiciones de los blobs en base a su velocidad
		this->arrBlobs[i].move(this->velPercent);

	}


	//Revisamos que tengamos siempre toda la comida
	for (int i = 0; i < MAX_BLOB_CANT; i++)
	{
		if (this->arrFood[i].isNotEaten == false)//Si esta comida la revivimos en otro lado
		{
			this->arrFood[i].isNotEaten = true;
			this->arrFood[i].pos.x = (rand() % (this->texture->width - this->arrFood[i].texture->width));
			this->arrFood[i].pos.y = (rand() % (this->texture->height - this->arrFood[i].texture->height));
		}
	}

}