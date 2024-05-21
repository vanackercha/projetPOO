#include "Menu.h"

Menu::Menu(float width, float height) : selectedItemIndex(0) {
    if (!font.loadFromFile("arial.ttf")) {
        // TODO : Gestion erreur
    }
    title.setFont(font);
    title.setString("Choo-Choo Valley");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Black);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(width / 2.0f, height / 6.0f));

    std::string menuOptions[] = { "Play", "Options", "Exit" };
    for (int i = 0; i < 3; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(50);
        text.setFillColor(i == 0 ? sf::Color::Blue : sf::Color::Black);

        // Center the text horizontally
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(width / 2.0f, height / (3 + 2) * (i + 2)));

        menuItems.push_back(text);

        //sf::RectangleShape button(sf::Vector2f(textRect.width + 20, textRect.height + 10));
        //button.setOrigin(button.getSize().x / 2.0f, button.getSize().y / 2.0f);
        //button.setPosition(sf::Vector2f(width / 2.0f, height / (3 + 2) * (i + 2)));
        //button.setFillColor(sf::Color::Transparent);
        //button.setOutlineColor(sf::Color::White);
        //button.setOutlineThickness(2);
        //buttons.push_back(button);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (const auto& button : buttons) {
        window.draw(button);
    }
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

int Menu::getSelectedItemIndex() const {
    return selectedItemIndex;
}
