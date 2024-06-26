#pragma once
#include <SFML/Graphics.hpp>
#include "Rail.h"
#include "Station.h"
#include "Train.h"
#include "RailSwitch.h"
class Cell {
public:
    Cell(float x, float y, float size);
    ~Cell();
    void draw(sf::RenderWindow& window);
    void toggleValue();
    void addRail(int idRail, bool direction);
    void addStation(sf::Color color);
    void viewStatus(bool hover);
    bool contains(sf::Vector2f point);
    Train* moveTrainToRail(Cell* adjCell, Station* station);
    Rail* getRailFromCell();
    void debugStation();
    void debugRail();
    void setValue(int value);
    int getValue() const;
    bool hasRail() const;
    bool hasStation() const;
    bool hasTrain() const;
    bool hasSwitch() const;
    void destroyTrain();
    Station* getStationFromCell();
    Train* getTrainFromCell();
    RailSwitch* getSwitchFromCell();
    Train* addTrain();
    sf::Vector2f getPosTrain();
    sf::Vector2f getPosCell();
    void TrainMoveTo(sf::Vector2f nextCell);
    void addSwitch(int idrail, std::vector<Rail*> raillink);
    std::string colorToString(sf::Color color);
    void setColor(sf::Color color);


private:
    sf::RectangleShape shape;
    int value;
    float posy;
    float posx;
    Rail* rail; // Pointeur brut vers un rail MERCI MEC
    Station* station;
    Train* train;
    RailSwitch* railswitch;

};

