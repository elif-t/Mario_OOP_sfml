#include "Mario.h"

static constexpr float GRAVITY = 0.2f;

Mario::Mario(sf::RenderWindow* window) : Object(window)
{
    loadMarioTextures();
    sprite.setTexture(textures[0]);
    sprite.setScale(-0.5f, 0.5f);

    heading = RIGHT;
    vy = 0;
    setPosition({ 150, 404 });
    jumping = false;

}

void Mario::loadMarioTextures()
{
    for (int i = 1; i < 8; ++i) {
        std::string filename = "mario" + std::to_string(i) + ".png";
        loadTexture(filename, i - 1);
    }
}

void Mario::move()
{
    // Check if any movement keys are pressed
    bool movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool movingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    // Update texture and heading based on movement direction
    if ((movingUp && movingLeft) || (movingUp && movingRight)) {
        jump(false); // Call jump function with down set to false
    }
    else if (movingLeft) {
        sprite.setScale(0.5f, 0.5f);
        heading = LEFT;
        if (pos.x > 0) {
            pos.x -= 3.f;
        }
    }
    else if (movingRight) {
        sprite.setScale(-0.5f, 0.5f);
        heading = RIGHT;
        if (pos.x < window->getSize().x) {
            pos.x += 3.f;
        }
    }
    else if (movingUp) {
        // Jump
        jump(false); // Call jump function with down set to false
    }
    else {
        sprite.setTexture(textures[0]);
    }

    // Update texture for running animation
    if (movingLeft || movingRight) {
        int frame = (int)(pos.x / 10) % 3 + 1;
        sprite.setTexture(textures[frame]);
    }

    setPosition(pos);
}

void Mario::fall()
{
}

void Mario::jump(bool down)
{
    if (!down) {
        sprite.setTexture(textures[5]); // Set texture to mario6.png for jumping
        sprite.setScale((heading == RIGHT) ? -0.5f : 0.5f, 0.5f); // Flip the texture if mario is facing right
        vy = -3.f; // Set vertical velocity for jumping
        jumping = true;
    }
    else {
        // If user is pressing the down arrow key, make Mario fall faster
        vy += GRAVITY;
    }

    // Set horizontal velocity if user is pressing left or right arrow key while jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        vx = -3.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        vx = 3.f;
    }
}

void Mario::updatePosition(Game* game)
{
    pos.x += vx; // Update horizontal position
    pos.y += vy; // Update vertical position

    int roundedX = static_cast<int>(std::round(pos.x));
    int roundedY = static_cast<int>(std::round(pos.y));

    pos.x = static_cast<float>(roundedX);
    pos.y = static_cast<float>(roundedY);

    // Check if Mario is moving left or right while jumping
    if (jumping) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pos.x -= 3.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pos.x += 3.f;
        }
    }
    setPosition(pos);

    // Apply gravity
    if (!game->onFloor(this)) {
        vy += GRAVITY;
        setPosition(pos);
    }
    else {
        vy = 0;
        jumping = false;
    }
    vx = 0.f;

    sf::Vector2f new_pos = pos;
    new_pos.y += vy;
    sf::IntRect marioRect(new_pos.x, new_pos.y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    // Check for brick collision, make sure Mario doesn't fall through or jump up through bricks
    for (const auto& brickRect : game->bricks) {
        if (marioRect.intersects(brickRect)) {
            // If Mario is moving down (falling) and there's a brick below
            if (vy >= 0) {
                new_pos.y = brickRect.top - sprite.getGlobalBounds().height;
                vy = 0; // stop downward motion
                jumping = false; // Mario has landed on a brick
            }
            // If Mario is moving up (jumping) and there's a brick above
            else if (vy < 0) {
                new_pos.y = brickRect.top + brickRect.height; // position Mario below the brick
                vy = 0; // stop upward motion
            }
            break;
        }
    }

    for (const auto& pipeRect : game->bottomPipes) {
        if (marioRect.intersects(pipeRect)) {
            // If Mario is moving right and there's a pipe to the right
            if (vx > 0) {
                new_pos.x = pipeRect.left - sprite.getGlobalBounds().width;
                vx = 0; // stop horizontal motion
            }
            // If Mario is moving left and there's a pipe to the left
            else if (vx < 0) {
                new_pos.x = pipeRect.left + pipeRect.width; // position Mario to the right of the pipe
                vx = 0; // stop horizontal motion
            }
            break;
        }
    }

    // Gravity should only apply when Mario is not on a brick
    if (jumping) {
        vy += GRAVITY;
    }

    // Update Mario's position
    pos = new_pos;
    setPosition(pos);

    vx = 0.f;
}

