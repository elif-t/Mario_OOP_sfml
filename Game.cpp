#include "Game.h"
#include "Object.h"


Game::Game()
{
    lifeTexture.loadFromFile("mariohead.png");
    brickTexture.loadFromFile("brick.png");
    pipesTexture.loadFromFile("pipes.png");
    floorTexture.loadFromFile("floor.png");
    pipeTexture.loadFromFile("pipe.png");

    // Initialize the bricks vector
    initializeVectors();
}

void Game::initializeVectors() 
{

    sf::Sprite floorSprite(floorTexture);
    floorSprite.setScale(scaleFactor, scaleFactor);

    sf::Sprite brickSprite(brickTexture);
    brickSprite.setScale(scaleFactor, scaleFactor);

    const int brickWidth = brickSprite.getGlobalBounds().width;
    const int brickHeight = brickSprite.getGlobalBounds().height;

    // Add the position and size of each brick to the bricks vector
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 12; j++) {
            sf::IntRect brickRect(j * brickWidth, i * brickHeight + (brick_start_height) * (i + 1), brickWidth, brickHeight);
            bricks.push_back(brickRect);
            sf::IntRect brickRect2(windowWidth - (j + 1) * brickWidth, i * brickHeight + (brick_start_height) * (i + 1), brickWidth, brickHeight);
            bricks.push_back(brickRect2);
        }
    }

    for (int i = 0; i < 4; i++) {
        sf::IntRect brickRect(i * brickWidth, brickHeight + (brick_start_height)+75, brickWidth, brickHeight);
        bricks.push_back(brickRect);
        sf::IntRect brickRect2(windowWidth - (i + 1) * brickWidth, brickHeight + 75 + (brick_start_height), brickWidth, brickHeight);
        bricks.push_back(brickRect2);
    }

    for (int i = 0; i < 16; i++) {
        sf::IntRect brickRect((9 * brickWidth) + (i * brickWidth), brickHeight + (brick_start_height)+(75 - brickWidth), brickWidth, brickHeight);
        bricks.push_back(brickRect);
    }

    //----------- pipes at the bottom  -----------//
    sf::Sprite pipe1Sprite(pipeTexture);
    sf::Sprite pipe2Sprite(pipeTexture);
    pipe1Sprite.setScale(-scaleFactor, scaleFactor);
    pipe2Sprite.setScale(scaleFactor, scaleFactor);
    // Set the position of the pipe sprites relative to the floor sprite
    
    cout << "pipes2 " << windowWidth - pipe2Sprite.getGlobalBounds().width << " " << brick_start_height - 5 * brickHeight << " " << pipe2Sprite.getGlobalBounds().width << " " << pipe2Sprite.getGlobalBounds().height << endl;

}

void Game::drawBackground(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    //---------- life -------------//
    sf::Sprite lifeSprite(lifeTexture);
    lifeSprite.setScale(scaleFactor, scaleFactor);
    for (int i = 0; i < 3; i++) {
        lifeSprite.setPosition(window.getSize().x - (lifeTexture.getSize().x * scaleFactor * (i + 1)) - 5 * (i + 1), 10);
        window.draw(lifeSprite);
    }

    //---------- brick ------------//
    sf::Sprite brickSprite(brickTexture);
    brickSprite.setScale(scaleFactor, scaleFactor);

    const int brickWidth = brickSprite.getGlobalBounds().width;
    const int brickHeight = brickSprite.getGlobalBounds().height;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 12; j++) {
            brickSprite.setPosition(j * brickWidth, i * brickHeight + (brick_start_height) * (i + 1));
            window.draw(brickSprite);
            brickSprite.setPosition(window.getSize().x - (j + 1) * brickWidth, i * brickHeight + (brick_start_height) * (i + 1));
            window.draw(brickSprite);
        }
    }

    for (int i = 0; i < 4; i++) {
        brickSprite.setPosition(i * brickWidth, brickHeight + (brick_start_height)+75);
        window.draw(brickSprite);
        brickSprite.setPosition(window.getSize().x - (i + 1) * brickWidth, brickHeight + 75 + (brick_start_height));
        window.draw(brickSprite);
    }

    for (int i = 0; i < 16; i++) {
        brickSprite.setPosition((9 * brickWidth) + (i * brickWidth), brickHeight + (brick_start_height)+(75 - brickWidth));
        window.draw(brickSprite);
    }

    //----------- pipes at the top  -----------//
    sf::Sprite pipes1Sprite(pipesTexture);
    sf::Sprite pipes2Sprite(pipesTexture);
    pipes1Sprite.setScale(scaleFactor, scaleFactor);
    pipes2Sprite.setScale(-scaleFactor, scaleFactor);

    pipes1Sprite.setPosition(0, brick_start_height - 5 * brickHeight);
    pipes2Sprite.setPosition(window.getSize().x, brick_start_height - 5 * brickHeight);

    window.draw(pipes1Sprite);
    window.draw(pipes2Sprite);

    // ----------- floor  -----------//
    sf::Sprite floorSprite(floorTexture);
    floorSprite.setScale(scaleFactor, scaleFactor);

    float xPosition = 0;
    float yPosition = window.getSize().y - floorSprite.getGlobalBounds().height;

    floorSprite.setPosition(xPosition, yPosition);
    window.draw(floorSprite);


    //-------- pipe at the bottom ----------//
    sf::Sprite pipe1Sprite(pipeTexture);
    sf::Sprite pipe2Sprite(pipeTexture);
    pipe1Sprite.setScale(-scaleFactor, scaleFactor);
    pipe2Sprite.setScale(scaleFactor, scaleFactor);
    // Set the position of the pipe sprites relative to the floor sprite
    pipe1Sprite.setPosition(pipeTexture.getSize().x * scaleFactor, floorSprite.getPosition().y - pipeTexture.getSize().y * scaleFactor);
    pipe2Sprite.setPosition(window.getSize().x - pipeTexture.getSize().x * scaleFactor, floorSprite.getPosition().y - pipeTexture.getSize().y * scaleFactor);
    window.draw(pipe1Sprite);
    window.draw(pipe2Sprite);


}

bool Game::onFloor(Object* obj)
{
    sf::IntRect objRect = obj->boundingBox();

    sf::Sprite floorSprite(floorTexture);
    floorSprite.setScale(scaleFactor, scaleFactor);

    float yPosition = windowHeight - floorSprite.getGlobalBounds().height;
    float height = floorSprite.getGlobalBounds().height;
    sf::IntRect floor = sf::IntRect(0, yPosition, windowWidth, height);

    if (objRect.intersects(floor)) {
        return true;
    }

    for (const auto& brickRect : bricks) {
        if (objRect.intersects(brickRect)) {
            return true;
        }
    }

    std::cout << "Floor bounding box: " << floor.left << ", " << floor.top << ", " << floor.width << ", " << floor.height << std::endl;

    return false;
}

bool Game::checkCollision(Turtle* t, Mario* m, int& side)
{
    return false;
}


