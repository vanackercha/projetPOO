#include "Tile.h"

Tile::Tile(int x, int y, int size) : defaultColor(sf::Color::White) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x * size, y * size);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
    shape.setFillColor(defaultColor);
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Tile::setColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void Tile::resetColor() {
    shape.setFillColor(defaultColor);
}
