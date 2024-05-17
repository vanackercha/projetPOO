#pragma once
#include <SFML/Graphics.hpp>
class Station {
private:
    sf::RectangleShape shape[3][3];
public:
    Station(float x, float y, float cellSize);
    void draw(sf::RenderWindow& window);
};

