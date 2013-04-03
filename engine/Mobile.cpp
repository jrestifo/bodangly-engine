/*
 * Mobile.cpp
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <cmath>

#include "Mobile.h"
#include "SteeringBehavior.h"
#include "EngineMath.h"

class SteeringBehavior;

Mobile::Mobile() {

	_screen = NULL;
	_edgeBehavior = NULL;
	_mass = 1.0;
	_maxSpeed = 10.0;
	_position = Vector2D<Double>(0.0, 0.0);
	_screenPosition = Vector2D<int32_t>(0, 0);
	_velocity = Vector2D<Double>(0.0, 0.0);
	_steeringBehavior = NULL;

}

Mobile::Mobile(const Screen* const screen, const Double& mass,
		const Double& maxSpeed, const Double& rotation,
		const Vector2D<Double>& position,
		const Vector2D<int32_t>& screenPosition,
		const Vector2D<Double>& velocity, const edgeBehavior_t& edgeBehavior,
		const bool& isSteered) {

	_screen = screen;
	_edgeBehavior = new EdgeBehavior(edgeBehavior, this);
	_mass = mass;
	_maxSpeed = maxSpeed;
	_rotation = rotation;
	_position = position;
	_screenPosition = screenPosition;
	_velocity = velocity;
	if (isSteered)
		_steeringBehavior = new SteeringBehavior(this);
	else
		_steeringBehavior = NULL;

}

Mobile::~Mobile() {
	delete _edgeBehavior;
}

void Mobile::update(void) {

	//Ensure velocity is not beyond maxSpeed
	_velocity.truncate(_maxSpeed);

	//Adjust position by velocity
	_position += _velocity;

	//Execute the edge behavior
	_edgeBehavior->execute();

	//Convert internal position to screen coordinates
	_screenPosition = Vector2D<int32_t>(
			(int32_t) rint(_position.getX().getVal()),
			(int32_t) rint(_position.getY().getVal()));

	//Adjust the rotation of the Mobile to match the current velocity
	_rotation = _velocity.getAngle() * 180.0 / M_PI;

}

EdgeBehavior::EdgeBehavior() {
	_behavior = WRAP;
	_parent = NULL;
}

EdgeBehavior::EdgeBehavior(const edgeBehavior_t& behavior, Mobile* parent) {
	_behavior = behavior;
	_parent = parent;
}

EdgeBehavior::~EdgeBehavior() {
}

void EdgeBehavior::execute() {
	switch (_behavior) {

	case WRAP: {
		this->wrap();
		break;
	}

	case BOUNCE: {
		this->bounce();
		break;
	}

	case CONTINUE: {
		this->wrap();
		printf("Warning: CONTINUE edge behavior unimplemented\r\n");
		break;
	}

	default: {
		this->wrap();
		printf("Warning: unenumerated edge behavior: %d\r\n", _behavior);
		break;
	}

	}
}

void EdgeBehavior::bounce() {
	if (_parent->_screen) {
		Vector2D<int32_t> *position = &_parent->_screenPosition;
		Vector2D<Double> *velocity = &_parent->_velocity;

		if (position->getX() > _parent->_screen->getWidth()) {
			position->setX(_parent->_screen->getWidth());
			velocity->setX(velocity->getX() * -1.0);
		} else if (position->getX() < 0) {
			position->setX(0);
			velocity->setX(velocity->getX() * -1.0);
		}

		if (position->getY() > _parent->_screen->getHeight()) {
			position->setY(_parent->_screen->getHeight());
			velocity->setY(velocity->getY() * -1.0);
		} else if (position->getY() < 0) {
			position->setY(0);
			velocity->setY(velocity->getY() * -1.0);
		}
	}
}

void EdgeBehavior::wrap() {
	if (_parent->_screen) {
		Vector2D<int32_t> *position = &_parent->_screenPosition;

		if (position->getX() > _parent->_screen->getWidth())
			position->setX(0);
		if (position->getX() < 0)
			position->setX(_parent->_screen->getWidth());

		if (position->getY() > _parent->_screen->getHeight())
			position->setY(0);
		if (position->getY() < 0)
			position->setY(_parent->_screen->getHeight());
	}
}
