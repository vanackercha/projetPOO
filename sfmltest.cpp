#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Grid.h"
#include "WinMenu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Choo-Choo Valley");

    const int rows = 75;
    const int cols = 75;
    const float cellSize = 50.0f;

    Grid grid(rows, cols, cellSize);
    grid.placeStation(cellSize, cellSize);
    grid.placeStation(cellSize * 15, cellSize * 3);

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("grass.png")) {
        return -1;
    }

    std::vector<sf::Sprite> grassSprites;
    for (int i = 0; i < window.getSize().x; i += grassTexture.getSize().x) {
        for (int j = 0; j < window.getSize().y; j += grassTexture.getSize().y) {
            sf::Sprite sprite(grassTexture);
            sprite.setPosition(i, j);
            grassSprites.push_back(sprite);
        }
    }

    sf::RectangleShape railButton(sf::Vector2f(100, 50));
    railButton.setPosition(850, 50);
    railButton.setFillColor(sf::Color::Blue);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text buttonText("Rail", font, 20);
    buttonText.setPosition(870, 60);
    buttonText.setFillColor(sf::Color::White);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    int score = 0;

    bool railMode = false;
    bool inGame = false;
    bool gameWon = false;

    Menu menu(window.getSize().x, window.getSize().y);
    WinMenu winMenu(window.getSize().x, window.getSize().y);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    sf::Texture winTexture;
    if (!winTexture.loadFromFile("win.png")) {
        return -1;
    }
    sf::Sprite winBackground(winTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inGame) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (railButton.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                        railMode = !railMode;
                        grid.setRailMode(railMode);
                        railButton.setFillColor(railMode ? sf::Color::Green : sf::Color::Blue);
                    }
                    else {
                        grid.handleClick(window.mapPixelToCoords(mousePos));
                        score++;
                        if (score >= 10) {
                            gameWon = true;
                            inGame = false;
                        }
                    }
                }

                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    grid.handleHover(window.mapPixelToCoords(mousePos));
                }
            }
            else if (gameWon) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        winMenu.moveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        winMenu.moveDown();
                    }
                    if (event.key.code == sf::Keyboard::Return) {
                        int selectedItem = winMenu.getSelectedItemIndex();
                        if (selectedItem == 0) {
                            score = 0;
                            grid = Grid(rows, cols, cellSize);  
                            grid.placeStation(cellSize, cellSize);
                            grid.placeStation(cellSize * 15, cellSize * 3);
                            inGame = true;
                            gameWon = false;
                        }
                        else if (selectedItem == 1) {
                            window.close();
                        }
                    }
                }
            }
            else {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                    }
                    if (event.key.code == sf::Keyboard::Return) {
                        int selectedItem = menu.getSelectedItemIndex();
                        if (selectedItem == 0) {
                            inGame = true;
                        }
                        else if (selectedItem == 1) {
                            // TODO : OPTION
                        }
                        else if (selectedItem == 2) {
                            window.close();
                        }
                    }
                }
            }
        }

        window.clear();

        if (inGame) {
            for (auto& sprite : grassSprites) {
                window.draw(sprite);
            }
            grid.draw(window);
            window.draw(railButton);
            window.draw(buttonText);

            scoreText.setString("Score: " + std::to_string(score));
            window.draw(scoreText);
        }
        else if (gameWon) {
            window.draw(winBackground);
            winMenu.draw(window);
        }
        else {
            window.draw(background);
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}
