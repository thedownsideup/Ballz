#ifndef NAMEEDITOR_H
#define NAMEEDITOR_H

#include <fstream>
#include <string>
#include <vector>

#include "RSDL/src/rsdl.hpp"
#include "Style.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "Controls.hpp"

const int MAX_STRING_LENGTH = 10;

enum editState
{
	SAVE,
	CANCEL
};

class NameEditor
{
private:
	int selectedButtonIndex;
	std::vector<Button> buttons;
	Game* game;
	void press();
	std::string inputString;

public:
	NameEditor(Game* owner);
	std::string getText();
	void update(Event* event);
	void draw(Window* win);
	void processLastEvent(Event *event);
};

#endif