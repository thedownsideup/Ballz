#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>

#include "RSDL/src/rsdl.hpp"
#include "Style.hpp"

const std::string WINDOW_NAME = "Ballz";
const int DELAY_TIME = 8;
const std::string LEADERBOARD_FILE = "assets/leaderboard.txt";
const std::string LASTPLAYERFILE = "assets/lastPlayerFile.txt";

enum GameState
{
	MAIN_MENU,
	PLAYING,
	EDIT_USERNAME,
	SCOREBOARD,
	GAME_OVER
};

class MainMenu;
class Scoreboard;
class NameEditor;
class Playground;
class GameOver;

class Game
{
private:
	Window* window;
	bool running;
	GameState state;

	MainMenu* mainMenu;
	Scoreboard* scoreboard;
	NameEditor* nameEditor;
	Playground* playground;
	GameOver* gameover;
	std::vector<std::pair<std::string, int> > leaderboard;
	int lastScore;
	std::string username;

	void loadGame();
	void update();
	void draw();
	bool checkLastPlayer();
	void loadLeaderboard();
	void saveLeaderboard();
public:
	Game();

	void setUsername(std::string name);
	std::string getUsername();
	void run();
	void quit();
	void changeState(GameState gameState);
	void addRecord(std::string name, int score);
	int getHighscore();
	int getLastScore();
	std::vector<std::pair<std::string, int> > getScores();
};

#endif