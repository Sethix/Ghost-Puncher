#pragma once


#include "GameObject.h"


class Projectile : public GameObject
{
private:

	Projectile(int d, Vector2 p, Vector2 v);

	float attackSpeed;

	int damage;

	Vector2 dest;

	bool attacking;

	bool timerSet;

	float attackTimer;

	float currentAttackTimer;

public:

	static bool loaded;

	Projectile();

#pragma region GettersAndSetters

	int getDamage();

	void setDamage(int d);

#pragma endregion

	void Move();

	void attack(Vector2 d);

};