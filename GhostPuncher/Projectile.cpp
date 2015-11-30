#include <math.h>

#include "AssetLib.h"
#include "GameState.h"
#include "Projectile.h"

bool Projectile::loaded = false;

// Set our default damage, position and velocity
Projectile::Projectile()
{
	setDamage(1);
	
	switch (rand() % 10)
	{
	case 0:
		setPos(Vector2(-10, 0));
		break;
	case 1:
		setPos(Vector2(-20, 0));
		break;
	case 2:
		setPos(Vector2(-10, -10));
		break;
	case 3:
		setPos(Vector2(10, 10));
		break;
	case 4:
		setPos(Vector2(10, -10));
		break;
	case 5:
		setPos(Vector2(10, -20));
		break;
	case 6:
		setPos(Vector2(20, -10));
		break;
	case 7:
		setPos(Vector2(-10, 20));
		break;
	case 8:
		setPos(Vector2(-20, 10));
		break;
	case 9:
		setPos(Vector2(-10, 30));
		break;
	default:
		setPos(Vector2(-30, 10));
		break;
		break;
	}

	setVel(Vector2(0, 0));
	setDim(Vector2(16, 16));

	accRate = 8;
	attackSpeed = 12;
	maxSpeed = 10;

	attackTimer = 2;
	timerSet = false;

	dest = Vector2(0, 0);
	attacking = false;

	setSpriteName("Projectile");

	if (!loaded)
	{
		loadTexture(getSpriteName(), "../textures/projectile.png", 1, 1);
		loaded = true;
	}
}

// Create our projectile with parameters
Projectile::Projectile(int d, Vector2 p, Vector2 v)
{
	setDamage(d);
	setPos(p);
	setVel(v);
}

#pragma region GettersAndSetters

// Our getters
int Projectile::getDamage()
{
	return damage;
}

// Our setters
void Projectile::setDamage(int d)
{
	damage = d;
}

#pragma endregion

void Projectile::Move()
{
	// Reset the acceleration each time in case we don't need to move.
	setAcc(Vector2(0, 0));

	if (attacking)
	{
		if (timerSet == false)
		{
			currentAttackTimer = attackTimer + sfw::getTime();
			timerSet = true;
		}

		// Check what direction brings us towards the destination.
		if		(dest.x > getPos().x - 20)
		{
			if(getVel().x < -0.5f)
				setAcc(Vector2(attackSpeed * 4, getAcc().y));
			else
				setAcc(Vector2(attackSpeed, getAcc().y));
		}

		else if (dest.x < getPos().x + 20)
		{
			if(getVel().x > 0.5f)
				setAcc(Vector2(-attackSpeed * 4, getAcc().y));
			else
				setAcc(Vector2(-attackSpeed, getAcc().y));
		}


		if		(dest.y > getPos().y - 20)
		{
			if(getVel().y < -0.5f)
				setAcc(Vector2(getAcc().x, attackSpeed * 4));
			else
				setAcc(Vector2(getAcc().x, attackSpeed));
		}

		else if (dest.y < getPos().y + 20)
		{
			if(getVel().y > 0.5f)
				setAcc(Vector2(getAcc().x, -attackSpeed * 4));
			else
				setAcc(Vector2(getAcc().x, -attackSpeed));
		}


		if (attackTimer < sfw::getTime())
		{
			attacking = false;
			timerSet = false;
		}

		else if(getPos().x > dest.x - 5 && getPos().x < dest.x + 5 &&
				getPos().y > dest.y - 5 && getPos().y < dest.y + 5)
		{
			attacking = false;
			timerSet = false;
		}

	}
	else
	{
		// Check what direction brings us towards the player.
		if		(game()->getPlayer().getPos().x >= getPos().x)
		{
			if (getVel().x < -0.5f)
				setAcc(Vector2(accRate * 1.5f, getAcc().y));
			else
				setAcc(Vector2(accRate, getAcc().y));
		}

		else if (game()->getPlayer().getPos().x < getPos().x)
		{
			if (getVel().x > 0.5f)
				setAcc(Vector2(-accRate * 1.5f, getAcc().y));
			else
				setAcc(Vector2(-accRate, getAcc().y));
		}


		if		(game()->getPlayer().getPos().y >= getPos().y)
		{
			if (getVel().y < -0.5f)
				setAcc(Vector2(getAcc().x, accRate * 1.5f));
			else
				setAcc(Vector2(getAcc().x, accRate));
		}

		else if (game()->getPlayer().getPos().y < getPos().y)
		{
			if (getVel().y > 0.5f)
				setAcc(Vector2(getAcc().x, -accRate * 1.5f));
			else
				setAcc(Vector2(getAcc().x, -accRate));
		}
	}

	// Apply the acceleration to the velocity
	if (getAcc().x == 0 && getAcc().y == 0)
		setVel(Vector2(getVel().x / 4, getVel().y / 4));
	else if (getAcc().x == 0)
		setVel(Vector2(getVel().x / 4, getVel().y + (getAcc().y * sfw::getDeltaTime())));
	else if (getAcc().y == 0)
		setVel(Vector2(getVel().x + (getAcc().x * sfw::getDeltaTime()), getVel().y / 4));
	else
		setVel(Vector2(getVel().x + (getAcc().x * sfw::getDeltaTime()), getVel().y + (getAcc().y * sfw::getDeltaTime())));
	
	applyMaxSpeed();

	// Use all the information we just calculated to move accordingly
	setPos(Vector2(getPos().x + getVel().x, getPos().y + getVel().y));
}

void Projectile::attack(Vector2 d)
{
	dest = d;
	attacking = true;
}
