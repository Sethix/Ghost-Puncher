#pragma once


#include <fstream>
#include <sstream>

#include "MainMenu.h"
#include "GameOverScreen.h"
#include "GameLevel.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"


enum STATE
{
	SplashScreen = 0,
	TitleMenu = 1,
	ScoreMenu = 2,
	GameScreen = 3,
	GameOverScreen = 4,
	ExitMenu = 5,
	Options = 6,
	HowToMenu = 7,
	Credits = 8
};


class Game
{
private:

	STATE state;							// The current state of the game.

	std::string hScoreString;				// The string stream prefix

	std::ostringstream hScoreStream;		// Our high score stream. Prefixed with the string, suffixed with the score.

	std::fstream highScore;					// Our high score file stream.

	MainMenu mainMenu;						// Our main menu object.

	GameOverMenu endMenu;					// Our end menu object.

	Level mainLevel;						// Our main level object.

	Enemy enemies[200];						// Our enemy objects.

	Player player;							// Our player object.

	bool exiting;							// Are we exiting the game?

	bool spawning;							// Do we need to spawn another enemy?

	float exitTimer;						// Wait time to exit the game

	float spawnTimer;						// Wait time to spawn an enemy


	float phaseZeroTimer;					// How long the spawn timer should be per phase

	float phaseOneTimer;

	float phaseTwoTimer;

	float phaseThreeTimer;


	int phaseOneScore;						// How many points we need to reach each phase

	int phaseTwoScore;

	int phaseThreeScore;


	int hScore;								// Our high score

	int tempHScore;							// Temporary high score loaded from file

	bool endScoreCheck;						// Used to determine if we need to load the high score

public:

	Game();

	Vector2 camOffset;						// Our camera offset. Used for drawing things in the middle of the screen.

	Vector2 camPos;							// The position of our camera. Follows the player after they leave the center of the screen.

	Projectile flames[FLAME_COUNT];			// Our projectiles. They follow the player unless they're attacking.

#pragma region GettersAndSetters

	STATE getGameState();

	Player getPlayer();

	float getTimer(int i);

	int getPhase(int i);

	void setGameState(STATE s);

	void SetScoreString(int score);

	void setTimers(float i, float a, float b, float c);

	void setPhaseScores(int a, int b, int c);

#pragma endregion

	void ExitFunction();					// Our exit function. Counts down to the exit.

	void SpawnEnemy();						// Spawn (revive) an enemy in a random corner with stats depending on the corner.

	void Run();								// Executes every frame. Changes depending on gamestate.

	void followPlayer();					// Makes the camera follow the player.

	void Draw();							// Calls the draw functions from each object.
};