#include "Player.h"

#include <vector>
#include <sfwdraw.h>

#include "AssetLib.h"
#include "Defines.h"
#include "GameState.h"
#include "Projectile.h"

// Set our static bool loaded to false by default. Used in detecting if we've loaded textures yet.
bool Player::loaded = false;

// Set our starter values. If it's our first game then load the textures.
Player::Player()
{
	setPos(Vector2(0, 0));
	setDim(Vector2(32, 36));
	setDirection(S);
	setState(Idle);

	accRate = 100;
	maxSpeed = 4;
	decRate = 50;
	attackTimer = 0;

	invulnerabilityTimer = 0.4f;
	deathTimer = 2.5f;
	currentInvulnerabilityTimer = 0;
	currentDeathTimer = 0;

	tookDamage = false;
	dead = false;

	setMaxHealth(100);
	setHealth(40);
	setArmor(2);
	setDamage(10);

	setKillCount(0);

	setExperience(0);
	setLevel(1);

	healthTex = "hp";

	setSpriteName("Player");
	setCurrentAnimation("IdleSouth");

	if (!loaded)
	{
		loadTexture(getSpriteName(), "../textures/player.png", 6, 4);

		loadTexture(healthTex, "../textures/health.png", 1, 1);

		addAnimation(getSpriteName(), getCurrentAnimation(), std::vector<unsigned>{13});
		addAnimation(getSpriteName(), "WalkSouth", std::vector<unsigned>{12, 13, 14, 13});
		addAnimation(getSpriteName(), "AttackSouth", std::vector<unsigned>{15, 16, 17, 16, 15});

		addAnimation(getSpriteName(), "IdleNorth", std::vector<unsigned>{1});
		addAnimation(getSpriteName(), "WalkNorth", std::vector<unsigned>{0, 1, 2, 1});
		addAnimation(getSpriteName(), "AttackNorth", std::vector<unsigned>{3, 4, 5, 4, 3});

		addAnimation(getSpriteName(), "IdleEast", std::vector<unsigned>{7});
		addAnimation(getSpriteName(), "WalkEast", std::vector<unsigned>{6, 7, 8, 7});
		addAnimation(getSpriteName(), "AttackEast", std::vector<unsigned>{9, 10, 11, 10, 9});

		addAnimation(getSpriteName(), "IdleWest", std::vector<unsigned>{19});
		addAnimation(getSpriteName(), "WalkWest", std::vector<unsigned>{18, 19, 20, 19});
		addAnimation(getSpriteName(), "AttackWest", std::vector<unsigned>{21, 22, 23, 22, 21});
	}
}

#pragma region GettersAndSetters

// Our getters
PState Player::getState()
{
	return stateInfo;
}

PDirection Player::getDirection()
{
	return dir;
}

int Player::getMaxHealth()
{
	return maxHealth;
}

int Player::getHealth()
{
	return health;
}

int Player::getArmor()
{
	return armor;
}

int Player::getDamage()
{
	return damage;
}

int Player::getExperience()
{
	return experience;
}

int Player::getLevel()
{
	return level;
}

int Player::getKillCount()
{
	return killCount;
}

// Our setters
void Player::setState(PState s)
{
	stateInfo = s;
}

void Player::setDirection(PDirection d)
{
	dir = d;
}

void Player::setMaxHealth(int h)
{
	maxHealth = h;
}

void Player::setHealth(int h)
{
	health = h;
}

void Player::setArmor(int a)
{
	armor = a;
}

void Player::setDamage(int d)
{
	damage = d;
}

void Player::setExperience(int e)
{
	experience = e;
}

void Player::setLevel(int l)
{
	level = l;
}

void Player::setKillCount(int i)
{
	killCount = i;
}

#pragma endregion


void Player::incrementScore()
{
	killCount++;
}

// Update our animation, check for input, move and allow attacking.
// Check if we're supposed to be invulnerable.
void Player::update()
{
	GameObject::update();

	Input();

	Move(getAcc());

	Animate();

	DeathCheck();

	if (getState() == Attacking) Attack();

	if (tookDamage)
		if (currentInvulnerabilityTimer < sfw::getTime()) tookDamage = false;
}

// Check controller/keyboard input and move/attack accordingly
void Player::Input()
{
	setAcc(Vector2(0, 0));

	if (health > 0 && getState() != Attacking)
	{

		if		(BUTTON_UP)
		{
			setAcc(Vector2(getAcc().x, accRate));
		}

		else if (BUTTON_DOWN)
		{
			setAcc(Vector2(getAcc().x, -accRate));
		}

		if		(BUTTON_LEFT)
		{
			setAcc(Vector2(-accRate, getAcc().y));
		}

		else if (BUTTON_RIGHT)
		{
			setAcc(Vector2(accRate ,getAcc().y));
		}


		if (BUTTON_TWO)
			setState(Attacking);
	}
}

