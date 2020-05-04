#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <string>
#include <vector>
#include <sstream>

#include "RSDL/src/rsdl.hpp"
#include "Style.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "Controls.hpp"

const std::string GAMEOVER_BACKGROUND = "assets/GameOver2.png";
const std::string GAMEOVER = "Game Over!";
enum GameOverState
{
	MENU,
	NEWGAME
};

class GameOver
{
private:
	Game* game;
	int selectedButtonIndex;
	std::vector<Button> buttons;
	void press();

public:
	GameOver(Game* owner);
	void update(Event* event);
	void draw(Window* window);
	std::string convertIntegerToString(int stringWannaBe);
	
};

#endif