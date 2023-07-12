#include "scoreBoard.h"

ScoreBoard::ScoreBoard()
{
    if (!font.loadFromFile("font.ttf")) {
        cout << "File could not be found!" << endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
}

void ScoreBoard::setScore(int score, sf::RenderWindow& window)
{
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "File could not be found!" << endl;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << score;
    std::string scoreStr = "Score: " + ss.str();

    scoreText.setString(scoreStr);

    // Draw the score text on the screen using the SFML window
    window.draw(scoreText);
}

void ScoreBoard::setLives(int lives)
{
}

int ScoreBoard::getLives()
{
    return 0;
}



