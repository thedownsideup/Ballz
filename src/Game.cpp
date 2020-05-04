#include "Game.hpp"
#include "MainMenu.hpp"
#include "Scoreboard.hpp"
#include "NameEditor.hpp"
#include "Playground.hpp"
#include "GameOver.hpp"

Game::Game()
{
	running = false;
}

void Game::loadGame()
{
	running = true;
	state = MAIN_MENU;
	if(checkLastPlayer() == false)
	{
		username = "Player";
	}
	window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	mainMenu = new MainMenu(this);
	scoreboard = new Scoreboard(this);
	nameEditor = new NameEditor(this);
	playground = new Playground(this);
	gameover = new GameOver(this);
	lastScore = 0;
	loadLeaderboard();

}

void Game::loadLeaderboard()
{
	std::ifstream learderboardFile(LEADERBOARD_FILE.c_str());

	while(learderboardFile.good())
  	{ 
		std::string name;
		int score;
		learderboardFile >> name;
		if(learderboardFile.good()) 
		{
			learderboardFile >> score;
			leaderboard.push_back(std::pair<std::string, int>(name, score));
		}
	}
	learderboardFile.close();
}

void Game::addRecord(std::string name, int score)
{
	lastScore = score;
	bool added = false;
	for(int i = 0; i < leaderboard.size(); i++)
	{
		if(score > leaderboard[i].second)
		{
			added = true;
			leaderboard.insert(leaderboard.begin() + i, std::pair<std::string, int>(name, score));
		}
	}
	if(!added)
	{
		leaderboard.push_back(std::pair<std::string, int>(name, score));
	}
	if(leaderboard.size() > 5)
	{
		leaderboard.erase(leaderboard.end()-1);
	}
}

bool Game::checkLastPlayer()
{
	std::ifstream lastPlayerFile(LASTPLAYERFILE.c_str());

	if(lastPlayerFile)
  	{ 
		char readString[DELIM];
		while(lastPlayerFile) 
		{
			lastPlayerFile.getline(readString, DELIM);
			if(lastPlayerFile)
				username = readString;
		}
	}
	if(username.size() == 0)
	{
		return false;	
	} 
	else 
	{
		return true;
	}
	
	lastPlayerFile.close();
}

void Game::update()
{
	Event e = window->pollForEvent();
	if(e.type() == QUIT)
	{
		quit();
	}

	if(state == MAIN_MENU)
	{
		mainMenu->update(&e);
	}

	else if(state == SCOREBOARD)
	{
		scoreboard->update(&e);
	}

	else if(state == EDIT_USERNAME)
	{
		nameEditor->update(&e);
	}

	else if(state == PLAYING)
	{
		playground->update(&e);
	}

	else if(state == GAME_OVER)
	{
		gameover->update(&e);
	}

}

void Game::draw()
{
	window->clear();
	if(state == MAIN_MENU)
	{
		mainMenu->draw(window);
	}
	else if(state == SCOREBOARD)
	{
		scoreboard->draw(window);
	}
	else if (state == EDIT_USERNAME)
	{
		nameEditor->draw(window);
	}
	else if(state == PLAYING)
	{
		playground->draw(window);
	}

	else if(state == GAME_OVER)
	{
		gameover->draw(window);
	}

	window->update_screen();
}

void Game::run()
{
	loadGame();
	while(running)
	{
		Delay(DELAY_TIME);
		update();
		draw();
	}
	delete window;
}

void Game::quit()
{
	running = false;
	std::ofstream lastPlayerFile(LASTPLAYERFILE.c_str());
	lastPlayerFile << username << std::endl;
	lastPlayerFile.close();
	saveLeaderboard();
}

void Game::changeState(GameState gameState)
{
	state = gameState;
	if(gameState == SCOREBOARD)
	{
		scoreboard->getScores();
	}
	else if (gameState == PLAYING)
	{
		playground->loadNewGame();
	}
}

void Game::setUsername(std::string name)
{
	username = name;
}

std::string Game::getUsername()
{
	return username;
}

int Game::getHighscore()
{
	if(leaderboard.empty())
		return 0;
	return leaderboard[0].second;
}

int Game::getLastScore()
{
	return lastScore;
}

std::vector<std::pair<std::string, int> > Game::getScores()
{
	return leaderboard;
}

void Game::saveLeaderboard()
{
	std::ofstream learderboardFile(LEADERBOARD_FILE.c_str());

	for(int i = 0; i < leaderboard.size(); i++)
	{
		learderboardFile << leaderboard[i].first << ' ' << leaderboard[i].second << std::endl;
	}

	learderboardFile.close();
}