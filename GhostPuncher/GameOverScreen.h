#pragma once


#include <string>
#include <sstream>
#include <sfwdraw.h>

#include "Defines.h"


class GameOverMenu
{
private:

	std::string backgroundTexture;

	std::string selectedTexture;

	std::string fontMap;

	int currentSelection;				// Our current selected menu option

	bool changedSelection;				// Check if we've changed the menu selection.

	bool stateChange;					// Check if we've selected a menu option then change states.

	bool exiting;						// Used in checking if we're closing the game.


public:

	static bool loaded;					// Used in checking if we've loaded the textures yet.

	bool beatScore;						// Did we beat the high score?

	GameOverMenu();

#pragma region GettersAndSetters

	std::string getBackgroundTexture();

	std::string getSelectedTexture();

	std::string getFontMap();

	int getCurrentSelection();

	bool getChangedSelection();

	bool getStateChange();

	void setBackgroundTexture(std::string s);

	void setSelectedTexture(std::string s);

	void setFontMap(std::string s);

	void setCurrentSelection(int s);

	void setChangedSelection(bool b);

	void setStateChange(bool b);

	void setExiting(bool b);

#pragma endregion

	void Input();						// Gets input to navigate the menu

	void Select();						// Allows us to select a menu option

	void Draw();

};