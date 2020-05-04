#include "Bomb.hpp"

Bomb::Bomb(Point pos,int bombWidth, int bombHeight)
{
	position = pos;
	width = bombWidth;
	height = bombHeight;
}

void Bomb::draw(Window* window)
{
	window->fill_rect(position.x,position.y, width, height, BLACK);
}

bool Bomb::isInside(Point pos)
{
if(pos.x <= position.x + width && pos.x >= position.x && pos.y <= position.y + height && pos.y >= position.y)
{
	return true;
}
else return false;

}

void Bomb::setPosition(Point pos)
{
	position.y = pos.y;

}

Point Bomb::getPosition()
{
	return position;
}
