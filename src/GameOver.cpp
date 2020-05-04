#include "GameOver.hpp"

GameOver::GameOver(Game* owner)
{
	game = owner;
	buttons.push_back(Button(Point(MARGIN, MARGIN + 400 + 2*SPACING), (WINDOW_WIDTH - 2*MARGIN - SPACING)/2, 100, "Menu", PRIMARY_COLOR));
	buttons.push_back(Button(Point(MARGIN + (WINDOW_WIDTH - 2*MARGIN - SPACING)/2 + SPACING, MARGIN + 400 + 2*SPACING), (WINDOW_WIDTH - 2*MARGIN - SPACING)/2, 100, "New Game", PRIMARY_COLOR));
	selectedButtonIndex = 0;
	buttons[selectedButtonIndex].select();
}

void GameOver::update(Event* event)
{
	if(event->type() == KEY_PRESS)
	{
		char btn = event->pressedKey();
		if(btn == RIGHT_BUTTON)
		{
			buttons[selectedButtonIndex].deselect();
			selectedButtonIndex--;

			if(selectedButtonIndex < 0)
			{
				selectedButtonIndex = buttons.size()-1;
			}

			buttons[selectedButtonIndex].select();
		}
		else if(btn == LEFT_BUTTON)
		{
			buttons[selectedButtonIndex].deselect();
			selectedButtonIndex++;

			if(selectedButtonIndex > buttons.size()-1)
			{
				selectedButtonIndex = 0;
			}

			buttons[selectedButtonIndex].select();
		}
		else if(btn == ENTER_BUTTON)
		{
			press();
		}
	}
}

void GameOver::draw(Window* window)
{
	window->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR);
	window->draw_png(BACKGROUND_NAME , 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	window->show_text(GAMEOVER, 130 , 100, BLACK, FONT_NAME, FONT_SIZE + 30);
	window->show_text("Highscore: " + convertIntegerToString(game->getHighscore()), 130 , 200, BLACK, FONT_NAME, FONT_SIZE);
	window->show_text("Score: " + convertIntegerToString(game->getLastScore()), 130 , 300, BLACK, FONT_NAME, FONT_SIZE);
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(window);
	}
}

void GameOver::press()
{
	if(selectedButtonIndex == NEWGAME)
	{
		game->changeState(PLAYING);
	}

	if(selectedButtonIndex == MENU)
	{
		game->changeState(MAIN_MENU);
	}

}

std::string GameOver::convertIntegerToString(int stringWannaBe)
{
	std::stringstream ss;
	ss << stringWannaBe;
	return ss.str();
}