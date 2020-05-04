#include "LifeBall.hpp"

LifeBall::LifeBall(Point pos, int ballWidth, int ballHeight)
{
	width = ballWidth;
	height = ballHeight;
	position = pos;
}

void LifeBall::draw(Window* window)
{
	window->draw_png(LIFEBALL_IMG, position.x, position.y, width, height);
}
bool LifeBall::isInside(Point pos)
{
	if(pos.x <= position.x + width && pos.x >= position.x && pos.y <= position.y + height && pos.y >= position.y)
	{
		return true;
	}
	else return false;
}
void LifeBall::setPosition(Point pos)
{
	position.y = pos.y;
}

Point LifeBall::getPosition()
{
	return position;
}