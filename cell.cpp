#include "Cell.h"

Cell::Cell(float x, float y, float size) : value(0), rail(nullptr) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Blue);
}

Cell::~Cell() {
    delete rail;
}

void Cell::draw(sf::RenderWindow& window) {
    window.draw(shape);
    if (rail) {
        rail->draw(window);
    }
}

void Cell::toggleValue() {
    value = (value == 1) ? 0 : 1;
    shape.setFillColor((value == 1) ? sf::Color::Green : sf::Color::Black);
}

void Cell::addRail() {
    if (value == 0 && !rail) {
        rail = new Rail(shape.getPosition().x, shape.getPosition().y, shape.getSize().x);
    }
}

void Cell::viewStatus(bool hover) {
    if (hover) {
        shape.setFillColor(sf::Color::Red);
    }
    else {
        shape.setFillColor((value == 1) ? sf::Color::Green : sf::Color::Black);
    }
}

bool Cell::contains(sf::Vector2f point) {
    return shape.getGlobalBounds().contains(point);
}

int Cell::getValue() const {
    return value;
}
