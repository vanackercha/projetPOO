#pragma once
#include <SFML/Graphics.hpp>


class Train
{
public:
	Train(float x, float y, float size);
	void draw(sf::RenderWindow& window);
	sf::Vector2f  getPosition();
	void moveTo(sf::Vector2f nextCell);
private : 
	std::string color;
	sf::RectangleShape shape;
	float x;
	float y;
	sf::Vector2f position;
	sf::Vector2f posi;
	sf::Vector2f next;
	
};

