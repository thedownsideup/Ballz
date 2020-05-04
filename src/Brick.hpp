#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <sstream>

#include "RSDL/src/rsdl.hpp"
#include "Point.hpp"
#include "Style.hpp"

const int RED_COLOR = 255;
const int GREEN_COLOR = 204;
const int BLUE_COLOR = 204;
const int BASE_COLOR = 204;
const int COLOR_COEFFICIENT = 1;

class Brick
{
private:
	int width, height;
	int laResistance;
	Point position;
	RGB rgb;
	bool died;

public:
	Brick(Point pos,int brickWidth, int brickHeight, int resistance);
	void draw(Window* window);
	void takeDamage();
	void die();
	bool hasDied();
	std::string convertIntegerToString(int stringWannaBe);
	bool isInside(Point pos);
	void setPosition(Point pos);
	Point getPosition();
};
#endif