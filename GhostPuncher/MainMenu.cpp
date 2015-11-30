#include "MainMenu.h"
#include "AssetLib.h"

bool MainMenu::loaded = false;

// Set our start values and load our menu textures if it's our first time at the screen.
MainMenu::MainMenu()
{
	setCurrentSelection(0);
	setSplashState(true);
	setChangedSelection(false);
	setExiting(false);

	hScoreString = "High score: ";

	setSelectedTexture("Select");
	setSplashTexture("Splash");
	setFontMap("Font");

	if (!loaded)
	{
		loadTexture(selectedTexture, "../textures/select.png", 1, 1);
		loadTexture(splashTexture, "../textures/splash.bmp", 1, 1);
		loadTexture(fontMap, "../textures/fontmap.png", 16, 16);
	}
}

#pragma region GettersAndSetters

// Our getters
std::string MainMenu::getSplashTexture()
{
	return splashTexture;
}

std::string MainMenu::getSelectedTexture()
{
	return selectedTexture;
}

std::string MainMenu::getFontMap()
{
	return fontMap;
}

int MainMenu::getCurrentSelection()
{
	return currentSelection;
}

bool MainMenu::getSplashState()
{
	return splashState;
}

bool MainMenu::getChangedSelection()
{
	return changedSelection;
}

bool MainMenu::getStateChange()
{
	return stateChange;
}

// Our setters
void MainMenu::setSplashTexture(std::string s)
{
	splashTexture = s;
}

void MainMenu::setSelectedTexture(std::string s)
{
	selectedTexture = s;
}

void MainMenu::setFontMap(std::string s)
{
	fontMap = s;
}

void MainMenu::setCurrentSelection(int s)
{
	currentSelection = s;
}

void MainMenu::setSplashState(bool b)
{
	splashState = b;
}

void MainMenu::setChangedSelection(bool b)
{
	changedSelection = b;
}

void MainMenu::setStateChange(bool b)
{
	stateChange = b;
}

void MainMenu::setExiting(bool b)
{
	exiting = b;
}

#pragma endregion

void MainMenu::SetScoreString(int score)
{
	hScoreStream.clear();
	hScoreStream.str(std::string());
	hScoreStream << hScoreString << score;
}

// Where we check for button/key input.
void MainMenu::Input()
{
	// If we're not at the splash screen, move through menu options and allow selecting
	if (!getSplashState())
	{
		if (BUTTON_TWO)
		{
			Select();
		}
		if (BUTTON_ONE)
		{
			setSplashState(true);
		}
		if (BUTTON_DOWN && !getChangedSelection())
		{
			if (currentSelection < 1)
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

	// Else we want to press start to play.
	else
	{
		if (BUTTON_START)
			setSplashState(false);
	}
}

// Tell our game state it's time to change states.
void MainMenu::Select()
{
	setStateChange(true);
}

// Draw the splash screen and menu.
void MainMenu::Draw()
{
	if (splashState)
	{
		RENDER(getTexture(splashTexture), 0, TEXTURE_HEIGHT(getTexture(splashTexture)), TEXTURE_WIDTH(getTexture(splashTexture)), TEXTURE_HEIGHT(getTexture(splashTexture)), 0, false);

		DRAW_TEXT(getTexture(fontMap), SPLASH_TEXT, 100, 100, 16, 16, 0, 0, WHITE);
	}
	else if (exiting)
	{
		RENDER(getTexture(splashTexture), 0, TEXTURE_HEIGHT(getTexture(splashTexture)), TEXTURE_WIDTH(getTexture(splashTexture)), TEXTURE_HEIGHT(getTexture(splashTexture)), 0, false);

		DRAW_TEXT(getTexture(fontMap), EXIT_TEXT, 50, 300, 16, 16, 0, 0, WHITE);
	}
	else
	{
		RENDER(getTexture(splashTexture), 0, TEXTURE_HEIGHT(getTexture(splashTexture)), TEXTURE_WIDTH(getTexture(splashTexture)), TEXTURE_HEIGHT(getTexture(splashTexture)), 0, false);

		DRAW_TEXT(getTexture(fontMap), MAINMENU_OPTION_ONE, 40, 100, 16, 16, 0, 0, WHITE);

		DRAW_TEXT(getTexture(fontMap), MAINMENU_OPTION_TWO, 60, 80, 16, 16, 0, 0, WHITE);

		DRAW_TEXT(getTexture(fontMap), hScoreStream.str().c_str(), 30, 30, 16, 16, 0, 0, WHITE);

		switch (getCurrentSelection())
		{
		case 0:
			RENDER(getTexture(selectedTexture), 20, 100, 20, 20, 0, 0);
			break;
		case 1:
			RENDER(getTexture(selectedTexture), 40, 80, 20, 20, 0, 0);
			break;
		}
	}
}
