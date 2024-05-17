#include <SFML/Graphics.hpp>
#include "Grid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML Grid");

    const int rows = 40;
    const int cols = 40;
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
