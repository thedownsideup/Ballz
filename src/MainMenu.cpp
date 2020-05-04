#include "MainMenu.hpp"

MainMenu::MainMenu(Game* owner)
{
	game = owner;
	buttons.push_back(Button(Point(MARGIN, MARGIN), WINDOW_WIDTH - 2*MARGIN, 100, "New Game", PRIMARY_COLOR));
	buttons.push_back(Button(Point(MARGIN, MARGIN + 100 + SPACING), WINDOW_WIDTH - 2*MARGIN, 100, "Scoreboard", PRIMARY_COLOR));
	buttons.push_back(Button(Point(MARGIN, MARGIN + 200 + 2*SPACING), WINDOW_WIDTH - 2*MARGIN, 100, "Edit Username", PRIMARY_COLOR));
	buttons.push_back(Button(Point(MARGIN, MARGIN + 300 + 3*SPACING), WINDOW_WIDTH - 2*MARGIN, 100, "Exit", PRIMARY_COLOR));
	selectedButtonIndex = 0;
	buttons[selectedButtonIndex].select();
}

void MainMenu::update(Event* event)
{
	if(event->type() == KEY_PRESS)
	{
		char btn = event->pressedKey();
		if(btn == UP_BUTTON)
		{
			buttons[selectedButtonIndex].deselect();
			selectedButtonIndex--;

			if(selectedButtonIndex < 0)
			{
				selectedButtonIndex = buttons.size()-1;
			}

			buttons[selectedButtonIndex].select();
		}
		else if(btn == DOWN_BUTTON)
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

void MainMenu::draw(Window* window)
{
	window->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR);
	window->draw_png(BACKGROUND_NAME, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(window);
	}
}

void MainMenu::press()
{
	if(selectedButtonIndex == PLAY)
	{
		game->changeState(PLAYING);
	}

	if(selectedButtonIndex == SCORE)
	{
		game->changeState(SCOREBOARD);
	}

	if(selectedButtonIndex == EDIT)
	{
		game->changeState(EDIT_USERNAME);
	}

	if(selectedButtonIndex == EXIT)
	{
		game->quit();
	}
}