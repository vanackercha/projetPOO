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
}

void Grid::handleClick(sf::Vector2f mousePos) {
    for (auto& cell : cells) {
        if (cell.contains(mousePos)) {
            /*std::cout << modeTrain << std::endl;
             if (cell.hasRail()) {
                cell.getRailFromCell();
            }
            else if (cell.hasStation()) {
                cell.getStationFromCell();
            }
             else if (railMode == 1 && cell.getValue() == 0) {
            }*/
             if (railMode == 1 && cell.getValue() == 0) {
                 std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                 if ((adjacentCells[1]->getValue() == 2) || (adjacentCells[2]->getValue() == 2)) {
                     std::vector<Rail> vector;
                     idRail++;
                     cell.addRail(idRail, 0);
                     
                 }
                 else if ((adjacentCells[1]->getValue() == 1) || (adjacentCells[2]->getValue() == 1)) {
                     idRail++;
                     cell.addRail(idRail, 0);
                 }
                 //std::cout << adjacentCells[1]->getValue() << std::endl;
                 
            }
             else if (railMode == 2 && cell.getValue() == 0) {

                 std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                 if ((adjacentCells[3]->getValue() == 2)
                     || ((adjacentCells[3]->getValue() == 1))
                     || (adjacentCells[4]->getValue() == 2)
                     || (adjacentCells[4]->getValue() == 1)) {


                     idRail++;
                     cell.addRail(idRail, 1);
                 }
                 //std::cout << adjacentCells[1]->getValue() << std::endl;

             }
            
             else if (modeTrain == 1) {
                if (cell.hasRail()) {
                    cell.addTrain();
                    sf::Vector2f trainpos = cell.getPosTrain();
                    for (auto& cell : cells) {
                        if (cell.contains(trainpos)) {
                            std::vector<Cell*> celladja = getNeighbourHood(trainpos);
                            sf::Vector2f nextCell = celladja[2]->getPosCell();
                             cell.TrainMoveTo(nextCell);
                            /*std::cout << trainpos.x << "//" << trainpos.y << std::endl;*/
                        }
                    }
                    
                 
                }
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
void Grid::placeStation(float x, float y, sf::Color color) {
    Cell* cell = getCellAt(x, y);
    std::cout << x << " " << y << std::endl;
    cell->addStation(color);
}
void Grid::setTrainMode(bool trainMode) {

    modeTrain = trainMode;

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

