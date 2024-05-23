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
    void placeStation(float x, float y, sf::Color color);
    void setTrainMode(bool trainmode);
    std::vector<Cell*> getNeighbourHood(sf::Vector2f mousePos);
 

private:
    int rows, cols;
    float cellSize;
    std::vector<Cell> cells;
    std::vector<Cell> neighbourHood;
    std::vector<Rail> circuit;
    Cell* previousHoveredCell;
    int railMode;
    bool modeTrain;
    int idRail = 1;
    Cell* getCellAt(float x, float y);
    Rail* rail;
};
