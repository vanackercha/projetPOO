#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell {
public:
    Cell(float x, float y, float size);

    void draw(sf::RenderWindow& window);
    void toggleValue();
    void viewStatus();
    bool contains(sf::Vector2f point);
    int getValue() const;

private:
    sf::RectangleShape shape;
    int value;
};

#endif
