#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Grid.h"
#include "WinMenu.h"
#include "GameLose.h"
#include <iostream>

int main() {
    // Obtenir le mode vidéo par défaut (la résolution de l'écran)
    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    //// Création de la fenêtre en mode plein écran
    //sf::RenderWindow window(desktop, "Choo-Choo Valley", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Choo-Choo Valley");

    const int rows = 75;
    const int cols = 75;
    const float cellSize = 50.0f;

    Grid grid(rows, cols, cellSize);
    grid.placeStation(cellSize * 10, cellSize * 10, sf::Color::Magenta);
    grid.placeStation(cellSize * 4, cellSize * 15, sf::Color::Red);
    grid.placeStation(cellSize * 15, cellSize * 15, sf::Color::Blue);

    sf::Clock clock;

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

    sf::RectangleShape trainButton(sf::Vector2f(100, 50));
    trainButton.setPosition(1050, 150);
    trainButton.setFillColor(sf::Color::Blue);


    sf::RectangleShape SwitchButton(sf::Vector2f(100, 50));
    SwitchButton.setPosition(1050, 250);
    SwitchButton.setFillColor(sf::Color::Blue);
  
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

    sf::Text textTrain("Train", font, 20);
    textTrain.setPosition(1070, 160);
    textTrain.setFillColor(sf::Color::White);

    sf::Text textSwitch("switch", font, 20);
    textSwitch.setPosition(1070, 260);
    textSwitch.setFillColor(sf::Color::White);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    int score = grid.getScore();

    int railMode = 0;
    bool inGame = false;
    bool gameWon = false;
    bool trainmode = false;
    bool switchmode = false;
    bool gameLose = false;

    Menu menu(window.getSize().x, window.getSize().y);
    WinMenu winMenu(window.getSize().x, window.getSize().y);
    GameLose loseMenu(window.getSize().x, window.getSize().y);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    sf::Texture winTexture;
    if (!winTexture.loadFromFile("win_img.png")) {
        return -1;
    }
    sf::Sprite winBackground(winTexture);
    winBackground.setScale(window.getSize().x, window.getSize().y);

    sf::Texture loseTexture;
    if (!loseTexture.loadFromFile("lose.png")) {
        return -1;
    }
    sf::Sprite loseBackground(loseTexture);
    loseBackground.setScale(window.getSize().x , window.getSize().y );

    window.setFramerateLimit(60);

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
                    else if (trainButton.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                        trainmode = !trainmode;
                        grid.setTrainMode(trainmode);
                        if (trainmode) {
                            trainButton.setFillColor(sf::Color::Green);
                        }
                        else {
                            trainButton.setFillColor(sf::Color::Blue);
                        }
                    }
                    else if (SwitchButton.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                        switchmode = !switchmode;
                        grid.setSwitchMode(switchmode);
                        if (switchmode == false) {
                            SwitchButton.setFillColor(sf::Color::Green);
                        }
                        else {
                            SwitchButton.setFillColor(sf::Color::Blue);
                        }
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
                            grid.setScore(0);
                            grid = Grid(rows, cols, cellSize);
                            grid.placeStation(cellSize * 15, cellSize * 10, sf::Color::Magenta);
                            grid.placeStation(cellSize * 4, cellSize * 4, sf::Color::Red);
                            grid.placeStation(cellSize * 15, cellSize * 15, sf::Color::Blue);
                            inGame = true;
                            gameWon = false;
                        }
                        else if (selectedItem == 1) {
                            window.close();
                        }
                    }
                }
            }
            else if (gameLose) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        loseMenu.moveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        loseMenu.moveDown();
                    }
                    if (event.key.code == sf::Keyboard::Return) {
                        int selectedItem = loseMenu.getSelectedItemIndex();
                        if (selectedItem == 0) {
                            grid.setScore(0);
                            grid = Grid(rows, cols, cellSize);
                            grid.placeStation(cellSize * 15, cellSize * 10, sf::Color::Magenta);
                            grid.placeStation(cellSize * 4, cellSize * 4, sf::Color::Red);
                            grid.placeStation(cellSize * 15, cellSize * 15, sf::Color::Blue);
                            inGame = true;
                            gameLose = false;
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
                            window.close();
                        }
                    }
                }
            }
        }

        sf::Time time = clock.restart();

        if (inGame) {
            grid.update(time);
            window.clear();

            for (auto& sprite : grassSprites) {
                window.draw(sprite);
            }
            grid.draw(window);
            window.draw(railButtonH);
            window.draw(railButtonV);
            window.draw(textRailH);
            window.draw(textRailV);
            window.draw(trainButton);
            window.draw(textTrain);
            window.draw(SwitchButton);
            window.draw(textSwitch);

            scoreText.setString("Score: " + std::to_string(grid.getScore()));
            window.draw(scoreText);

            if (grid.getGameWon()) {
                gameWon = true;
                inGame = false;
            }
            else if (grid.getGameLose()) {
                gameLose = true;
                inGame = false;
            }
        }
        else if (gameWon) {
            window.draw(winBackground);
            winMenu.draw(window);
        }
        else if (gameLose) {
            window.draw(loseBackground);
            loseMenu.draw(window);
        }
        else {
            window.draw(background);
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}