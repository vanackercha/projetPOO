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
    std::cout << "Rail | Id : " << rail->getId() << "| Direction : " <<rail->getDirection() << std::endl;
    return rail;
}
Station* Cell::getStationFromCell() {
    std::cout << "Gare | Couleur : " << station ->getColor() << "| Nombre de train: " << station->getNbTrain() << std::endl;
    return station;
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
        shape.setFillColor((value == 1) ? sf::Color::Green : sf::Color::Color(0, 0, 0, 0));
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

bool Cell::hasRail() const {
    return rail != nullptr;
}
bool Cell::hasStation() const {
    return station != nullptr;
}
 
void Cell::addTrain() {
    std::cout << "test" << std::endl;
    train = new Train(shape.getPosition().x, shape.getPosition().y, shape.getSize().x);
}
