#pragma once


#include <string>

#include "Defines.h"
#include "GameObject.h"


// This enum will be used for animations and knowing which direction to attack.
enum PDirection 
{
	N = 0,
	E = 1,
	S = 2,
	W = 3
};

// This enum will be used for animations.
enum PState
{
	Idle = 0,
	Walk = 1,
	Attacking = 2,
	Dead = 3
};

// This struct will contain all the variables and functions related to our player.
class Player : public GameObject
{
private:

	PState stateInfo;					// Used for animation.

	PDirection dir;						// Used for animation and attacking.

	Vector2 attackDestination;

	std::string healthTex;

	int maxHealth;

	int health;							// Used to know when the game is over.

	int armor;							// Used for enemy damage mitigation.

	int damage;							// How much damage we do.

	int experience;						// How much EXP til we level.

	int level;							// Our correct level. Level will dictate max HP and damage.

	int killCount;						// How many enemies we've killed. Used for score.

	float attackTimer;					// How long our projectiles should try to reach the destination.

	float deathTimer;					// How long the screen should linger after we die.

	float currentDeathTimer;			// Time of death + Death timer

	bool dead;							// Are we dead?

	bool tookDamage;					// Have we taken damage? Used in determining invinciblity frames.

	float invulnerabilityTimer;			// How long to remain invulnerable after being hit.

	float currentInvulnerabilityTimer;  // Time we were hit + Invuln timer


public:

	static bool loaded;					// Have we loaded our textures yet?

	Player();

#pragma region GettersAndSetters

	// Our getters
	PState getState();

	PDirection getDirection();
	
	int getMaxHealth();

	int getHealth();
	
	int getArmor();
	
	int getDamage();
	
	int getExperience();
	
	int getLevel();

	int getKillCount();
	
	
	// Our setters
	void setState(PState s);

	void setDirection(PDirection d);
	
	void setMaxHealth(int h);

	void setHealth(int h);
	
	void setArmor(int a);
	
	void setDamage(int d);
	
	void setExperience(int e);
	
	void setLevel(int l);

	void setKillCount(int i);

#pragma endregion


	void incrementScore();				// Increase score by one.

	virtual void update();
	
	void Input();						// Used to detect input so we know when to attack and move.

	void Move(Vector2 inputAxis);		// Used to move player according to input.

	void Attack();						// Used to attack according to input.

	void DeathCheck();					// Check if our health has dropped to or below 0.

	void takeDamage(int d);				// Reduce our health.

	void Animate();						// Apply our animations.

	virtual void draw();
};