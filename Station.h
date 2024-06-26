#pragma once
#include <SFML/Graphics.hpp>
#include "train.h"
class Station {
private:
    sf::RectangleShape shape;
    std::string color;
    int nbTrain = 0;
    sf::Time elapsedTime;
    sf::Time TrainInterval = sf::seconds(2);
    sf::Font font;
    sf::Text trainCountText;
    bool hasRail = false;
public:
    Station(float x, float y, float cellSize, sf::Color color);
    void draw(sf::RenderWindow& window);
    int getNbTrain();
    void setNbTrain(int nbTrain);
    std::string getColor();
    void setHasRail();
    bool getHasRail();
    std::string colorToString(sf::Color color);
    void generateTrain();
    void removeTrain();
    void update(sf::Time time);
    
};

