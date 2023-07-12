#pragma once
#include "Common.h"

class ScoreBoard {
private:
    string score;   // Current score
    int lives;      // Remaining life count for Mario
    sf::Text scoreText;
    sf::Font font;
public:
    void setScore(int score, sf::RenderWindow& window);
    void setLives(int lives);
    int getLives();
    ScoreBoard();
};


    

    


