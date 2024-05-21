#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "Rail.h"

class Cell {
public:
    Cell(float x, float y, float size);
    ~Cell();
    void draw(sf::RenderWindow& window);
    void toggleValue();
    void addRail();
    void viewStatus(bool hover);
    bool contains(sf::Vector2f point);
    void setValue(int value);
    int getValue() const;
    bool hasRail() const;

private:
    sf::RectangleShape shape;
    int value;
    Rail* rail; // Pointeur brut vers un rail
};

#endif