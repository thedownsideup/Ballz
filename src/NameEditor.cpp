#include "NameEditor.hpp"

NameEditor::NameEditor(Game* owner)
{
	game = owner;
	inputString = game->getUsername();
	buttons.push_back(Button(Point(MARGIN, MARGIN + 200 + 2*SPACING), WINDOW_WIDTH - 2*MARGIN, 100, "Save", PRIMARY_COLOR));
	buttons.push_back(Button(Point(MARGIN, MARGIN + 300 + 3*SPACING), WINDOW_WIDTH - 2*MARGIN, 100, "Cancel", PRIMARY_COLOR));
	selectedButtonIndex = 0;
	buttons[selectedButtonIndex].select();
}

void NameEditor::update(Event* event)
{
	processLastEvent(event);
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

void NameEditor::press()
{
	if(selectedButtonIndex == SAVE)
	{
		game->setUsername(inputString);
		game->changeState(MAIN_MENU);
	}

	if(selectedButtonIndex == CANCEL)
	{
		inputString = game->getUsername();
		game->changeState(MAIN_MENU);
	}
}

void NameEditor::draw(Window* win)
{
	win->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR);
	win->draw_png(BACKGROUND_NAME, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	win->fill_rect(MARGIN, 3*MARGIN, WINDOW_WIDTH - 2*MARGIN, MARGIN, PRIMARY_COLOR);
	win->show_text(" " + inputString, MARGIN + 2, 3*MARGIN, BLACK, FONT_NAME, FONT_SIZE);
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(win);
	}
}

void NameEditor::processLastEvent(Event* event)
{
	if(event->type() == KEY_PRESS)
	{
		if(event->pressedKey() == BACKSPACE_BUTTON && inputString.size() > 0)
		{
			inputString.erase(inputString.size() - 1);
		}
		else if(event->pressedKey() >= 'a' && event->pressedKey() <= 'z')
		{
			if(inputString.size() < MAX_STRING_LENGTH)
			{
				inputString += event->pressedKey();
			}
		}
	}
}
