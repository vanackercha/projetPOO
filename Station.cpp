 
#include "Station.h"
#include <iostream>
Station::Station(float x, float y, float cellSize, sf::Color color): nbTrain(0), elapsedTime(sf::Time::Zero) {
    shape.setSize(sf::Vector2f(cellSize * 1.2, cellSize * 1.2));
    shape.setPosition(x, y);
    shape.setFillColor(color);
    this->color = colorToString(color);
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Police non chargée" << std::endl;
    }
    trainCountText.setFont(font);
    trainCountText.setCharacterSize(20);
    trainCountText.setFillColor(sf::Color::White);
    trainCountText.setPosition(x, y - 25);
    trainCountText.setString("Trains: 0");
}

void Station::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(trainCountText);
}
std::string Station::getColor() {
    return this->color;
}
void Station::setNbTrain(int nbTrain) {
    this->nbTrain = nbTrain;
}
int Station::getNbTrain() {
    return this->nbTrain;
}
void Station::setHasRail() {
    this->hasRail = !this->hasRail;
}
bool Station::getHasRail() {
    return this->hasRail;
}
void Station::generateTrain() {
    std::cout << "Train généré sur station :" << this->color << std::endl;
    if (nbTrain < 3) {
        nbTrain++;
    }
    else {
        nbTrain = 3;
    }
    trainCountText.setString("Trains: " + std::to_string(nbTrain));
}

void Station::removeTrain() {
    if (nbTrain > 0) {
        nbTrain--;
    }
    trainCountText.setString("Trains: " + std::to_string(nbTrain));
}
void Station::update(sf::Time time) {
    this->elapsedTime += time;
    if (elapsedTime >= TrainInterval) {
        generateTrain();
        elapsedTime -= TrainInterval;
    }
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
