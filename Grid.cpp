#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int cols, float cellSize) : rows(rows), cols(cols), cellSize(cellSize) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells.push_back(Cell(j * cellSize, i * cellSize, cellSize));
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
            cell.toggleValue();
            std::cout << "Clicked on cell at (" << mousePos.x / cellSize << ", " << mousePos.y / cellSize << ") with new value: " << cell.getValue() << std::endl;
            break;
        }
    }
}

void Grid::handleHover(sf::Vector2f mousePos) {
    for (auto& cell : cells) {
        if (cell.contains(mousePos)) {
            cell.viewStatus();
        }
    }
}
