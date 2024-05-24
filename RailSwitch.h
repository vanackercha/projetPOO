#pragma once
#include <SFML/Graphics.hpp>
#include "rail.h"


class RailSwitch
{public :
	RailSwitch(float x, float y, float size);
	void draw(sf::RenderWindow& window);
	void setId(int id);
	void setadjarail(std::vector<Rail*> railink);
private:
	
	sf::RectangleShape shape;
	bool direction;
	int idRail = 0;
	int id1 = 0;
	int id2 = 0;
	int id3 = 0;

};

