#include <sfwdraw.h>

#include "Defines.h"
#include "AssetLib.h"
#include "GameState.h"
#include "GameLevel.h"

bool Level::loaded = false;

// We set up a static instance of GameState so that we may access the gamestate after it's initialized.
Game *& Level::game()
{
	static Game *gs;
	return gs;
}

// Set our texture name and level bounds. If this is our first session then load the texture.
Level::Level()
{
	textureName = "Map";

	if (!loaded)
		loadTexture(textureName, "../textures/BasicMap.png", 1, 1);

	negativeBounds = Vector2(-450, -440);
	positiveBounds = Vector2(450, 465);
}

// Draw the level background and tint it blue to simulate darkness.
void Level::Draw()
{
	RENDER(getTexture(textureName), -game()->camOffset.x, -game()->camOffset.y,
		960, 960, 0, true, 0,0x005aaeff);
}

// Get our levels bounds
Vector2 Level::getNegativeBounds()
{
	return negativeBounds;
}

Vector2 Level::getPositiveBounds()
{
	return positiveBounds;
}
