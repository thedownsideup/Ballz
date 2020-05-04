#include "Brick.hpp"

Brick::Brick(Point pos, int brickWidth, int brickHeight, int resistance) : rgb(RED_COLOR, GREEN_COLOR, BLUE_COLOR)
{
	width = brickWidth;
	height = brickHeight;
	laResistance = resistance;
	position = pos;
	died = false;
}

void Brick::draw(Window* window)
{
	int color = BASE_COLOR - COLOR_COEFFICIENT*laResistance;
	if(color < 0)
	{
		color = 0;
	}
	
	window->fill_rect(position.x,position.y, width, height, RGB(RED_COLOR, color, color));
	window->show_text(convertIntegerToString(laResistance),  position.x + width / 2 - (float)convertIntegerToString(laResistance).size()/2 * (float)FONT_SIZE * 3 / 5, position.y + height/2 - (float)(FONT_SIZE - 10) * 3 / 5, WHITE, FONT_NAME, FONT_SIZE - 10);
}

void Brick::takeDamage()
{
	laResistance--;
	if(laResistance == 0)
	{
		die();
	}
}

void Brick::die()
{
	died = true;
}

bool Brick::hasDied()
{
	return died;
}

std::string Brick::convertIntegerToString(int stringWannaBe)
{
	std::stringstream ss;
	ss << stringWannaBe;
	return ss.str();
}

bool Brick::isInside(Point pos)
{
	if(pos.x <= position.x + width && pos.x >= position.x && pos.y <= position.y + height && pos.y >= position.y)
	{
		return true;
	}
	else return false;
}

void Brick::setPosition(Point pos)
{
	position.y = pos.y;
}

Point Brick::getPosition()
{
	return position;
}