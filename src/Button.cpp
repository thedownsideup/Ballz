#include "Button.hpp"

void Button::draw(Window* win)
{
	win->fill_rect(position.x, position.y, width, height, color);
	win->show_text(text, position.x + width / 2 - (float)text.size()/2 * (float)FONT_SIZE * 3 / 5, position.y + height/2 - (float)FONT_SIZE * 3 / 5, ACCENT_COLOR, FONT_NAME, FONT_SIZE);

	if(isSelected == true)
	{
		win->draw_rect(position.x + PADDING, position.y + PADDING, width - 2*PADDING, height - 2*PADDING, ACCENT_COLOR);
	}
}

void Button::select()
{
	isSelected = true;
}

void Button::deselect()
{
	isSelected = false;
}
