#include <sfwdraw.h>

#include "AssetLib.h"
#include "GameState.h"
#include "Enemy.h"


// Set our static bool loaded to false by default. Used in detecting if we've loaded textures yet.
bool Enemy::loaded = false;

// In our enemy constructor we want to set some default values.
// If it's our first time creating an enemy then we want to load the sprite.
Enemy::Enemy()
{
	setDim(Vector2(32, 32));
	setHealth(0);

	accRate = 100;
	maxSpeed = 0.8f;
	decRate = 50;

	setArmor(2);
	setDamage(10);

	setSpriteName("Enemy");
	
	if (!loaded)
	{
		loadTexture(getSpriteName(), "../textures/enemy.png", 1, 1);
		loaded = true;
	}
}

#pragma region GettersAndSetters

// Getters
int Enemy::getHealth()
{
	return health;
}

int Enemy::getArmor()
{
	return armor;
}

int Enemy::getDamage()
{
	return damage;
}

// Setters
void Enemy::setHealth(int h)
{
	health = h;
}

void Enemy::setArmor(int a)
{
	armor = a;
}

void Enemy::setDamage(int d)
{
	damage = d;
}

#pragma endregion

bool Enemy::scoreCheck()
{
	if (previousHealth > 0 && health <= 0)
	{
		previousHealth = health;
		return true;
	}
	else
	{
		previousHealth = health;
		return false;
	}
}

// Our track function finds the position of the player and moves us towards them.
void Enemy::Track()
{
	// Reset the acceleration each time in case we don't need to move.
	setAcc(Vector2(0, 0));

	// Check what direction brings us towards the player. Don't accelerate if we're on them.
	if		(game()->getPlayer().getPos().x > getPos().x + (game()->getPlayer().getDim().x / 2))
	{
		setAcc(Vector2(accRate, getAcc().y));
	}

	else if (game()->getPlayer().getPos().x < getPos().x - (game()->getPlayer().getDim().x / 2))
	{
		setAcc(Vector2(-accRate, getAcc().y));
	}


	if		(game()->getPlayer().getPos().y > getPos().y + (game()->getPlayer().getDim().y / 2))
	{
		setAcc(Vector2(getAcc().x, accRate));
	}

	else if (game()->getPlayer().getPos().y < getPos().y - (game()->getPlayer().getDim().y / 2))
	{
		setAcc(Vector2(getAcc().x, -accRate));
	}

	// Apply the acceleration to the velocity
	setVel(Vector2(getVel().x + (getAcc().x * sfw::getDeltaTime()), getVel().y + (getAcc().y * sfw::getDeltaTime())));

	// Cap the speed
	applyMaxSpeed();

	// Decelerate if we aren't accelerating
	applyDeceleration();

	// Use all the information we just calculated to move accordingly
	setPos(Vector2(getPos().x + getVel().x, getPos().y + getVel().y));
}

void Enemy::takeDamage(int d)
{
	health -= (d / armor);
}
