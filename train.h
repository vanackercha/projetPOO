#pragma once
#include <SFML/Graphics.hpp>


class Train
{
public:
	Train(float x, float y, float size);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void moveTo(sf::Vector2f nextCell);
	void updatePos( sf::Vector2f nextCell, sf::Vector2f current);
	void setPreviousPosition(sf::Vector2f previousPos);
	void setIdRail(int idRail);
	int getIdRail();
	sf::Vector2f getPreviousPosition();
	std::string colorToString(sf::Color color);
	void setColor(sf::Color color);
	std::string getColor();
	void setPrevId(int id);
	int getPrevId();
private : 
	std::string color;
	sf::RectangleShape shape;
	float x;
	float y;
	int prevId = 0;
	int idRail;
	sf::Vector2f position;
	sf::Vector2f previousPosition;
	sf::Vector2f posi;
	sf::Vector2f next;
	int velocity = 5;
	bool stop = false;
	
};

