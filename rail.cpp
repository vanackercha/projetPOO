#include "Rail.h"

Rail::Rail(float x, float y, float size) {
    shape.setSize(sf::Vector2f(size, size / 4)); // Rail représenté comme un rectangle horizontal
    shape.setPosition(x, y + size / 2 - size / 8); // Centré verticalement dans la cellule
    shape.setFillColor(sf::Color::Red); // Couleur du rail
}

void Rail::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
