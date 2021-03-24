#pragma once

#include "Food.h"
#include "EtaryGroup.h"

#define GOB_TEXTURE ".\\Resources\\goodoldblob.png"
#define GB_TEXTURE ".\\Resources\\grownblob.png"
#define BB_TEXTURE ".\\Resources\\babyblob.png"

class Blob
{
public:
	Position pos;				//Posicion del blob
	int foodCount;				//Contador de comida ingerida
	const EtaryGroup* eGroup;	//Puntero al grupo etario
	float vel;					//Velocidad del blob
	int sonIndex;				//Indice del hijo(En caso de dar a luz)
	int dadIndex;				//Indice del padre(En caso de tener uno)
	bool isAlive;				//Estado de vida del Blob

	//Constructor
	Blob(EtaryGroupType tipo = BABY_BLOB);
	//Funcion de movimiento de los blobs. Recibe el porcentaje de velocidad de movimiento
	void move(float vmaxPercent);
	//Cambio de direccion de acuerdo a la comida mas cercana(oler la comida). Recibe el radio de olfateo, el arreglo de alimentos y la cantidad de alimentos del arreglo
	void smell(float smellRadius, Food* FoodArr, unsigned int foodCant);
	//Metodo de crecimiento para el blob, recibe la direccion del blob mas grande y uan nueva velocidadd
	void grow(float newDir, float newSpeed);
	//Asesinato del Blob
	void die();
	//Revivimos el blob recibiendo la nueva posicion y direccion
	void revive(float x, float y, float newDir); 

	//Funciones estaticas para carga y destruccion de las texturas
	static void loadTextures();
	static void freeTextures();
};




