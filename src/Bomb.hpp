#ifndef BOMB_H
#define BOMB_H

#include "RSDL/src/rsdl.hpp"
#include "Point.hpp"

class Bomb
{
private:
	int width, height;
	Point position;

public:
	Bomb(Point pos,int bombWidth, int bombHeight);
	void draw(Window* window);
	bool isInside(Point pos);
	void setPosition(Point pos);
	Point getPosition();
};
#endif