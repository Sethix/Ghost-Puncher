#include "GameOverScreen.h"
#include "AssetLib.h"

bool GameOverMenu::loaded = false;

// Set our start values and load our menu textures if it's our first time at the screen.
GameOverMenu::GameOverMenu()
{
	setCurrentSelection(0);
	setChangedSelection(false);
	setExiting(false);
	beatScore = false;

	setSelectedTexture("Select");
	setBackgroundTexture("GameOverBackground");
	setFontMap("Font");

	if (!loaded)
	{
		loadTexture(backgroundTexture, "../textures/gameover.png", 1, 1);
	}
}

#pragma region GettersAndSetters

std::string GameOverMenu::getBackgroundTexture()
{
	return backgroundTexture;
}

// Our getters
std::string GameOverMenu::getSelectedTexture()
{
	return selectedTexture;
}

std::string GameOverMenu::getFontMap()
{
	return fontMap;
}

int GameOverMenu::getCurrentSelection()
{
	return currentSelection;
}

bool GameOverMenu::getChangedSelection()
{
	return changedSelection;
}

bool GameOverMenu::getStateChange()
{
	return stateChange;
}

// Our setters
void GameOverMenu::setBackgroundTexture(std::string s)
{
	backgroundTexture = s;
}

void GameOverMenu::setSelectedTexture(std::string s)
{
	selectedTexture = s;
}

void GameOverMenu::setFontMap(std::string s)
{
	fontMap = s;
}

void GameOverMenu::setCurrentSelection(int s)
{
	currentSelection = s;
}

void GameOverMenu::setChangedSelection(bool b)
{
	changedSelection = b;
}

void GameOverMenu::setStateChange(bool b)
{
	stateChange = b;
}

void GameOverMenu::setExiting(bool b)
{
	exiting = b;
}

#pragma endregion

// Where we check for button/key input.
void GameOverMenu::Input()
{
	// If we're not at the splash screen, move through menu options and allow selecting
	if (BUTTON_TWO)
	{
		Select();
	}

	if (BUTTON_DOWN && !getChangedSelection())
	{
		if (currentSelection < 2)
			currentSelection++;

		setChangedSelection(true);
	}
	else if (BUTTON_UP && !getChangedSelection())
	{
		if (currentSelection > 0)
			currentSelection--;

		setChangedSelection(true);
	}

	if (MOVEMENT_INACTIVE) setChangedSelection(false);
}

// Tell our game state it's time to change states.
void GameOverMenu::Select()
{
	setStateChange(true);
}

// Draw the splash screen and menu.
void GameOverMenu::Draw()
{
	if (exiting)
	{
		RENDER(getTexture(backgroundTexture), 0, TEXTURE_HEIGHT(getTexture(backgroundTexture)), TEXTURE_WIDTH(getTexture(backgroundTexture)), TEXTURE_HEIGHT(getTexture(backgroundTexture)), 0, false);

		DRAW_TEXT(getTexture(fontMap), EXIT_TEXT, 50, 300, 16, 16, 0, 0, WHITE);
	}
	else
	{
		RENDER(getTexture(backgroundTexture), 0, TEXTURE_HEIGHT(getTexture(backgroundTexture)), TEXTURE_WIDTH(getTexture(backgroundTexture)), TEXTURE_HEIGHT(getTexture(backgroundTexture)), 0, false);

		if (beatScore)
		{
			DRAW_TEXT(getTexture(fontMap), GAMEOVER_WIN_TEXT, 100, 300, 12, 12, 0, 0, WHITE);
		}
		else
		{
			DRAW_TEXT(getTexture(fontMap), GAMEOVER_LOSE_TEXT, 100, 300, 12, 12, 0, 0, WHITE);
		}

		DRAW_TEXT(getTexture(fontMap), GAMEOVER_OPTION_ONE, 40, 100, 16, 16, 0, 0, WHITE);

		DRAW_TEXT(getTexture(fontMap), GAMEOVER_OPTION_TWO, 60, 80, 16, 16, 0, 0, WHITE);

		DRAW_TEXT(getTexture(fontMap), GAMEOVER_OPTION_THREE, 80, 60, 16, 16, 0, 0, WHITE);

		switch (getCurrentSelection())
		{
		case 0:
			RENDER(getTexture(selectedTexture), 20, 100, 20, 20, 0, 0);
			break;
		case 1:
			RENDER(getTexture(selectedTexture), 40, 80, 20, 20, 0, 0);
			break;
		case 2:
			RENDER(getTexture(selectedTexture), 60, 60, 20, 20, 0, 0);
			break;
		}
	}
}
