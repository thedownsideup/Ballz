#include "FireBall.hpp"

FireBall::FireBall(Point pos, int ballWidth, int ballHeight) : Ball(pos, ballWidth, ballHeight)
{
	ballType = FIRE_BALL;
}

void FireBall::draw(Window* window)
{
	window->draw_png(FIREBALL_IMG, position.x, position.y, width, height);
}