// If we aren't attacking set acceleration to velocity and velocity to position
void Player::Move(Vector2 inputAxis)
{
	if (getState() != Attacking)
	{
		setVel(Vector2(getVel().x + (inputAxis.x * sfw::getDeltaTime()), getVel().y + (inputAxis.y * sfw::getDeltaTime())));

		applyMaxSpeed();
	}

	applyDeceleration();

	setPos(Vector2(getPos().x + getVel().x, getPos().y + getVel().y));
}

// Start our attack animation
void Player::Attack()
{
	attackTimer += sfw::getDeltaTime();

	if (attackTimer > getAnimationDuration(getSpriteName(), getCurrentAnimation()))
	{
		setState(Idle);
		attackTimer = 0;
	}

	//for (int i = 0; i < FLAME_COUNT; ++i)
	//	game()->flames[i].setVel(Vector2(game()->flames[i].getVel().x, game()->flames[i].getVel().y));

	switch (dir)
	{
	case N:
		for (int i = 0; i < FLAME_COUNT; ++i)
			game()->flames[i].attack(Vector2(getPos().x - 16, getPos().y + 30));
		break;
	case E:
		for (int i = 0; i < FLAME_COUNT; ++i)
			game()->flames[i].attack(Vector2(getPos().x + 30, getPos().y - 16));
		break;
	case S:
		for (int i = 0; i < FLAME_COUNT; ++i)
			game()->flames[i].attack(Vector2(getPos().x - 16, getPos().y - 70));
		break;
	case W:
		for (int i = 0; i < FLAME_COUNT; ++i)
			game()->flames[i].attack(Vector2(getPos().x - 70, getPos().y - 16));
		break;
	default:
		break;
	}
}

void Player::takeDamage(int d)
{
	if (!tookDamage && health > 0)
	{
		health -= (d / armor);
		tookDamage = true;
		currentInvulnerabilityTimer = invulnerabilityTimer + sfw::getTime();
	}
	if (health < 0)
		health = 0;
}

void Player::DeathCheck()
{
	if (health < 1)
	{
		if (!dead)
		{
			dead = true;
			currentDeathTimer = deathTimer + sfw::getTime();
		}

		if (currentDeathTimer < sfw::getTime())
			game()->setGameState(GameOverScreen);
	}
}

// Check which animation frame we should be on
void Player::Animate()
{
	if		(getVel().x > 0) setDirection(E);
	else if (getVel().x < 0) setDirection(W);
	else if (getVel().y > 0) setDirection(N);
	else if (getVel().y < 0) setDirection(S);

	if (getState() != Attacking && getState() != Walk)	
		if (getVel().x != 0 || getVel().y != 0) setState(Walk);

	if (getState() != Attacking && getState() != Idle)
		if (getVel().x == 0 && getVel().y == 0) setState(Idle);

	switch (getDirection())
	{
	case N:

		switch (getState())
		{
		case Idle:
			setCurrentAnimation("IdleNorth");
			break;
		case Walk:
			setCurrentAnimation("WalkNorth");
			break;
		case Attacking:
			setCurrentAnimation("AttackNorth");
			break;
		case Dead:
			break;
		default:
			break;
		}

		break;
	case E:

		switch (getState())
		{
		case Idle:
			setCurrentAnimation("IdleEast");
			break;
		case Walk:
			setCurrentAnimation("WalkEast");
			break;
		case Attacking:
			setCurrentAnimation("AttackEast");
			break;
		case Dead:
			break;
		default:
			break;
		}

		break;
	case S:

		switch (getState())
		{
		case Idle:
			setCurrentAnimation("IdleSouth");
			break;
		case Walk:
			setCurrentAnimation("WalkSouth");
			break;
		case Attacking:
			setCurrentAnimation("AttackSouth");
			break;
		case Dead:
			break;
		default:
			break;
		}

		break;
	case W:

		switch (getState())
		{
		case Idle:
			setCurrentAnimation("IdleWest");
			break;
		case Walk:
			setCurrentAnimation("WalkWest");
			break;
		case Attacking:
			setCurrentAnimation("AttackWest");
			break;
		case Dead:
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
	
}

// Draw our character and tint it blue to simulate darkness
void Player::draw()
{
	if (health > 0)
	{
		if (!tookDamage)
			RENDER(getTexture(getSpriteName()), getPos().x - game()->camOffset.x, getPos().y - game()->camOffset.y,
				getDim().x, getDim().y, 0, true, getCurrentFrame(), 0x005aaeff);
		else
			RENDER(getTexture(getSpriteName()), getPos().x - game()->camOffset.x, getPos().y - game()->camOffset.y,
				getDim().x, getDim().y, 0, true, getCurrentFrame(), 0xff5050ff);
	}
	else
		RENDER(getTexture(getSpriteName()), getPos().x - game()->camOffset.x, getPos().y - game()->camOffset.y,
			getDim().x, -getDim().y, 0, true, getCurrentFrame(), 0xff5050ff);

	RENDER(getTexture(healthTex), 20, 20, health, 10, 0, 0);
}
