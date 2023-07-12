#pragma once
#include "Common.h"

class Object
{
protected:
	sf::Texture textures[12];	//Textures of Object
	sf::Sprite sprite;
	sf::RenderWindow* window;	//Pointer to render window
	int state;					//current animation state of the object
	int heading;				//facing direction of object
	sf::Vector2f pos;			//Current position of object on screen
	float scaleFactor = 0.5;
	void loadTexture(const std::string& filename, int index);
public:
	Object(sf::RenderWindow* window);     //Constructor
	void setPosition(sf::Vector2f pos);   //Sets position of the object
	sf::Vector2f getPosition();           //Gets position of the object
	sf::IntRect boundingBox(void);        //Returns the bounding rectangle of the object texture
	void draw(sf::RenderWindow& window);  //Draws current the object texture to screen
	virtual void move(void) = 0;                      //Abstract method that will be overridden
	virtual void fall(void) = 0;                      //Abstract method that will be overridden
	virtual void jump(bool down) = 0;                 //Abstract method that will be overridden

};
