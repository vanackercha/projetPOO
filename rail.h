#include <SFML/Graphics.hpp>
#include "Train.h"

class Rail {
public:
    Rail(float x, float y, float size);
    void draw(sf::RenderWindow& window);
    void setId(int id);
    int getId();
    void setDirection(bool dir);
    bool getDirection();
    void addtrain();

private:
    sf::RectangleShape shape;
    int idRail;
    bool direction;
    Train* train;
};

