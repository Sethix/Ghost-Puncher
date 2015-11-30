#pragma once


#include <string>


struct Vector2 { Vector2(); Vector2(float a, float b); float x, y; };

class Game;


class GameObject
{
private:
	
	// Our movement variables
	Vector2 pos;
	
	Vector2 acc;
	
	Vector2 vel;

	Vector2 dim;
	
	std::string sprite;

	std::string animationName;

	float angle;

	unsigned currentFrame;

	float animTimer;


public:

	static Game *&game();					// Used to access gamestate info

	float accRate;							// The speed at which we accelerate

	float decRate;							// The speed at which we slow down

	float maxSpeed;						    // The speed at which we cap out at

#pragma region GettersAndSetters

	// Our getters
	Vector2 getPos();
	
	Vector2 getAcc();
	
	Vector2 getVel();

	Vector2 getDim();

	Vector2 getTopLeft();

	Vector2 getTopRight();

	Vector2 getBottomLeft();

	Vector2 getBottomRight();

	std::string getSpriteName();

	std::string getCurrentAnimation();

	unsigned getCurrentFrame();
		
	// Our setters
	void setPos(Vector2 p);
	
	void setAcc(Vector2 a);
	
	void setVel(Vector2 v);

	void setDim(Vector2 d);
	
	void setSpriteName(std::string t);

	void setCurrentAnimation(std::string a);

	void setCurrentFrame(unsigned frame);

#pragma endregion


	void applyDeceleration();				// Apply our acceleration

	void applyMaxSpeed();					// Cap our speed

	bool CollisionCheck(GameObject obj);	// Check for colliding objects

	void boundsCheck(Vector2 n, Vector2 p); // Check if we're in the levels bounds

	virtual void update();					// Update animations

	virtual void draw();					// Draw object
};