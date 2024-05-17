#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>
#include <SFML/Graphics.hpp>

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
    Cell* previousHoveredCell;
};

#endif // GRID_H
