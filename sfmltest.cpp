#include <SFML/Graphics.hpp>
#include "Grid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML Grid");

    const int rows = 10;
    const int cols = 10;
    const float cellSize = 50.0f;

    Grid grid(rows, cols, cellSize);

    // Création du bouton "Rail"
    sf::RectangleShape railButton(sf::Vector2f(100, 50));
    railButton.setPosition(850, 50); // Position du bouton
    railButton.setFillColor(sf::Color::Blue);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Gestion de l'erreur
        return -1;
    }

    sf::Text buttonText("Rail", font, 20);
    buttonText.setPosition(870, 60); // Position du texte
    buttonText.setFillColor(sf::Color::White);

    bool railMode = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Vérifier si le bouton "Rail" est cliqué
                if (railButton.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    railMode = !railMode;
                    grid.setRailMode(railMode);
                    railButton.setFillColor(railMode ? sf::Color::Green : sf::Color::Blue); // Changer la couleur du bouton pour indiquer l'état
                }
                else {
                    grid.handleClick(window.mapPixelToCoords(mousePos));
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                grid.handleHover(window.mapPixelToCoords(mousePos));
            }
        }

        window.clear();
        grid.draw(window);
        window.draw(railButton);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
