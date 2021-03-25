#pragma once

class Position
{
public:
	float x;
	float y;
	float direction;//Angulo respecto a la horizontal (0 a 360)

	Position();//Constructor 
	float dist2(Position pos);//Mide distancia a un punto
	void point2(Position pos);//Cambia la direccion a un punto determiando 
};

