#include <sfwdraw.h>

#include "Defines.h"
#include "AssetLib.h"
#include "GameState.h"
#include "GameObject.h"


// Our Vec2 constructor. We want to start all Vec2's at 0,0
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

// We should also be allowed to create a vector 2 with two floats.
Vector2::Vector2(float a, float b)
{
	x = a;
	y = b;
}

// We set up a static instance of GameState so that we may access the gamestate after it's initialized.
Game *& GameObject::game()
{
	static Game *gs;
	return gs;
}

#pragma region GettersAndSetters

// Our getters
Vector2 GameObject::getPos()
{
	return pos;
}

Vector2 GameObject::getAcc()
{
	return acc;
}

Vector2 GameObject::getVel()
{
	return vel;
}

Vector2 GameObject::getDim()
{
	return dim;
}

Vector2 GameObject::getTopLeft()
{
	return Vector2(pos.x - (dim.x / 2), pos.y - (dim.y / 2));
}

Vector2 GameObject::getTopRight()
{
	return Vector2(pos.x + (dim.x / 2), pos.y - (dim.y / 2));
}

Vector2 GameObject::getBottomLeft()
{
	return Vector2(pos.x - (dim.x / 2), pos.y + (dim.y / 2));
}

Vector2 GameObject::getBottomRight()
{
	return Vector2(pos.x + (dim.x / 2), pos.y + (dim.y / 2));
}

std::string GameObject::getSpriteName()
{
	return sprite;
}

std::string GameObject::getCurrentAnimation()
{
	return animationName;
}

unsigned GameObject::getCurrentFrame()
{
	return currentFrame;
}

// Our setters
void GameObject::setPos(Vector2 p)
{
	pos = p;
}

void GameObject::setAcc(Vector2 a)
{
	acc = a;
}

void GameObject::setVel(Vector2 v)
{
	vel = v;
}

void GameObject::setDim(Vector2 d)
{
	dim = d;
}

void GameObject::setSpriteName(std::string t)
{
	sprite = t;
}

void GameObject::setCurrentAnimation(std::string a)
{
	animationName = a;
}

void GameObject::setCurrentFrame(unsigned frame)
{
	currentFrame = frame;
}

#pragma endregion

// Check if we aren't accelerating. If we aren't, check our velocity.
// If our velocity is positive, apply negative deceleration and vice versa.
// If we're moving slow enough then come to a complete halt so we don't keep
// shifting between moving forward and backward.
void GameObject::applyDeceleration()
{
	if (getAcc().x == 0)
	{

		if (getVel().x > 0)
		{

			if (getVel().x < 1)
				setVel(Vector2(0, getVel().y));

			else
				setVel(Vector2(getVel().x - (decRate * sfw::getDeltaTime()), getVel().y));
		}

		if (getVel().x < 0)
		{

			if (getVel().x > -1)
				setVel(Vector2(0, getVel().y));

			else
				setVel(Vector2(getVel().x + (decRate * sfw::getDeltaTime()), getVel().y));
		}
	}

	if (getAcc().y == 0)
	{
		if (getVel().y > 0)
		{

			if (getVel().y < 1)
				setVel(Vector2(getVel().x, 0));

			else
				setVel(Vector2(getVel().x, getVel().y - (decRate * sfw::getDeltaTime())));
		}

		if (getVel().y < 0)
		{

			if (getVel().y > -1)
				setVel(Vector2(getVel().x, 0));

			else
				setVel(Vector2(getVel().x, getVel().y + (decRate * sfw::getDeltaTime())));
		}
	}
}

// Check our velocity against our max speed. If it's over then set it to max.
void GameObject::applyMaxSpeed()
{
	if		(getVel().x >  maxSpeed)	setVel(Vector2( maxSpeed, getVel().y));
	else if (getVel().x < -maxSpeed)	setVel(Vector2(-maxSpeed, getVel().y));
	if		(getVel().y >  maxSpeed)	setVel(Vector2(getVel().x,  maxSpeed));
	else if (getVel().y < -maxSpeed)	setVel(Vector2(getVel().x, -maxSpeed));
}

// Check our position and dimensions against another object. If it overlaps return true.
bool GameObject::CollisionCheck(GameObject obj)
{
	if (getPos().x - (getDim().x / 2) < obj.getPos().x + (obj.getDim().x / 2) &&
		getPos().x + (getDim().x / 2) > obj.getPos().x - (obj.getDim().x / 2) &&
		getPos().y - (getDim().y / 2) < obj.getPos().y + (obj.getDim().y / 2) &&
		getPos().y + (getDim().y / 2) > obj.getPos().y - (obj.getDim().y / 2))   return true;

	else return false;
}

// Check if we're inside the level. If we aren't then put us back in.
void GameObject::boundsCheck(Vector2 n, Vector2 p)
{
	if (pos.x < n.x) pos.x = n.x + 1;
	if (pos.x > p.x) pos.x = p.x - 1;
	if (pos.y < n.y) pos.y = n.y + 1;
	if (pos.y > p.y) pos.y = p.y - 1;
}

// Update our animation state.
void GameObject::update()
{
	animTimer += sfw::getDeltaTime();

	currentFrame = sampleAnimation(sprite, animationName, animTimer);

	if (animTimer > getAnimationDuration(sprite, animationName))
		animTimer = 0;
}

// Simple SFW draw call. No animation support, override the function where needed.
void GameObject::draw()
{
	RENDER(getTexture(getSpriteName()), getPos().x - game()->camOffset.x, getPos().y - game()->camOffset.y,
		getDim().x, getDim().y, 0, true, 0);
}
