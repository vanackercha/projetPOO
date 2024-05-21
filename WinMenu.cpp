#include "WinMenu.h"

WinMenu::WinMenu(float x, float y) : selectedItemIndex(0) {
    if (!font.loadFromFile("arial.ttf")) {
        // TODO :: ERREUR
    }
    title.setFont(font);
    title.setString("You win !");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Black);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(x / 2.0f, y / 6.0f));
    std::string menuOptions[] = { "Replay", "Quit" };
    for (int i = 0; i < 2; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(50);
        text.setFillColor(i == 0 ? sf::Color::Blue : sf::Color::Black);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(x / 2.0f, y / 3.0f * (i + 1)));

        menuItems.push_back(text);
    }
}

void WinMenu::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void WinMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

void WinMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

int WinMenu::getSelectedItemIndex() const {
    return selectedItemIndex;
}
