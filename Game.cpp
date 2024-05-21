#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1500, 1000), "Choo-Choo Valley"),
    grid(75, 75, 50.0f),
    menu(window.getSize().x, window.getSize().y),
    railButton(sf::Vector2f(100, 50)),
    score(0),
    railMode(false),
    inGame(false),
    gameWon(false) {

    grid.placeStation(50.0f, 50.0f);
    grid.placeStation(750.0f, 150.0f);

    if (!grassTexture.loadFromFile("grass.png")) {
        // Handle error
    }

    for (int i = 0; i < window.getSize().x; i += grassTexture.getSize().x) {
        for (int j = 0; j < window.getSize().y; j += grassTexture.getSize().y) {
            sf::Sprite sprite(grassTexture);
            sprite.setPosition(i, j);
            grassSprites.push_back(sprite);
        }
    }

    railButton.setPosition(850, 50);
    railButton.setFillColor(sf::Color::Blue);

    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }

    buttonText.setFont(font);
    buttonText.setString("Rail");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(870, 60);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    winText.setFont(font);
    winText.setString("You Win!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::Green);
    sf::FloatRect winTextRect = winText.getLocalBounds();
    winText.setOrigin(winTextRect.left + winTextRect.width / 2.0f, winTextRect.top + winTextRect.height / 2.0f);
    winText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    if (!backgroundTexture.loadFromFile("background.png")) {
        // TODO :: GESTION D'ERREUR
    }
    background.setTexture(backgroundTexture);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (inGame) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseMoved) {
                handleMouseHover(sf::Mouse::getPosition(window));
            }
        }
        else {
            if (event.type == sf::Event::KeyPressed) {
                handlePlayerInput(event.key.code, true);
            }
        }
    }
}

void Game::render() {
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

        if (gameWon) {
            window.draw(winText);
        }
    }
    else {
        window.draw(background);
        menu.draw(window);
    }

    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Up) {
        menu.moveUp();
    }
    else if (key == sf::Keyboard::Down) {
        menu.moveDown();
    }
    else if (key == sf::Keyboard::Return) {
        int selectedItem = menu.getSelectedItemIndex();
        if (selectedItem == 0) {
            inGame = true;
        }
        else if (selectedItem == 1) {
            // TODO: Handle options
        }
        else if (selectedItem == 2) {
            window.close();
        }
    }
}

void Game::handleMouseClick(sf::Vector2i mousePos) {
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
        }
    }
}

void Game::handleMouseHover(sf::Vector2i mousePos) {
    grid.handleHover(window.mapPixelToCoords(mousePos));
}
