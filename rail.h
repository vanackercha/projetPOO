#include <SFML/Graphics.hpp>

class Rail {
public:
    Rail(float x, float y, float size);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
};

