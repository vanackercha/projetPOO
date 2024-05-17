#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(int x, int y, int size);
    void draw(sf::RenderWindow& window);
    void setColor(const sf::Color& color);
    void resetColor();

private:
    sf::RectangleShape shape;
    sf::Color defaultColor;
};

#endif // TILE_H
