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
void Train::updatePos(float time, sf::Vector2f nextCell) {
	previousPosition = getPosition();
	next= nextCell - previousPosition;
	shape.move(next.x/(time*velocity), next.y/(time*velocity));
	
}
void Train::setIdRail(int idRail) {
	this->idRail = idRail;
}
int Train::getIdRail() {
	return this->idRail;
}
void Train::moveTo(sf::Vector2f nextcell){
	posi = getPosition();
	next= nextcell - posi;
	shape.move(next);
}

void Train::setPreviousPosition(sf::Vector2f previousPos){
	this->previousPosition = previousPos;
}

sf::Vector2f Train::getPreviousPosition() {
	previousPosition.x = previousPosition.x+2;
	previousPosition.y = previousPosition.y-2;
	return this->previousPosition;
}