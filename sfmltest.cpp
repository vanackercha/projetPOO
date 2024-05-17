#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Classe représentant une cellule de la grille
class Cell {
public:
    Cell(float x, float y, float size) : value(0) {
        shape.setSize(sf::Vector2f(size, size));
        shape.setPosition(x, y);
        shape.setOutlineThickness(1);
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::Blue);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void toggleValue() {
        value = (value == 1) ? 0 : 1;
        shape.setFillColor((value == 1) ? sf::Color::Green : sf::Color::Black);
    }

    void viewStatus() {
        if (value == 1) {
            shape.setFillColor(sf::Color::Red);
        }
    }

    bool contains(sf::Vector2f point) {
        return shape.getGlobalBounds().contains(point);
    }

    int getValue() const {
        return value;
    }

private:
    sf::RectangleShape shape;
    int value;
};

// Classe représentant la grille de cellules
class Grid {
public:
    Grid(int rows, int cols, float cellSize) : rows(rows), cols(cols), cellSize(cellSize) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cells.push_back(Cell(j * cellSize, i * cellSize, cellSize));
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& cell : cells) {
            cell.draw(window);
        }
    }

    void handleClick(sf::Vector2f mousePos) {
        for (auto& cell : cells) {
            if (cell.contains(mousePos)) {
                cell.toggleValue();
                std::cout << "Clicked on cell at (" << mousePos.x / cellSize << ", " << mousePos.y / cellSize << ") with new value: " << cell.getValue() << std::endl;
                break;
            }
        }
    }

    void handleHover(sf::Vector2f mousePos) {
        for (auto& cell : cells) {
            if (cell.contains(mousePos)) {
                cell.viewStatus();
            }
        }
    }

private:
    int rows, cols;
    float cellSize;
    std::vector<Cell> cells;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML Grid");

    const int rows = 10;
    const int cols = 10;
    const float cellSize = 50.0f;

    Grid grid(rows, cols, cellSize);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                grid.handleHover(window.mapPixelToCoords(mousePos));
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                grid.handleClick(window.mapPixelToCoords(mousePos));
            }
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
