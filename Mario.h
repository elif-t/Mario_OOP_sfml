#pragma once
#include "Common.h"
#include "Object.h"

class Mario : public Object
{
private:
	void loadMarioTextures();
	float vy = 0.0f;
	float vx = 0.0f;
	bool onFloor;
public:
	Mario(sf::RenderWindow* window);    //Constructor
	void move();                        //Moves Mario left or right
	void jump(bool down);               //Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps up)
	void fall();                    //Makes Mario fall straight down when he dies
	static const int RIGHT = 0;
	static const int LEFT = 1;
	void updatePosition(Game* game);
	bool jumping;
	
};

