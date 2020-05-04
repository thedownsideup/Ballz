#include "Ball.hpp"

Ball::Ball(Point pos, int ballWidth, int ballHeight)
{
	position = pos;
	width = ballWidth;
	height = ballHeight;
	velocityX = 0;
	velocityY = 0;
	ballType = NORMAL_BALL;
}

void Ball::setVelocity(float vX, float vY)
{
	velocityX = vX;
	velocityY = vY;
}

float Ball::getVelocityX()
{
	return velocityX;
}

float Ball::getVelocityY()
{
	return velocityY;
}

void Ball::update(Event* event)
{
	position.x += velocityX;
	position.y += velocityY;
}

void Ball::draw(Window* window)
{
	window->draw_png(BALL_IMG, position.x, position.y, width, height);
}

Point Ball::getTop()
{
	return Point(position.x + width/2, position.y);
}

Point Ball::getBottom()
{
	return Point(position.x + width/2, position.y + height);
}

Point Ball::getLeft()
{
	return Point(position.x , position.y + height/2);
}

Point Ball::getRight()
{
	return Point(position.x + width, position.y + height/2);
}

void Ball::setPosition(Point pos)
{
	position.x = pos.x - width/2;
	position.y = pos.y - height/2;
}

BallType Ball::type()
{
	return ballType;
}