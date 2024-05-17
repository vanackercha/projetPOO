#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Grid {
public:
    Grid(int rows, int cols, float cellSize);

    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);
    void handleHover(sf::Vector2f mousePos);

private:
    int rows, cols;
    float cellSize;
    std::vector<Cell> cells;
};

#endif // GRID_H
