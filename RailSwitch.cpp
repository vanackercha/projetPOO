#include "RailSwitch.h"
#include <iostream>

RailSwitch::RailSwitch(float x, float y, float size) : direction(false){
   
    shape.setSize(sf::Vector2f(size, size / 2));
    shape.setPosition(x, y + size / 2 - size / 8);
    shape.setFillColor(sf::Color::Red);
}

void RailSwitch::draw(sf::RenderWindow& window) {
    
    window.draw(shape);
}

void RailSwitch::setId(int id) {
    idRail = id;
}

void RailSwitch::setadjarail(std::vector<Rail*>raillink){
    id1 = raillink[0]->getId();
    id2 = raillink[1]->getId();
    id3 = raillink[2]->getId();
    std::cout << id1 << "//" << id2 << "//" << id3 << std::endl;
}

int RailSwitch::getNextCell() {
    return this->id2;
}

