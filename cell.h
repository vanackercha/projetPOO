
#include <SFML/Graphics.hpp>
#include "Rail.h"
#include "Station.h"
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
    Rail* getRailFromCell();
    void setValue(int value);
    int getValue() const;
    bool hasRail() const;
    bool hasStation() const;
    Station* getStationFromCell();
    void addTrain();

private:
    sf::RectangleShape shape;
    int value;
    Rail* rail; // Pointeur brut vers un rail MERCI MEC
    Station* station;
    Train* train;
};

