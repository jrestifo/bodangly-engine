/*
 * Circle.cpp
 *
 *  Created on: Apr 1, 2013
 *      Author: demian
 */

#include "Circle.h"

Circle::Circle() {}

Circle::~Circle() {}

const Vector2D<Double>& Circle::getPosition() const {
	return _position;
}

void Circle::setPosition(const Vector2D<Double>& position) {
	_position = position;
}

const Double& Circle::getRadius() const {
	return _radius;
}

void Circle::setRadius(const Double& radius) {
	_radius = radius;
}
