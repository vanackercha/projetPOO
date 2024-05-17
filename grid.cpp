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
            if (railMode && cell.getValue() == 0) {
                cell.addRail(); // Ajouter un rail à la cellule cliquée si le mode "Rail" est activé et la valeur est 0
            }
            
            std::cout << "Clicked on cell at (" << mousePos.x / cellSize << ", " << mousePos.y / cellSize << ") with new value: " << cell.getValue() << std::endl;
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

void Grid::setRailMode(bool enabled) {
    railMode = enabled;
}
