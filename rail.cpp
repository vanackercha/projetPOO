#include "Rail.h"
#include <iostream>

Rail::Rail(float x, float y, float size) {
    shape.setSize(sf::Vector2f(size, size / 4)); 
    shape.setPosition(x, y + size / 2 - size / 8);
    shape.setFillColor(sf::Color::Red);
}
void Rail::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Rail::setId(int id) {
    this->idRail = id;
}
int Rail::getId() {
    return this->idRail;
}

void Rail::setDirection(bool dir) {
    this->direction = dir;
}
bool Rail::getDirection() {
    return direction;
}

