#include "Scoreboard.hpp"

Scoreboard::Scoreboard(Game* owner)
{
	game = owner;
	menuButton.push_back(Button(Point(MARGIN, MARGIN + 500 + 3*SPACING), WINDOW_WIDTH - 2*MARGIN, 100, "Menu", PRIMARY_COLOR));
	selectedButtonIndex = 0;
	menuButton[selectedButtonIndex].select();
}
void Scoreboard::update(Event* event)
{
	if(event->type() == KEY_PRESS)
	{
		char btn = event->pressedKey();
		if(btn == ENTER_BUTTON)
		{
			game->changeState(MAIN_MENU);
		}
	}
}

void Scoreboard::draw(Window* window)
{
	window->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR);
	window->draw_png(BACKGROUND_NAME, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	window->show_text(RECORDS, 2*MARGIN, MARGIN, BLACK, FONT_NAME, FONT_SIZE + 10);
	menuButton[selectedButtonIndex].draw(window);
	for(int i = 0; i < namesNscores.size(); i++)
	{
		window->show_text(convertIntegerToString(i+1) + ". " + namesNscores[i], 2*MARGIN, 2*MARGIN + i*2*FONT_SIZE, BLACK, FONT_NAME, FONT_SIZE);
	}
}

void Scoreboard::getScores()
{
	namesNscores.clear();
	std::vector<std::pair<std::string, int> > scoreboard = game->getScores();
	for(int i = 0; i < scoreboard.size(); i++)
	{
		namesNscores.push_back(scoreboard[i].first + " " + convertIntegerToString(scoreboard[i].second));
	}
}

std::string Scoreboard::convertIntegerToString(int stringWannaBe)
{
	std::stringstream ss;
	ss << stringWannaBe;
	return ss.str();
}