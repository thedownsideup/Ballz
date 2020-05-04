#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "RSDL/src/rsdl.hpp"
#include "Point.hpp"
#include "Style.hpp"

class Button
{

public:

	Button(Point pos, int width, int height, std::string title, RGB bgColor) : color(bgColor), text(title)
	{
		position = pos;
		this->height = height;
		this->width = width;
		isSelected = false;
	}
	void draw(Window* win);
	void select();
	void deselect();

private:
	std::string text;
	RGB color;
	bool isSelected;
	int height, width;
	Point position;
};

#endif
