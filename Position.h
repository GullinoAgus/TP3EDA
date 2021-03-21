#pragma once

class Position
{
public:
	float x;
	float y;
	float direction;

	Position();
	float dist2(Position pos);
	void point2(Position pos);
};

