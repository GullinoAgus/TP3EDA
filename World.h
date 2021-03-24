#pragma once

#include "Blob.h"
#include "allegro.h"



#define WORLD_TEXTURE ".\\Resources\\background.jpg"

#define MAX_BLOB_CANT 500
#define MAX_FOOD_CANT 100
#define MAX_VEL 100
#define MAX_SMELL_RADIUS 1000
#define TICKS_2_TOSS_DEATH 60

typedef enum  {MODO1, MODO2} ModoType;//los dos modos posibles de juegos

class World
{
public:
	Bitmap texture;				// la imagen de fondo de pantalla
	Blob arrBlobs[MAX_BLOB_CANT];//array qu econtienen todos los blobs
	Food arrFood[MAX_FOOD_CANT];//array que coniene toda la comida
	float velMax;				//veloidad maxima que puede llegar a tener un blob
	ModoType modo;				//modo de simulacion (1 o 2)
	unsigned int initBlobCount;	// cantidad de blobs con la que empieza la simulacion
	unsigned int foodCount;		//cantidad de comida en la simulacion
	float velPercent;			// velocidad real que tiene un blob. es un porcentaje de la maxima
	//probabilidad de muerte segun tipo de blob
	float deathProbGOb;
	float deathProbGb;
	float deathProbBb;
	float smellRadius;			// radio en el que puede detectar comida un blob
	float randomJiggleLimit;	//maximo rango de cambio de direccion al funcionar

	//constructor del world con sus defaults
	World(ModoType modo = MODO1, float maxVel = 10.0f, unsigned int initBlobCant = 10, unsigned int initFoodCant = 0);
	
	int birth(float x, float y, float newDir);	//nacimiento de un nuevo blob
	void blobOutScreen(unsigned int blobIndex);	//regresar al blob que sale de la pantalla al otro lado de la pantalla
	void Simulation();		//calculos de la simulacion en si
	bool preGame();			// pide datos al usuario necesarios para arrancar la simulacion
	void printBlobs();		//imprime los blobs en pantalla
	void printFood();		//imprime la comida
	void gamePrint();		//imprime la simulacion con todos sus controles
	void initBlobs();		//inicializa los blobs
	void initFood();		//inicializa la comida
};

