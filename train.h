#pragma once
#include <SFML/Graphics.hpp>

class Train
{
public:
	Train(float x, float y, float size);
	void draw(sf::RenderWindow& window);
private : 
	std::string color;
	sf::RectangleShape shape;
};

