#include "Rail.h"
#include <iostream>

Rail::Rail(float x, float y, float size, bool direction) {
    this->direction = direction;
    shape.setSize(sf::Vector2f(size, size / 4)); 
    shape.setPosition(x, y + size / 2 - size / 8);
    shape.setFillColor(sf::Color::Red);
    if (direction == false) {
        shape.setRotation(0);
    }
    else {
        shape.setRotation(90);
    }
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
    if (direction) {
        shape.setRotation(90);
        shape.setPosition(shape.getPosition().x + shape.getSize().x/2 + shape.getSize().x/8, shape.getPosition().y - shape.getPosition().y/14);
    }
    else {
        shape.setRotation(0);
        shape.setPosition(shape.getPosition().x, shape.getPosition().y + (shape.getSize().y / 2 - shape.getSize().x / 8));
    }
}
bool Rail::getDirection() {
    return direction;
}

