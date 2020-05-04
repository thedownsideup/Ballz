#ifndef BALL_H
#define BALL_H

#include <string>

#include "RSDL/src/rsdl.hpp"
#include "Point.hpp"

const std::string BALL_IMG = "assets/ball.png";

enum BallType { NORMAL_BALL, FIRE_BALL };

class Ball
{
protected:
	float velocityX, velocityY;
	Point position;
	int width, height;
	BallType ballType;
public:
	
	Ball(Point pos, int ballWidth, int ballHeight);
	void setVelocity(float vX, float vY);
	float getVelocityX();
	float getVelocityY();
	void update(Event* event);
	virtual void draw(Window* window);
	Point getTop();
	Point getBottom();
	Point getLeft();
	Point getRight();
	void setPosition(Point pos);

	BallType type();
};

#endif