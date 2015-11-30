#pragma once


#include <string>

#include "GameObject.h"


class Game;

class Level
{
private:

	// Bounds used to keep the player in the map
	Vector2 negativeBounds;

	Vector2 positiveBounds;

	std::string textureName;

public:

	static Game *&game();				// Used to access gamestate info

	static bool loaded;					// Used to detect if we need to load textures still

	Level();

	void Draw();

	// Our getters
	Vector2 getNegativeBounds();

	Vector2 getPositiveBounds();
};