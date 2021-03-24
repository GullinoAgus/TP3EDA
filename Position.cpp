#include "Position.h"
#define _USE_MATH_DEFINES
#include <cmath>
		
#define RAD2DEG(x) ((x)*(180.0F/ M_PI ))// transformacion de un angulo en radianes a grados


Position::Position()//constructor de la clase position
{
	this->x = 0;
	this->y = 0;
	this->direction = 0;
}


float Position::dist2(Position pos) //calcula la distancia euclidiana entre a un punto de tipo position
{

	return sqrtf(pow(this->x - pos.x, 2) + pow(this->y - pos.y, 2));

}

void Position::point2(Position pos)//modifica la direccion de una posicion para que apunte hacia pos
{

	float dx = pos.x - this->x;
	float dy = pos.y - this->y;
	this->direction = (float)RAD2DEG(atan2f(dy, dx));

}