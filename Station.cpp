 
#include "Station.h"

Station::Station(float x, float y, float cellSize, sf::Color color): nbTrain(0) {
    shape.setSize(sf::Vector2f(cellSize * 1.2, cellSize * 1.2));
    shape.setPosition(x, y);
    shape.setFillColor(color);
    this->color = colorToString(color);
}

void Station::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
std::string Station::getColor() {
    return this->color;
}
void Station::setNbTrain(int nbTrain) {
    this->nbTrain = nbTrain;
}
int Station::getNbTrain() {
    return nbTrain;
}

std::string Station::colorToString(sf::Color color) {
    if (color == sf::Color::Magenta) {
        return "Mangenta";
    }
    else if (color == sf::Color::Red) {
        return "Rouge";
    }
    else if (color == sf::Color::Blue) {
        return "Bleu";
    }
}
