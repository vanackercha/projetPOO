#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include "Station.h";
#include <vector>
#include <SFML/Graphics.hpp>


class Grid {
public:
    Grid(int rows, int cols, float cellSize);
    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);
    void handleHover(sf::Vector2f mousePos);
    void placeStation(float x, float y);

private:
    int rows, cols;
    float cellSize;
    std::vector<Cell> cells;
    std::vector<Station> stations;
    Cell* previousHoveredCell;
    Cell* getCellAt(float x, float y);

};

#endif // GRID_H
