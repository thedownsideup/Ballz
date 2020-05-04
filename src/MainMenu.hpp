#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>

#include "RSDL/src/rsdl.hpp"
#include "Style.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "Controls.hpp"

const char PLAY = 0;
const char SCORE = 1;
const char EDIT = 2;
const char EXIT = 3;

class MainMenu
{
private:
	int selectedButtonIndex;
	std::vector<Button> buttons;
	Game* game;
	void press();

public:
	MainMenu(Game* owner);

	void update(Event* event);
	void draw(Window* window);
};

#endif