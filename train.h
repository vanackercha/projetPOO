#pragma once
#include <SFML/Graphics.hpp>


class Train
{
public:
	Train(float x, float y, float size);
	void draw(sf::RenderWindow& window);
	sf::Vector2f  getPosition();
	void moveTo(sf::Vector2f nextCell);
	void updatePos( sf::Vector2f nextCell, sf::Vector2f current);
	void setPreviousPosition(sf::Vector2f previousPos);
	sf::Vector2f getPreviousPosition();
	void setPrevId(int id);
	int getPrevId();
private : 
	std::string color;
	sf::RectangleShape shape;
	float x;
	float y;
	int prevId = 0;
	sf::Vector2f position;
	sf::Vector2f previousPosition;
	sf::Vector2f posi;
	sf::Vector2f next;
	int velocity = 60;
	bool stop = false;
	
};

