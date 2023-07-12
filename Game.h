#pragma once
#include "Common.h"
class Object;
class Mario;
class Turtle;

class Game
{
private:
	float scaleFactor = 0.5f;
	int brick_start_height = 165;
	sf::Texture lifeTexture;
	sf::Texture brickTexture;
	sf::Texture floorTexture;
	sf::Texture pipeTexture;
	sf::Texture pipesTexture;
public:
	void drawBackground(sf::RenderWindow& window);
	Game();
	void initializeVectors();
	bool onFloor(Object* obj);
	bool checkCollision(Turtle* t, Mario* m, int& side);
	std::vector<sf::IntRect> bricks;
	std::vector<sf::IntRect> bottomPipes;



};

