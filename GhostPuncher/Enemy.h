#pragma once


#include "GameObject.h"


class Enemy : public GameObject
{
private:

	int health;							 // Used to know when to die.

	int previousHealth;					 // Used to check when the enemy first dies.

	int armor;							 // Used for player damage mitigation.

	int damage;							 // How much damage we do.


public:

	static bool loaded;					 // Used to detect if we still need to load our textures

	Enemy();

#pragma region GettersAndSetters

	// Our getters
	int getHealth();

	int getArmor();

	int getDamage();


	// Our setters
	void setHealth(int h);

	void setArmor(int a);

	void setDamage(int d);

#pragma endregion


	bool scoreCheck();					 // Check if we need to give points.
	
	void Track();						 // Used to move towards the player.
	 
	void takeDamage(int d);				 // Lower the current health of the enemy.
};