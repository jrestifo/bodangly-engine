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
#include "MobileFactory.h"

class SteeringBehavior;

Mobile::Mobile() {
	_id = MobileFactory::instance()->registerMob(this);
	_screen = NULL;
	_edgeBehavior = NULL;
	_mass = 1.0;
	_maxSpeed = 10.0;
	_position = Vector2D<Double>(0.0, 0.0);
	_screenPosition = Vector2D<int32_t>(0, 0);
	_velocity = Vector2D<Double>(0.0, 0.0);
	_steeringBehavior = NULL;
}

Mobile::Mobile(const uint32_t& id, const Screen* const screen, const Double& mass,
		const Double& maxSpeed, const Double& rotation,
		const Vector2D<Double>& position,
		const Vector2D<int32_t>& screenPosition,
		const Vector2D<Double>& velocity, const edgeBehavior_t& edgeBehavior,
		const bool& isSteered) {

	_id = id;
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
	if (_steeringBehavior)
		delete _steeringBehavior;
}

Mobile& Mobile::operator=(const Mobile& mobB) {
	if (this->_id == INVALID_ID)
		_id = MobileFactory::instance()->registerMob(this);
	_screen = mobB._screen;
	_edgeBehavior = new EdgeBehavior(mobB._edgeBehavior->_behavior, this);
	if (mobB._steeringBehavior)
		_steeringBehavior = new SteeringBehavior(
				this,
				mobB._steeringBehavior->_approachDistance,
				mobB._steeringBehavior->_avoidBuffer,
				mobB._steeringBehavior->_avoidDistance,
				mobB._steeringBehavior->_comfortDistance,
				mobB._steeringBehavior->_maxForce,
				mobB._steeringBehavior->_pathIndex,
				mobB._steeringBehavior->_pathThreshold,
				mobB._steeringBehavior->_viewDistance,
				mobB._steeringBehavior->_wanderDistance,
				mobB._steeringBehavior->_wanderRadius,
				mobB._steeringBehavior->_wanderRange,
				mobB._steeringBehavior->_wanderAngle,
				mobB._steeringBehavior->_steeringForce );
	_velocity = mobB._velocity;
	_mass = mobB._mass;
	_position = mobB._position;
	_screenPosition = mobB._screenPosition;
	_rotation = mobB._rotation;
	_maxSpeed = mobB._maxSpeed;
	return *this;
}
Mobile::Mobile(Mobile const& mobB) {
	if (this->_id == INVALID_ID)
		_id = MobileFactory::instance()->registerMob(this);
	_screen = mobB._screen;
	_edgeBehavior = new EdgeBehavior(mobB._edgeBehavior->_behavior, this);
	if (mobB._steeringBehavior)
		_steeringBehavior = new SteeringBehavior(this,
				mobB._steeringBehavior->_approachDistance,
				mobB._steeringBehavior->_avoidBuffer,
				mobB._steeringBehavior->_avoidDistance,
				mobB._steeringBehavior->_comfortDistance,
				mobB._steeringBehavior->_maxForce,
				mobB._steeringBehavior->_pathIndex,
				mobB._steeringBehavior->_pathThreshold,
				mobB._steeringBehavior->_viewDistance,
				mobB._steeringBehavior->_wanderDistance,
				mobB._steeringBehavior->_wanderRadius,
				mobB._steeringBehavior->_wanderRange,
				mobB._steeringBehavior->_wanderAngle,
				mobB._steeringBehavior->_steeringForce);
	_velocity = mobB._velocity;
	_mass = mobB._mass;
	_position = mobB._position;
	_screenPosition = mobB._screenPosition;
	_rotation = mobB._rotation;
	_maxSpeed = mobB._maxSpeed;
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

edgeBehavior_t Mobile::getEdgeBehavior() const {
	return _edgeBehavior->_behavior;
}

void Mobile::setEdgeBehavior(const edgeBehavior_t& edgeBehavior) {
	_edgeBehavior = new EdgeBehavior(edgeBehavior, this);
}

const Double& Mobile::getMass() const {
	return _mass;
}

void Mobile::setMass(const Double& mass) {
	_mass = mass;
}

const Double& Mobile::getMaxSpeed() const {
	return _maxSpeed;
}

void Mobile::setMaxSpeed(const Double& maxSpeed) {
	_maxSpeed = maxSpeed;
}

const Vector2D<Double>& Mobile::getPosition() const {
	return _position;
}

void Mobile::setPosition(const Vector2D<Double>& position) {
	_position = position;
}

const Double& Mobile::getRotation() const {
	return _rotation;
}

void Mobile::setRotation(const Double& rotation) {
	_rotation = rotation;
}

const Screen* Mobile::getScreen() const {
	return _screen;
}

const Vector2D<int32_t>& Mobile::getScreenPosition() const {
	return _screenPosition;
}

SteeringBehavior* Mobile::getSteering() const {
	return _steeringBehavior;
}

const Vector2D<Double>& Mobile::getVelocity() const {
	return _velocity;
}

void Mobile::setVelocity(const Vector2D<Double>& velocity) {
	_velocity = velocity;
}
