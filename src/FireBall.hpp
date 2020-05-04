#ifndef FIREBALL_H
#define FIREBALL_H

#include <string>

#include "RSDL/src/rsdl.hpp"
#include "Ball.hpp"

const std::string FIREBALL_IMG = "assets/fireBall.png";

class FireBall : public Ball
{
public:
	
	FireBall(Point pos, int ballWidth, int ballHeight);
	void draw(Window* window);
};

#endif