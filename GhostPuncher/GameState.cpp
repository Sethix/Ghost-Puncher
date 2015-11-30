#include "GameState.h"
#include "AssetLib.h"

// In our constructor we want to set up some default values
// As well as set the static instances of our gamestate in our
// Objects and level.
Game::Game()
{
	sfw::setBackgroundColor(BLACK);

	GameObject::game() = this;
	Level::game() = this;

	hScore = 0;
	tempHScore = 0;

	hScoreString = "Score: ";
	
	highScore.open("../data/Score.dat", std::ios::in | std::ios::binary);

	if (highScore.is_open())
	{
		while (!highScore.eof() && highScore.peek() != EOF)
			highScore.read((char*)&hScore, sizeof(int));
	}
	else
	{
		highScore.open("../data/Score.dat", std::ios::out | std::ios::trunc | std::ios::binary);
		highScore.write((char*)&hScore, sizeof(int));
	}

	highScore.close();

	mainMenu.SetScoreString(hScore);

	camPos.x = 0;
	camPos.x = 0;

	camOffset.x = -200;
	camOffset.y = -200;

	setPhaseScores(5, 15, 50);
	setTimers(6, 4, 2, 0.5f);

	state = SplashScreen;
	
	exiting = false;
	spawning = false;
	endScoreCheck = false;
}

#pragma region GettersAndSetters

// Our getters
STATE Game::getGameState()
{
	return state;
}

Player Game::getPlayer()
{
	return player;
}

float Game::getTimer(int i)
{
	switch (i)
	{
	case 0:
		return phaseZeroTimer;
	case 1:
		return phaseOneTimer;
	case 2:
		return phaseTwoTimer;
	case 3: 
		return phaseThreeTimer;
	default:
		return phaseOneTimer;
	}
}

int Game::getPhase(int i)
{
	switch (i)
	{
	case 1:
		return phaseOneScore;
	case 2:
		return phaseTwoScore;
	case 3:
		return phaseThreeScore;
	default:
		return phaseOneScore;
	}
}

// Our setters
void Game::setGameState(STATE s)
{
	state = s;
}

void Game::SetScoreString(int score)
{
	hScoreStream.clear();
	hScoreStream.str(std::string());
	hScoreStream << hScoreString << score;
}

void Game::setTimers(float i, float a, float b, float c)
{
	phaseZeroTimer	= i;
	phaseOneTimer	= a;
	phaseTwoTimer	= b;
	phaseThreeTimer = c;
}

void Game::setPhaseScores(int a, int b, int c)
{
	phaseOneScore	= a;
	phaseTwoScore	= b;
	phaseThreeScore = c;
}

#pragma endregion

// Our exit game function. Counts two and a half seconds then closes.
void Game::ExitFunction()
{
	if (exiting == false)
	{
		exitTimer = sfw::getTime() + 2.5f;

		exiting = true;
	}

	if (sfw::getTime() > exitTimer && exitTimer != NULL)
		sfw::termContext();
}

// Our spawn enemy function. Counts the appropriate time then spawns an enemy
// At a random spawn location. Stats depend on spawn location.
void Game::SpawnEnemy()
{
	if (spawning == false)
	{
		if       (player.getKillCount() < getPhase(1))
			spawnTimer = sfw::getTime() + getTimer(0);

		else if  (player.getKillCount() < getPhase(2))
			spawnTimer = sfw::getTime() + getTimer(1);

		else if  (player.getKillCount() < getPhase(3))
			spawnTimer = sfw::getTime() + getTimer(2);

		else if (player.getKillCount() >= getPhase(3))
			spawnTimer = sfw::getTime() + getTimer(3);

		spawning = true;
	}

	if (spawning == true && sfw::getTime() > spawnTimer && spawnTimer != NULL)
	{

		for (int i = 0; i < 200; ++i)
		{

			if (enemies[i].getHealth() <= 0)
			{

				switch (rand() % 4)
				{

				case 0:
					enemies[i].setHealth(80);
					enemies[i].setPos(Vector2(440, 450));
					break;
				
				case 1:
					enemies[i].setHealth(100);
					enemies[i].setPos(Vector2(-440, 450));
					break;
				
				case 2:
					enemies[i].setHealth(120);
					enemies[i].setPos(Vector2(440, -430));
					break;

				case 3:
					enemies[i].setHealth(100);
					enemies[i].setPos(Vector2(-440, -430));
					break;
				}

				break;
			}
		}

		spawning = false;

	}
}

