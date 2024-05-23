#include "train.h"

Train::Train(float x, float y, float size) {
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(x, y);
}

void Train::draw(sf::RenderWindow& window) {
	window.draw(shape);
}