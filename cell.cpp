#include "Cell.h"
#include <iostream>
#include<string>
Cell::Cell(float x, float y, float size) : value(0), rail(nullptr), station(nullptr),train(nullptr) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Color(0,0,0,0));
    shape.setOutlineColor(sf::Color::Color(100, 100, 100, 150));
}

Cell::~Cell() {
    delete rail;
    delete station;
}

void Cell::draw(sf::RenderWindow& window) {
    window.draw(shape);
    if (rail) {
        rail->draw(window);
    }
    if (station) {
        station->draw(window);
    }
    if (train) {
        train->draw(window);
    }
}
    
void Cell::toggleValue() {
    if (!rail) { 
        value = (value == 1) ? 0 : 1;
        shape.setFillColor((value == 1) ? sf::Color::Green : sf::Color::Color(0, 0, 0, 0));
    }
    if (!station) {
        value = (value == 2) ? 0 : 1;
    }
}
Rail* Cell::getRailFromCell() {
    return rail;
}
Station* Cell::getStationFromCell() {
    return station;
}
Train* Cell::getTrainFromCell() {
    return train;
}
void Cell::debugStation() {
    std::cout << "Gare | Couleur : " << station->getColor() << "| Nombre de train: " << station->getNbTrain() << std::endl;
}
void Cell::debugRail() {
    std::cout << "Rail | Id : " << rail->getId() << "| Direction : " << rail->getDirection() << std::endl;
}
void Cell::addRail(int idRail, bool direction) {
    if (value == 0 && !rail) {
        value = (value == 1) ? 0 : 1;
        rail = new Rail(shape.getPosition().x, shape.getPosition().y, shape.getSize().x);
        rail->setId(idRail);
        rail->setDirection(direction);
        std::cout << rail->getDirection() << std::endl;
    }   
}
void Cell::addStation(sf::Color color) {
    value = (value == 2) ? 0 : 2;
    station = new Station(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, color);

}
void Cell::viewStatus(bool hover) {
    
    if (hover) {
        shape.setFillColor(sf::Color::Color(0,255,0,100));
    }
    else if (hover && value == 1) {
        shape.setFillColor(sf::Color::Red);
    }
    else {
        shape.setFillColor((value == 1) ? sf::Color::Color(0, 0, 0, 0) : sf::Color::Color(0, 0, 0, 0));
    }
}

bool Cell::contains(sf::Vector2f point) {
    return shape.getGlobalBounds().contains(point);
}
void Cell::setValue(int val) {
    value = val;
}
int Cell::getValue() const {
    return value;
}
Train* Cell::moveTrainToRail(Cell* adjCell, Station* station) {
    Train* train = NULL;
    if (station->getNbTrain() > 0) {
        station->removeTrain();
        train = adjCell->addTrain();
    }
    sf::Color randomColor;
    do {
        int randomIndex = std::rand() % 3;
        switch (randomIndex) {
        case 0: randomColor = sf::Color::Blue; break;
        case 1: randomColor = sf::Color::Magenta; break;
        case 2: randomColor = sf::Color::Red; break;
        }
    } while (colorToString(randomColor) == station->getColor());
    train->setColor(randomColor);
    return train;
}

bool Cell::hasRail() const {
    return rail != nullptr;
}
bool Cell::hasStation() const {
    return station != nullptr;
}
bool Cell::hasTrain() const {
    return train != nullptr;
}
Train* Cell::addTrain() {
    std::cout << "test" << std::endl;
    train = new Train((shape.getPosition().x) + 2, (shape.getPosition().y) + 2, shape.getSize().x);
    return train;
    
}

sf::Vector2f Cell::getPosTrain() {
    sf::Vector2f position = train->getPosition();
    return position;
}

sf::Vector2f Cell::getPosCell() {
    posx = (shape.getPosition().x);
    posy = (shape.getPosition().y);

   return { posx,posy};
}

void Cell::TrainMoveTo(sf::Vector2f nextCell) {

    train->moveTo(nextCell);

}
std::string Cell::colorToString(sf::Color color) {
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
void Cell::destroyTrain() {
    delete train;
    train = nullptr;
}
