#ifndef RAIL_H
#define RAIL_H

#include <SFML/Graphics.hpp>

class Rail {
public:
    Rail(float x, float y, float size);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
};

#endif // RAIL_H
