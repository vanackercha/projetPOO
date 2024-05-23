#pragma once
#include "train.h"
#include <iostream>
#include <vector>

Train::Train(float x, float y, float size) {
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(x, y);
}

void Train::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
sf::Vector2f Train::getPosition() {
	x = shape.getPosition().x;
	y = shape.getPosition().y;
	return { x, y }; 
}

void Train::moveTo(sf::Vector2f nextCell){
	posi = getPosition();
	next= nextCell - posi;
	shape.move(next);
}