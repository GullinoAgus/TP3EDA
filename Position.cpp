#include "Position.h"
#define _USE_MATH_DEFINES
#include <cmath>

#define PI 3.14159265F
#define RAD2DEG(x) ((x)*(180.0F/ M_PI ))


Position::Position()
{
	this->x = 0;
	this->y = 0;
	this->direction = 0;
}


float Position::dist2(Position pos) 
{

	return sqrt(pow(this->x - pos.x, 2) + pow(this->y - pos.y, 2));

}

void Position::point2(Position pos)
{

	float dx = pos.x - this->x;
	float dy = pos.y - this->y;
	this->direction = RAD2DEG(atan2f(dy, dx));

}