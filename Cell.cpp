#include "Cell.h"

Cell::Cell(float x, float y, float size) : value(0) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::Blue);
}

void Cell::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Cell::toggleValue() {
    value = (value == 1) ? 0 : 1;
    shape.setFillColor((value == 1) ? sf::Color::Green : sf::Color::Black);
}

void Cell::viewStatus() {
    if (value == 1) {
        shape.setFillColor(sf::Color::Red);
    }
    else {
        shape.setFillColor(sf::Color::Green);
    }
}

bool Cell::contains(sf::Vector2f point) {
    return shape.getGlobalBounds().contains(point);
}

int Cell::getValue() const {
    return value;
}
