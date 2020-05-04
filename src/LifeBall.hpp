#ifndef LIFEBALL_H
#define LIFEBALL_H

#include <string>

#include "RSDL/src/rsdl.hpp"
#include "Point.hpp"

const std::string LIFEBALL_IMG = "assets/lifeBall.png";

class LifeBall
{
private:
	int width, height;
	Point position;

public:
	LifeBall(Point pos,int ballWidth, int ballHeight);
	void draw(Window* window);
	bool isInside(Point pos);
	void setPosition(Point pos);
	Point getPosition();
};
#endif
