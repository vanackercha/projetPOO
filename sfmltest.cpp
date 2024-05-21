#include <SFML/Graphics.hpp>
#include "Grid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML Grid");

    const int rows = 75;
    const int cols = 75;
    const float cellSize = 50.0f;

    
    Grid grid(rows, cols, cellSize);
    grid.placeStation(cellSize, cellSize);
    grid.placeStation(cellSize * 15, cellSize * 3);
    // Charger la texture d'herbe
    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("grass.png")) {
        return -1; // Erreur de chargement de la texture
    }

    // Créer une grille de sprites pour la texture d'herbe
    std::vector<sf::Sprite> grassSprites;
    for (int i = 0; i < window.getSize().x; i += grassTexture.getSize().x) {
        for (int j = 0; j < window.getSize().y; j += grassTexture.getSize().y) {
            sf::Sprite sprite(grassTexture);
            sprite.setPosition(i, j);
            grassSprites.push_back(sprite);
        }
    }

    // Créer le bouton "Rail"
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
        // Dessiner la grille de sprites pour la texture d'herbe
        for (auto& sprite : grassSprites) {
            window.draw(sprite);
        }
        grid.draw(window);
        window.draw(railButton);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
