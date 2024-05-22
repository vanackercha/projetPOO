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
    grid.placeStation(cellSize* 20, cellSize*15, sf::Color::Magenta);
    grid.placeStation(cellSize * 2, cellSize * 2, sf::Color::Red);

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

    sf::RectangleShape railButtonH(sf::Vector2f(100, 50));
    railButtonH.setPosition(850, 50);
    railButtonH.setFillColor(sf::Color::Blue);

    sf::RectangleShape railButtonV(sf::Vector2f(100, 50));
    railButtonV.setPosition(1050, 50);
    railButtonV.setFillColor(sf::Color::Blue);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text textRailH("RailH", font, 20);
    textRailH.setPosition(870, 60);
    textRailH.setFillColor(sf::Color::White);

    sf::Text textRailV("RailV", font, 20);
    textRailV.setPosition(1070, 60);
    textRailV.setFillColor(sf::Color::White);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    int score = 0;

    int railMode = 0;
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

                    if (railButtonH.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                        if (railMode == 1) {
                            railMode = 0;
                            railButtonH.setFillColor(sf::Color::Blue);
                        }
                        else {
                            railMode = 1;
                            railButtonH.setFillColor(sf::Color::Green);
                            railButtonV.setFillColor(sf::Color::Blue);
                        }
                        
                        grid.setRailMode(railMode);
                    }
                    else if (railButtonV.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                        if (railMode == 2) {
                            railMode = 0;
                            railButtonV.setFillColor(sf::Color::Blue);
                        }
                        else {
                            railMode = 2;
                            railButtonV.setFillColor(sf::Color::Green);
                            railButtonH.setFillColor(sf::Color::Blue);
                        }
                        grid.setRailMode(railMode);
                    }
                    else {
                        grid.handleClick(window.mapPixelToCoords(mousePos));
                        score++;
                        if (score >= 20) {
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
                            grid.placeStation(cellSize * 15, cellSize * 10, sf::Color::Magenta);
                            grid.placeStation(cellSize, cellSize, sf::Color::Red);
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
            window.draw(railButtonH);
            window.draw(railButtonV);
            window.draw(textRailH);
            window.draw(textRailV);

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
