#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

class Grid {
public:
    Grid(int width, int height, int tileSize);
    ~Grid();
    void draw(sf::RenderWindow& window);
    void highlightShape(int mouseX, int mouseY);
    void placeShape(int mouseX, int mouseY);
    void stop();

private:
    std::vector<std::vector<Tile>> grid;
    int width;
    int height;
    int tileSize;
    std::thread updateThread;
    std::mutex gridMutex;
    std::atomic<bool> running;
    int highlightX;
    int highlightY;

    void resetHighlight();
    void updateLoop();
    void update();
};

#endif // GRID_H
