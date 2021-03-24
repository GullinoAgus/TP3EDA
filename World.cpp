#include "World.h"
#include <cmath>

using namespace ImGui;


World::World( ModoType modo, float maxVel, unsigned int initBlobCant, unsigned int initFoodCant)
{
	this->texture = new Bitmap(WORLD_TEXTURE);
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
	
	for (int i = 0; i < MAX_BLOB_CANT; i++)//Para cada blob vemos ...
	{

		//Vemos si el blob muere
		switch (this->arrBlobs[i].eGroup->etaGroupID)//Dependiendo el grupo etario tienen distintas probabilidad de muerte
		{
		case BABY_BLOB:
			if ( ((rand() % 101)/100) < this->deathProbBb)//Si el numero al azar entre 0 y 1 es menor que la probabilidad de muerte
				this->arrBlobs[i].die();//Lo matamos
			break;
		case GROWN_BLOB:
			if (((rand() % 101) / 100) < this->deathProbGb)
				this->arrBlobs[i].die();
			break;
		case GOOD_OLD_BLOB:
			if (((rand() % 101) / 100) < this->deathProbGOb)
				this->arrBlobs[i].die();
			break;
		default:
			break;
		}

		if (this->arrBlobs[i].isAlive == false)//Si esta muerto el blob
		{
			continue; //Pasamos al siguiente blob 
		}
		
		//Vemos las coliciones de los blobs con las comidas
		for(int j=0; j< MAX_FOOD_CANT ; j++)
		{
			if ( ( ( (this->arrBlobs[i].pos.x + this->arrBlobs[i].eGroup->texture->width) > (this->arrFood[j].pos.x)) && ((this->arrBlobs[i].pos.x) < (this->arrFood[j].pos.x + this->arrFood[j].texture->width))) && (((this->arrBlobs[i].pos.y + this->arrBlobs[i].eGroup->texture->height) > (this->arrFood[j].pos.y)) && ((this->arrBlobs[i].pos.y) < (this->arrFood[j].pos.y + this->arrFood[j].texture->height))))// Si el blob colisiono con comida
			{
				this->arrBlobs[i].foodCount += 1;//Si se choco con la comida incrementamos su contador de comida
				this->arrFood[j].isNotEaten = false;// Destruimos lo que fue comido

				if (arrBlobs[i].foodCount == arrBlobs[i].eGroup->food2Birth)
				{
					this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y, abs(arrBlobs[i].pos.direction - 180)); // Si ya comio suficiente da a luz
				}
			}
		}
		
		//Vemos las coliciones entre blobs
		float DirectionSum = 0.F, NewDirection = 0.0F;
		for (int j = 0, flag=0; j < MAX_BLOB_CANT; j++ )//Aca debemos hacer que el blob ignore compararse consigo mismo
		{
			if( (i != j) && ( ( (this->arrBlobs[i].pos.x + this->arrBlobs[i].eGroup->texture->width) > (this->arrBlobs[j].pos.x) ) && ( (this->arrBlobs[i].pos.x) < (this->arrBlobs[j].pos.x + this->arrBlobs[j].eGroup->texture->width) ) ) && ( ( (this->arrBlobs[i].pos.y + this->arrBlobs[i].eGroup->texture->height) > (this->arrBlobs[j].pos.y)) && ((this->arrBlobs[i].pos.y) < (this->arrBlobs[j].pos.y + this->arrBlobs[j].eGroup->texture->height) ) ) )
			{
				if (this->arrBlobs[i].eGroup->etaGroupID == this->arrBlobs[j].eGroup->etaGroupID)//Si son del mismo tamaño
				{
					DirectionSum += this->arrBlobs[j].pos.direction;//Agrego al promedio la direccion del blob
					this->arrBlobs[j].die();//Matamos al blob con el que choco
					flag += 1; //Marcamos el flag para saber que el blob va a crecer
				}
			}
			if ((j == (MAX_BLOB_CANT - 1)) && (flag > 0))//Si ya revisamos toda la lista y se chocaron dos blobs
			{
				
				NewDirection = (DirectionSum/flag)+ (rand() % (int)this->randomJiggleLimit) ;
				this->arrBlobs[i].grow(NewDirection);//Hacemos que el blob crezca 
			}
		}
		

		//Vemos si hay comida serca del blob 
		this->arrBlobs[i].smell(this->smellRadius, this->arrFood, MAX_FOOD_CANT);//Cambiamos la orientacion de los blobs si hay comida serca

		//Actualizamos las posiciones de los blobs en base a su velocidad
		this->arrBlobs[i].move(this->velPercent);
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

void World::preGame()
{
	//antes de empezar la simulacion
	ImGui_ImplAllegro5_NewFrame();
	NewFrame();
	Begin("Blob World", NULL, ImGuiWindowFlags_MenuBar);//REVISAR
	//default bool mode = 1. mode1 = true, mode2 = false
	if (Button("Modo"))
	{
		modo ? false : true;
		if (modo)
			Text("Mode 1 selected");
		else
			Text("Mode 2 selected");
		Begin("Blob ammount.");
		if (Button("Increase Blob ammount"))
			initBlobCount++;
		else if (Button("Decrease Blob ammount"))
			initBlobCount++;;
		Text("Blobs = %d", initBlobCount);
		End();
		// despues de emp
	}
}

void World::printBlobs()
{
	for (int i = 0; i < MAX_BLOB_CANT; i++)
	{
		if (arrBlobs[i].isAlive)
		{
			if (this->arrBlobs[i].eGroup->etaGroupID == BABY_BLOB)
				al_draw_bitmap( arrBlobs[i].eGroup->texture->bitmap, arrBlobs[i].pos.x, arrBlobs[i].pos.y, 0);
			else if (this->arrBlobs[i].eGroup->etaGroupID == GROWN_BLOB)
				al_draw_bitmap(arrBlobs[i].eGroup->texture->bitmap, arrBlobs[i].pos.x, arrBlobs[i].pos.y, 0);
			else if (this->arrBlobs[i].eGroup->etaGroupID == GOOD_OLD_BLOB)
				al_draw_bitmap(arrBlobs[i].eGroup->texture->bitmap, arrBlobs[i].pos.x, arrBlobs[i].pos.y, 0);
		}
	}
}

void World::printFood()
{
	for (int i = 0; i < MAX_FOOD_CANT; i++)
	{
		if (arrFood[i].isNotEaten)
		{
			al_draw_bitmap(arrFood[i].texture->bitmap, arrFood[i].pos.x, arrFood[i].pos.y, 0);
		}
	}
}

void World::gamePrint()
{

	SliderFloat("Velocidad Maxima", &velMax, 0.0f, 1.0f);//corregir resto
	Text("Speed percentage");
	SliderFloat("float", &velPercent, 0.0f, 1.0f);
	Text("Smell radius");
	SliderFloat("float", &smellRadius, 0.0f, 1.0f);
	Text("Baby blob death probability");
	SliderFloat("float", &deathProbBb, 0.0f, 1.0f);
	Text("Grown blob death probability");
	SliderFloat("float", &deathProbGb, 0.0f, 1.0f);
	Text("Old blob death probability");
	SliderFloat("float", &deathProbGOb, 0.0f, 1.0f);


	Begin("Food count.");
	if (Button("Increase food count"))
		foodCount++;
	else if (Button("Decrease food count"))
		foodCount--;
	Text("Food count = %d", foodCount);
	End();
	//que es randomJiggleLimit?
	printBlobs();
	printFood();
}

