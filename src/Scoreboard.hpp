#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "RSDL/src/rsdl.hpp"
#include "Style.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"

const int DELIM = 255;
const int BOARD_HEIGHT = 400;
const int BOARD_WIDTH = 400;
const int BOARD_X = 100;
const int BOARD_Y = 100;
const std::string RECORDS = "Records:";

const std::string SCOREFILE = "assets/Scoreboard.txt";


class Scoreboard
{
private:
	std::ifstream scoreFile;
	Game* game;
	std::vector<std::string> namesNscores;
	std::vector<Button> menuButton;
	int selectedButtonIndex;

public:
	Scoreboard(Game* owner);
	void update(Event* event);
	void draw(Window* window);
	void getScores();
	std::string convertIntegerToString(int stringWannaBe);
	
};

#endif