#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int cols, float cellSize) : rows(rows), cols(cols), cellSize(cellSize), previousHoveredCell(nullptr) {
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
            cell.addRail();
            cell.toggleValue();
            std::cout << "(" << mousePos.x / cellSize << ", " << mousePos.y / cellSize << ") Value: " << cell.getValue() << std::endl;
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

void Grid::placeStation(float x, float y) {
    stations.emplace_back(x, y, cellSize);

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            Cell* cell = getCellAt(x + j * cellSize, y + i * cellSize);
            if (cell) {
                cell->setValue(1);
            }
        }
    }
}

Cell* Grid::getCellAt(float x, float y) {
    for (auto& cell : cells) {
        if (cell.contains(sf::Vector2f(x, y))) {
            return &cell;
        }
    }
    return nullptr;
}