#include "Grid.h"
#include <iostream>


Grid::Grid(int rows, int cols, float cellSize) : rows(rows), cols(cols), cellSize(cellSize), previousHoveredCell(nullptr), railMode(false) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells.emplace_back(j * cellSize, i * cellSize, cellSize);
        }
    }
}

void Grid::draw(sf::RenderWindow& window) {
    for (auto& cell : cells) {
        cell.draw(window);
    }
    for (auto& station : stations) {
        station.draw(window);
    }
}

void Grid::handleClick(sf::Vector2f mousePos) {
    for (auto& cell : cells) {
        if (cell.contains(mousePos)) {
             if (railMode == 1 && cell.getValue() == 0) {
                
                 std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                 if ((adjacentCells[1]->getValue() == 2) 
                     || ((adjacentCells[1]->getValue() == 1))
                     || (adjacentCells[2]->getValue() == 2)
                     || (adjacentCells[2]->getValue() == 1)) {


                     cell.addRail();
                 }
                 std::cout << adjacentCells[1]->getValue() << std::endl;
                 
            }
             if (railMode == 2 && cell.getValue() == 0) {

                 std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                 if ((adjacentCells[3]->getValue() == 2)
                     || ((adjacentCells[3]->getValue() == 1))
                     || (adjacentCells[4]->getValue() == 2)
                     || (adjacentCells[4]->getValue() == 1)) {


                     cell.addRail();
                 }
                 std::cout << adjacentCells[1]->getValue() << std::endl;

             }
            std::cout << "(" << (mousePos.x / cellSize) << ", " << mousePos.y / cellSize << ") Value: " << cell.getValue() << std::endl;
            break;
        }
    }
}

void Grid::handleHover(sf::Vector2f mousePos) {
    Cell* hoveredCell = nullptr;
    for (auto& cell : cells) {
        if (cell.contains(mousePos)) {
            hoveredCell = &cell;
            break;
        }
    }

    if (previousHoveredCell && previousHoveredCell != hoveredCell) {
        previousHoveredCell->viewStatus(false);
    }

    if (hoveredCell) {
        hoveredCell->viewStatus(true);
    }

    previousHoveredCell = hoveredCell;
}

void Grid::setRailMode(int mode) {
    railMode = mode;
}
void Grid::placeStation(float x, float y) {
    stations.emplace_back(x, y, cellSize);

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            Cell* cell = getCellAt(x + j * cellSize, y + i * cellSize);
            if (cell) {
                cell->setValue(2);
            }
        }
    }
}
std::vector<Cell*> Grid::getNeighbourHood(sf::Vector2f mousePos) {
    std::vector<Cell*> neighbourhood;

    Cell* cell0 = getCellAt(mousePos.x, mousePos.y);
    if (cell0) neighbourhood.push_back(cell0);

    Cell* cell1 = getCellAt(mousePos.x - cellSize, mousePos.y);
    if (cell1) neighbourhood.push_back(cell1);

    Cell* cell2 = getCellAt(mousePos.x + cellSize, mousePos.y);
    if (cell2) neighbourhood.push_back(cell2);

    Cell* cell3 = getCellAt(mousePos.x, mousePos.y - cellSize);
    if (cell3) neighbourhood.push_back(cell3);

    Cell* cell4 = getCellAt(mousePos.x, mousePos.y + cellSize);
    if (cell4) neighbourhood.push_back(cell4);

    return neighbourhood;
}
Cell* Grid::getCellAt(float x, float y) {
    for (auto& cell : cells) {
        if (cell.contains(sf::Vector2f(x, y))) {
            return &cell;
        }
    }
    return nullptr;
}
