#include "Turtle.h"
#include "Common.h"

static constexpr float GRAVITY = 0.5f;

Turtle::Turtle(sf::RenderWindow* window) : Object(window)
{
    loadTurtleTextures();
    sprite.setTexture(textures[7]);
    setPosition({ 100, 100 }); // Set initial position for Turtle (change the values as needed)
    sprite.setScale(0.5f, 0.5f); // Update the scale to face left
    heading = RIGHT;
}

void Turtle::loadTurtleTextures()
{
    for (int i = 1; i <= 5; ++i) {
        std::string filename = "turtle" + std::to_string(i) + ".png";
        loadTexture(filename, i + 6);
    }
}

void Turtle::setTexture(int textureIndex) {
    if (textureIndex >= 7 && textureIndex <= 9) {
        sprite.setTexture(textures[textureIndex]);
    }
}

void Turtle::move()
{
    // Set a constant speed for the turtle
    const float vx = 0.5f;
    vy += GRAVITY;
    sf::Vector2u turtleSize = textures[7].getSize();
    unsigned int width = turtleSize.x / 2;
    // If the turtle reaches the right limit, change its direction to left
    if (getPosition().x >= window->getSize().x - width && heading == RIGHT) {
        heading = LEFT;
        sprite.setScale(-0.5f, 0.5f); // Update the scale to face left
    }
    // If the turtle reaches the left limit, change its direction to right
    else if (getPosition().x <= 0 + width && heading == LEFT) {
        heading = RIGHT;
        sprite.setScale(0.5f, 0.5f); // Update the scale to face right
    }

    // Update the turtle's position based on its heading
    if (heading == RIGHT) {
        setPosition(getPosition() + sf::Vector2f(vx, 0));
    }
    else {
        setPosition(getPosition() - sf::Vector2f(vx, 0));
    }

    static int frameCounter = 0;
    static sf::Clock animationClock;

    if (animationClock.getElapsedTime().asMilliseconds() > 100) {
        frameCounter = (frameCounter + 1) % 3;
        sprite.setTexture(textures[7 + frameCounter]);
        animationClock.restart();
    }
}

void Turtle::fall()
{
    vy += GRAVITY;
}

void Turtle::jump(bool down)
{
}

void Turtle::updatePosition(Game* game)
{
    sf::Vector2f new_pos = pos;

    if (game->onFloor(this)) {
        vy = 0;
    }
    else {
        vy += GRAVITY;
    }

    new_pos.y += vy; // Calculate potential new position
    bool onBrick = false;

    sf::IntRect turtleRect(new_pos.x, new_pos.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    for (auto& brickRect : game->bricks) {
        if (turtleRect.intersects(brickRect)) {
            onBrick = true;
            new_pos.y = brickRect.top - sprite.getGlobalBounds().height;
            vy = 0;
            break;
        }
    }

    // Calculate potential new horizontal position based on its heading
    if (heading == RIGHT) {
        new_pos.x += vx;
    }
    else {
        new_pos.x -= vx;
    }

    for (const auto& pipeRect : game->bottomPipes) {
        if (turtleRect.intersects(pipeRect)) {
            if (heading == RIGHT) {
                heading = LEFT;
                new_pos.x -= vx;
            }
            else {
                heading = RIGHT;
                new_pos.x += vx;
            }
            break;
        }
    }

    const float vx = 0.5f;

    // After checks, finally update the turtle's position
    setPosition(new_pos);
    pos = new_pos;

}