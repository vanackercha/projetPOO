#include "Grid.h"
#include <iostream>

Grid::Grid(int width, int height, int tileSize) : width(width), height(height), tileSize(tileSize), running(true), highlightX(-1), highlightY(-1) {
    grid.resize(width, std::vector<Tile>(height, Tile(0, 0, tileSize)));

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            grid[i][j] = Tile(i, j, tileSize);
        }
    }

    updateThread = std::thread(&Grid::updateLoop, this);
}

Grid::~Grid() {
    running = false;
    if (updateThread.joinable()) {
        updateThread.join();
    }
}

void Grid::draw(sf::RenderWindow& window) {
    std::lock_guard<std::mutex> lock(gridMutex);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            grid[i][j].draw(window);
        }
    }
}

void Grid::highlightShape(int mouseX, int mouseY) {
    std::lock_guard<std::mutex> lock(gridMutex);
    resetHighlight();

    int x = mouseX / tileSize;
    int y = mouseY / tileSize;

    if (x < 0 || y < 0 || x + 2 >= width || y + 2 >= height) {
        return; // Ne rien faire si les indices sont hors limites
    }

    for (int i = x; i < x + 3 && i < width; ++i) {
        for (int j = y; j < y + 3 && j < height; ++j) {
            grid[i][j].setColor(sf::Color::Yellow);
        }
    }

    highlightX = x;
    highlightY = y;
}

void Grid::placeShape(int mouseX, int mouseY) {
    std::lock_guard<std::mutex> lock(gridMutex);
    int x = mouseX / tileSize;
    int y = mouseY / tileSize;

    if (x < 0 || y < 0 || x + 2 >= width || y + 2 >= height) {
        return; // Ne rien faire si les indices sont hors limites
    }

    for (int i = x; i < x + 3 && i < width; ++i) {
        for (int j = y; j < y + 3 && j < height; ++j) {
            grid[i][j].setColor(sf::Color::Blue);
        }
    }
}

void Grid::resetHighlight() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            grid[i][j].resetColor();
        }
    }
}

void Grid::update() {
    std::lock_guard<std::mutex> lock(gridMutex);
    if (highlightX >= 0 && highlightY >= 0) {
        highlightShape(highlightX * tileSize, highlightY * tileSize);
    }
}

void Grid::updateLoop() {
    while (running) {
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Environ 60 FPS
    }
}
