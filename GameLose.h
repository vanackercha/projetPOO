#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameLose {
public:
    GameLose(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
};

