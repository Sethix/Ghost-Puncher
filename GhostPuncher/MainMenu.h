#pragma once


#include <sstream>
#include <string>
#include <sfwdraw.h>

#include "Defines.h"


class MainMenu
{
private:

	std::string splashTexture;

	std::string selectedTexture;

	std::string fontMap;

	std::string hScoreString;

	std::ostringstream hScoreStream;

	bool splashState;					// Are we at the splash screen?

	int currentSelection;				// Our current selected menu option

	bool changedSelection;				// Have we changed the menu selection?

	bool stateChange;					// Have we selected a menu option?

	bool exiting;						// Used in checking if we're closing the game.


public:

	static bool loaded;
	
	MainMenu();

#pragma region GettersAndSetters

	std::string getSplashTexture();

	std::string getSelectedTexture();

	std::string getFontMap();

	int getCurrentSelection();

	bool getSplashState();

	bool getChangedSelection();

	bool getStateChange();

	void setSplashTexture(std::string s);

	void setSelectedTexture(std::string s);

	void setFontMap(std::string s);

	void setCurrentSelection(int s);

	void setSplashState(bool b);

	void setChangedSelection(bool b);

	void setStateChange(bool b);

	void setExiting(bool b);

#pragma endregion

	void SetScoreString(int score);		// Used in checking if we've loaded the textures yet.

	void Input();						// Gets input to navigate the menu

	void Select();						// Allows us to select a menu option

	void Draw();

};