#include "Station.h"

Station::Station(float x, float y, float cellSize) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            shape[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            shape[i][j].setPosition(x + j * cellSize, y + i * cellSize);
            shape[i][j].setFillColor(sf::Color(128, 128, 128));
            shape[i][j].setOutlineThickness(1);
            shape[i][j].setOutlineColor(sf::Color::Black);
        }
    }
}

void Station::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            window.draw(shape[i][j]);
        }
    }
}
