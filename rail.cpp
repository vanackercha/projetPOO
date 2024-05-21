#include "Rail.h"

Rail::Rail(float x, float y, float size) {
    shape.setSize(sf::Vector2f(size, size / 4)); 
    shape.setPosition(x, y + size / 2 - size / 8);
    shape.setFillColor(sf::Color::Red);
}

void Rail::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
