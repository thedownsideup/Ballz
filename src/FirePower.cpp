#include "FirePower.hpp"

FirePower::FirePower(Point pos, int ballWidth, int ballHeight)
{
	width = ballWidth;
	height = ballHeight;
	position = pos;
}

void FirePower::draw(Window* window)
{
	window->draw_png(FIREPOWER_IMG, position.x, position.y, width, height);
}
bool FirePower::isInside(Point pos)
{
	if(pos.x <= position.x + width && pos.x >= position.x && pos.y <= position.y + height && pos.y >= position.y)
	{
		return true;
	}
	else return false;
}
void FirePower::setPosition(Point pos)
{
	position.y = pos.y;
}

Point FirePower::getPosition()
{
	return position;
}