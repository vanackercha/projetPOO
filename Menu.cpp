#include "Menu.h"

Menu::Menu(float width, float height) : selectedItemIndex(0) {
    if (!font.loadFromFile("arial.ttf")) {
        // TODO : Gestion erreur
    }

    // Configuration du titre
    title.setFont(font);
    title.setString("Choo-Choo Valley");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(width / 2.0f, height / 6.0f));

    // Configuration des options de menu
    std::string menuOptions[] = { "Exit", "Play" };
    for (int i = 0; i < 2; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(50);
        text.setFillColor(i == 1 ? sf::Color::Yellow : sf::Color::White); // "Play" en jaune, "Exit" en blanc
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(width / 2.0f, height / (2.5f + i * 1.5f)));

        menuItems.push_back(text);

        sf::RectangleShape button(sf::Vector2f(textRect.width + 40, textRect.height + 20));
        button.setOrigin(button.getSize().x / 2.0f, button.getSize().y / 2.0f);
        button.setPosition(sf::Vector2f(width / 2.0f, height / (2.5f + i * 1.5f)));
        button.setFillColor(sf::Color(0, 0, 0, 150));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(2);
        buttons.push_back(button);
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
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int Menu::getSelectedItemIndex() const {
    return selectedItemIndex;
}
