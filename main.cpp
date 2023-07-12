#include "Common.h"
#include "Game.h"
#include "Mario.h"
#include "Turtle.h"
#include "Object.h"
#include "ScoreBoard.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Super Mario!");
    window.setFramerateLimit(100);
    window.setVerticalSyncEnabled(true);

    Game game;
    Mario mario(&window);
    Turtle turtle(&window);
    ScoreBoard scoreBoard;
    std::map<Turtle*, std::pair<int, sf::Clock>> turtleFrames;

    // Load the "start screen" image from a file 
    sf::Texture textureStart;
    if (!textureStart.loadFromFile("super_mario_start.png")) {
        // handle error loading the image
        cout << "File could not be found!" << endl;
    }
    // Create a sprite for the start screen image
    sf::Sprite spriteStart(textureStart);
    // Resize the start sprite to fit the upper half of the window
    sf::Vector2u windowSize = window.getSize();
    float scale = static_cast<float>(windowSize.x) / textureStart.getSize().x;
    spriteStart.setScale(scale, scale);
    spriteStart.setPosition(0, 0);

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        cout << "File could not be found!" << endl;
    }
    sf::Text startText("Start the game", font, 40); // Create a text object
    startText.setPosition((window.getSize().x - startText.getLocalBounds().width) / 2, (window.getSize().y - startText.getLocalBounds().height) / 1.75); // Set the position of the text


    bool gameStarted = false;

    sf::Clock turtleSpawnClock;
    int turtleNum = 0;
    std::vector<Turtle*> turtles;
    int score = 0;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //cehck if the player has pressed the enter key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                gameStarted = true;
            }
        }

        if (gameStarted) {
            game.drawBackground(window);

            mario.move();
            mario.draw(window);
            mario.updatePosition(&game);

            if (turtleNum < 5 && turtleSpawnClock.getElapsedTime().asSeconds() >= 5) {
                Turtle* newTurtle = new Turtle(&window);
                newTurtle->setPosition({ 100,100 });
                turtles.push_back(newTurtle);
                turtleNum++;
                turtleSpawnClock.restart();
            }

            for (auto& turtle : turtles) {
                // Get the frame and clock for this turtle
                auto& frameClockPair = turtleFrames[turtle];
                int& frameCounter = frameClockPair.first;
                sf::Clock& animationClock = frameClockPair.second;

                // Update the turtle animation
                if (animationClock.getElapsedTime().asMilliseconds() > 100) {
                    frameCounter = (frameCounter + 1) % 3;
                    turtle->setTexture(frameCounter + 7);
                    animationClock.restart();
                }

                // Update the turtle position and movement
                turtle->updatePosition(&game);
                turtle->move();
                turtle->draw(window);
            }

            //turtle.move();
            //turtle.draw(window);
            //turtle.updatePosition(&game);
            scoreBoard.setScore(score, window);

            window.display();
        }
        else {
            window.clear();

            window.draw(spriteStart);
            window.draw(startText);
            window.display();
        }
        
    }

    return 0;
}
