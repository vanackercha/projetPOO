#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Rail.h"

class Cell {
public:
    Cell(float x, float y, float size);
    void draw(sf::RenderWindow& window);
    void toggleValue();
    void addRail();
    void viewStatus(bool hover);
    bool contains(sf::Vector2f point);
    int getValue() const;

private:
    sf::RectangleShape shape;
    int value;
    std::unique_ptr<Rail> rail; // Pointeur unique vers un rail
};

#endif // CELL_H