// Our main function. Called every frame and changes depending on the game state.
void Game::Run()
{
	switch (getGameState())
	{
	case SplashScreen:				// Draw the splash and check for start button.

		mainMenu.Input();

		if (mainMenu.getSplashState() == false) setGameState(TitleMenu);

		Draw();

		break;

	case TitleMenu:					// Draw main menu and allow navigation between menus.
		
		mainMenu.Input();
		
		if (mainMenu.getSplashState() == true) setGameState(SplashScreen);

		// When we select a menu option change the state accordingly.
		if (mainMenu.getStateChange())
		{
			switch (mainMenu.getCurrentSelection())
			{
			case 0:
				setGameState(GameScreen);
				break;
			case 1:
				setGameState(ExitMenu);
				break;
			}
		}

		Draw();

		break;
	case ScoreMenu:
		break;
	case GameScreen:				// This is where we play the game.
									// We want to spawn enemies, move the camera to the player
		SpawnEnemy();				// Update the player animations, keep the player in the level
									// Move enemies, Allow spawning and moving projectiles
		followPlayer();				// And then finally draw everything.

		player.update();

		player.boundsCheck(mainLevel.getNegativeBounds(), mainLevel.getPositiveBounds());

		for (int i = 0; i < 200; ++i)
		{
			if (enemies[i].scoreCheck() == true)
				player.incrementScore();

			if (enemies[i].getHealth() > 0)
			{
				enemies[i].Track();

				for (int j = 0; j < FLAME_COUNT; ++j)

					if (enemies[i].CollisionCheck(flames[j]) && player.getHealth() > 0)

						enemies[i].takeDamage(player.getDamage());

			}
		}

		for (int i = 0; i < FLAME_COUNT; ++i)
		{
			flames[i].Move();
		}

		for (int i = 0; i < 200; ++i)

			if (enemies[i].getHealth() > 0)

				if (player.CollisionCheck(enemies[i]))

					player.takeDamage(enemies[i].getDamage());

		SetScoreString(player.getKillCount());

		Draw();

		break;
	case GameOverScreen:

		if (endScoreCheck == false)
		{
			hScore = player.getKillCount();

			highScore.open("../data/Score.dat", std::ios::in | std::ios::binary);

			while (!highScore.eof() && highScore.peek() != EOF)
				highScore.read((char*)&tempHScore, sizeof(int));

			if (tempHScore < hScore)
			{
				highScore.close();
				highScore.open("../data/Score.dat", std::ios::out | std::ios::trunc | std::ios::binary);
				highScore.write((char*)&hScore, sizeof(int));
				endMenu.beatScore = true;
			}

			highScore.close();

			endScoreCheck = true;
		}

		endMenu.Input();

		// When we select a menu option change the state accordingly.
		if (endMenu.getStateChange())
		{
			camPos.x = 0;
			camPos.y = 0;
			player = Player();
			player.setKillCount(0);
			for (int i = 0; i < 200; ++i)
				enemies[i] = Enemy();
			for (int i = 0; i < FLAME_COUNT; ++i)
				flames[i] = Projectile();

			switch (endMenu.getCurrentSelection())
			{
			case 0:
				setGameState(GameScreen);
				endMenu.setCurrentSelection(0);
				endMenu.setStateChange(false);
				endScoreCheck = false;
				break;
			case 1:
				setGameState(TitleMenu);
				mainMenu.setSplashState(true);
				mainMenu.setCurrentSelection(0);
				mainMenu.setStateChange(false);
				endMenu.setCurrentSelection(0);
				endMenu.setStateChange(false);
				endScoreCheck = false;

				mainMenu.SetScoreString(hScore);

				break;
			case 2:
				setGameState(ExitMenu);
				break;
			}

			endScoreCheck = false;
		}

		Draw();

		break;
	case ExitMenu:					// Draw the exit screen and exit after the appropriate time.

		Draw();

		mainMenu.setExiting(true);

		ExitFunction();

		break;
	case Options:
		break;
	case HowToMenu:
		break;
	case Credits:
		break;
	default:
		break;
	}
}

// Check the players position and move the camera accordingly.
// Cap out at 280 or -280
void Game::followPlayer()
{
	if (player.getPos().x > camPos.x + 50)
	{
		camPos.x += 4;
	}
	else if (player.getPos().x < camPos.x - 50)
	{
		camPos.x -= 4;
	}
	if (player.getPos().y > camPos.y + 50)
	{
		camPos.y += 4;
	}
	else if (player.getPos().y < camPos.y - 50)
	{
		camPos.y -= 4;
	}

	if (camPos.x > 280)
	{
		camPos.x = 280;
	}
	else if (camPos.x < -280)
	{
		camPos.x = -280;
	}
	if (camPos.y > 280)
	{
		camPos.y = 280;
	}
	else if (camPos.y < -280)
	{
		camPos.y = -280;
	}

	camOffset.x = camPos.x - 200;
	camOffset.y = camPos.y - 200;
}

// Check what state we're in and draw sprites accordingly.
void Game::Draw()
{
	switch (getGameState())
	{
	case SplashScreen:

	case TitleMenu:

		mainMenu.Draw();

		break;

	case ScoreMenu:
		break;
	case GameScreen:

		mainLevel.Draw();

		player.draw();

		for (int i = 0; i < 200; ++i)
		{
			if (enemies[i].getHealth() > 0)
			{
				enemies[i].draw();
			}
		}

		for (int i = 0; i < FLAME_COUNT; ++i)
		{
			flames[i].draw();
		}

		DRAW_TEXT(getTexture(mainMenu.getFontMap()), hScoreStream.str().c_str(), 260, 20, 10, 10, 0, 0, WHITE);

		break;
	case GameOverScreen:

		endMenu.Draw();

		break;
	case ExitMenu:
		
		mainMenu.Draw();

		break;
	case HowToMenu:
		break;
	case Credits:
		break;
	default:
		break;
	}

}
