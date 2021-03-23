#include "World.h"
#include <cmath>

World::World(const char* textureDirectory, ModoType modo, float maxVel, unsigned int initBlobCant, unsigned int initFoodCant)
{
	this->texture = new Bitmap(textureDirectory);
	for (int i = 0; i < initBlobCant; i++)
	{
		switch (this->modo)//En base al modo le asinamos una velocidad al blob
		{
		case MODO1: this->arrBlobs[i].vel = this->velMax; break; 
		case MODO2: this->arrBlobs[i].vel = ( rand() % (int)this->velMax); break; 
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


void World::birth(float x, float y, float newDir)
{
	int i;
	for (i = 0; i < MAX_BLOB_CANT && arrBlobs[i].isAlive; i++) {}	//Busco un blob muerto
	arrBlobs[i].revive(x, y, newDir);								//Lo revivo en su nueva ubicacion
}


void World::blobOutScreen(unsigned int blobIndex)
{
	if (this->arrBlobs[blobIndex].pos.x >= this->texture->width)		//Si se pasa por la derecha
	{
		this->arrBlobs[blobIndex].pos.x = -(int)this->arrBlobs[blobIndex].eGroup->texture->width;	//lo llevo al borde izquierdo
	}
	else if (this->arrBlobs[blobIndex].pos.y >= this->texture->height)	//Si se pasa por abajo
	{
		this->arrBlobs[blobIndex].pos.y = -(int)this->arrBlobs[blobIndex].eGroup->texture->height;	//lo llevo al borde superior
	}
	else if (this->arrBlobs[blobIndex].pos.y <= -(int)this->arrBlobs[blobIndex].eGroup->texture->height)	//Si se pasa por arriba
	{
		this->arrBlobs[blobIndex].pos.y = this->texture->height;								//lo llevo al borde inferior
	}
	else if (this->arrBlobs[blobIndex].pos.x <= -(int)this->arrBlobs[blobIndex].eGroup->texture->width)	//Si se pasa por la izquierda
	{
		this->arrBlobs[blobIndex].pos.x = this->texture->width;									//lo llevo al borde derecho
	}
}


void World::Simulation()
{
	//
	
	//TODO: Hay que agregar lo de ver que el blob este vivo antes de chequear todo, y ademas falta calcular la muerte
	for (int i = 0; i < MAX_BLOB_CANT; i++)//Para cada blob vemos ...
	{

		//Vemos las coliciones de los blobs con las comidas
		for(int j=0; j< MAX_FOOD_CANT ; j++)
		{
			//TODO : Completar el condicional de colision. Recordar que esta el bitmap con el alto y ancho en eGroup.texture.height y .width
			if ((this->arrBlobs[i].pos.x == this->arrFood->pos.x) && (this->arrBlobs[i].pos.y == this->arrFood->pos.y))// Si el blob colisiono con comida//Falta tomar en cuenta el ancho y alto de food y blob
			{
				this->arrBlobs[i].foodCount += 1;//Si se choco con la comida incrementamos su contador de comida
				this->arrFood[j].isNotEaten = false;// Destruimos lo que fue comido

				//TODO : Cambiar este switch. abajo de esto esta el if que deberia quedar

				//switch (this->arrBlobs->eGroup->etaGroupID)//Si el contador de comida del blob es sufiente para crecer lo hacemos crecer
				//{
				//case BABY_BLOB:
				//	if (this->arrBlobs[i].foodCount == 5)
				//	{				
				//		this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y); // Si ya comio suficiente da a luz
				//	}

				//	; break;
				//case GROWN_BLOB:
				//	if (this->arrBlobs[i].foodCount == 4)
				//	{				
				//		this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y);//Si ya comio suficiente da a luz
				//	}
				//	; break;
				//case GOOD_OLD_BLOB:
				//	if (this->arrBlobs[i].foodCount == 3)
				//	{				
				//		this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y);//Si ya comio suficiente da a luz
				//	}
				//	; break;
				//}

				if (arrBlobs[i].foodCount == arrBlobs[i].eGroup->food2Birth)
				{
					this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y, abs(arrBlobs[i].pos.direction - 180)); // Si ya comio suficiente da a luz
				}
			}
		}
		//TODO: Chequear en la consigna como tiene que quedar la direccion despues de la colision, es un promedio medio loco y hay que usar randomJiggleLimit
		//Vemos las coliciones entre blobs
		for (int j = 0, flag=0; j < MAX_BLOB_CANT; j++ )//Aca debemos hacer que el blob ignore compararse consigo mismo
		{
			if( (this->arrBlobs[i].pos.x == this->arrBlobs[j].pos.x) && (this->arrBlobs[i].pos.y == this->arrBlobs[j].pos.y) && (this->arrBlobs+i != this->arrBlobs+j))//Falta tomar en cuenta el ancho y alto de los blobs
			{
				if (this->arrBlobs[i].eGroup->etaGroupID == this->arrBlobs[j].eGroup->etaGroupID)//Si son del mismo tama�o
				{
					this->arrBlobs[j].die();//Matamos al blob con el que choco
					flag = 1; //Marcamos el flag para saber que el blob va a crecer
				}
			}
			if ((j == (MAX_BLOB_CANT - 1)) && (flag > 0))//Si ya revisamos toda la lista y se chocaron dos blobs
			{
				//HACK: Le agregue a grow que reciba la direccion nueva(en la consigna dice)
				this->arrBlobs[i].grow();//Hacemos que el blob crezca 
			}
		}
		

		//Vemos si hay comida serca del blob 
		this->arrBlobs[i].smell(this->smellRadius, this->arrFood, MAX_FOOD_CANT);//Cambiamos la orientacion de los blobs si hay comida serca

		//Actualizamos las posiciones de los blobs en base a su velocidad
		this->arrBlobs[i].move(this->velPercent);
		//TODO: Chequear esto con salvador, habria que ver si se agrega aca o no. Es para que cuando se este por escapar de la pantalla aparezca del otro lado
		this->blobOutScreen(i);
	}


	//Revisamos que tengamos siempre toda la comida
	for (int i = 0; i < MAX_FOOD_CANT; i++)
	{
		if (this->arrFood[i].isNotEaten == false)//Si esta comida la revivimos en otro lado
		{
			this->arrFood[i].isNotEaten = true;
			this->arrFood[i].pos.x = (rand() % (this->texture->width - this->arrFood[i].texture->width));
			this->arrFood[i].pos.y = (rand() % (this->texture->height - this->arrFood[i].texture->height));
		}
	}

}