#include "Object.h"
#include "Common.h"

void Object::loadTexture(const std::string& filename, int index) {
    if (!textures[index].loadFromFile(filename)) {
        std::cerr << "Error: Could not load texture from file: " << filename << std::endl;
    }
}

Object::Object(sf::RenderWindow* window) : window(window), state(0), heading(1)
{
    this->window = window;
}

void Object::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
    sprite.setPosition(pos);
}

sf::Vector2f Object::getPosition()
{
    return pos;
}

sf::IntRect Object::boundingBox(void)
{
    sf::IntRect rect(static_cast<int>(sprite.getGlobalBounds().left), 
        static_cast<int>(sprite.getGlobalBounds().top),
        static_cast<int>(sprite.getGlobalBounds().width),
        static_cast<int>(sprite.getGlobalBounds().height));

    cout << "left: " << rect.left << " top" << rect.top << " width " << rect.width << " height" << rect.height << endl;

    return rect;
}

void Object::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}