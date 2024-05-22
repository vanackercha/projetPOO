#pragma once
#include <SFML/Graphics.hpp>
class Station {
private:
    sf::RectangleShape shape;
    std::string color;
    int nbTrain = 0;
public:
    Station(float x, float y, float cellSize, sf::Color color);
    void draw(sf::RenderWindow& window);
    int getNbTrain();
    void setNbTrain(int nbTrain);
    std::string getColor();
    std::string colorToString(sf::Color color);
};

