#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Station.h"

class Grid {
public:
    Grid(int rows, int cols, float cellSize);
    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);
    void handleHover(sf::Vector2f mousePos);
    void setRailMode(int mode);
    void placeStation(float x, float y);
    std::vector<Cell*> getNeighbourHood(sf::Vector2f mousePos);

private:
    int rows, cols;
    float cellSize;
    std::vector<Cell> cells;
    std::vector<Station> stations;
    std::vector<Cell> neighbourHood;
    Cell* previousHoveredCell;
    int railMode;
    Cell* getCellAt(float x, float y);
};
