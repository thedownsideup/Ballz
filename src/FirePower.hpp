#ifndef FIREPOWER_H
#define FIREPOWER_H

#include <string>

#include "RSDL/src/rsdl.hpp"
#include "Point.hpp"

const std::string FIREPOWER_IMG = "assets/firePower.png";

class FirePower
{
private:
	int width, height;
	Point position;

public:
	FirePower(Point pos,int ballWidth, int ballHeight);
	void draw(Window* window);
	bool isInside(Point pos);
	void setPosition(Point pos);
	Point getPosition();
};
#endif
