#include <SFML/Graphics.hpp>
#include "Grid.h"

const int TILE_SIZE = 32;
const int GRID_WIDTH = 30; // Agrandi pour observer les performances
const int GRID_HEIGHT = 30; // Agrandi pour observer les performances

int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE), "Mini Jeu de Grille");

    Grid grid(GRID_WIDTH, GRID_HEIGHT, TILE_SIZE);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;
                    grid.placeShape(mouseX, mouseY);
                }
            }
        }

        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;
        grid.highlightShape(mouseX, mouseY);

        window.clear(sf::Color::White);
        grid.draw(window);
        window.display();
    }

    return 0;
}
