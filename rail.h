#pragma once
#include <SFML/Graphics.hpp>


class Rail {
public:
    Rail(float x, float y, float size, bool direction);
    void draw(sf::RenderWindow& window);
    void setId(int id);
    int getId();
    void setDirection(bool dir);
    bool getDirection();
    

private:
    sf::RectangleShape shape;
    int idRail;
    bool direction;
  
};

