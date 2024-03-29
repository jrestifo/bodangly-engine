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
#include <memory>

#include "GameLogic.h"
#include "Mobile.h"
#include "SteeringBehavior.h"
#include "EngineMath.h"
#include "Screen.h"

class SteeringBehavior;

Mobile::Mobile() {
	_id = 0;
	_mass = 1.0;
	_maxSpeed = 10.0;
	_position = Vector2D<Double>(0.0, 0.0);
	_screenPosition = Vector2D<int32_t>(0, 0);
	_velocity = Vector2D<Double>(0.0, 0.0);
}

Mobile::Mobile(const Double& mass, const Double& maxSpeed,
		const Double& rotation, const Vector2D<Double>& position,
		const Vector2D<int32_t>& screenPosition,
		const Vector2D<Double>& velocity) {

	_id = 0;
	_mass = mass;
	_maxSpeed = maxSpeed;
	_rotation = rotation;
	_position = position;
	_screenPosition = screenPosition;
	_velocity = velocity;
}

Mobile::~Mobile() {
}

Mobile& Mobile::operator=(const Mobile& mobB) {
	std::weak_ptr<Mobile> wptr(GameLogic::instance()->findMob(this->_id));
	_edgeBehavior = std::shared_ptr<EdgeBehavior>(
			new EdgeBehavior(mobB._edgeBehavior->_behavior, wptr));

	if (mobB._steeringBehavior)
		_steeringBehavior = std::shared_ptr<SteeringBehavior>(
				new SteeringBehavior(wptr,
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
						mobB._steeringBehavior->_steeringForce));
	_velocity = mobB._velocity;
	_mass = mobB._mass;
	_position = mobB._position;
	_screenPosition = mobB._screenPosition;
	_rotation = mobB._rotation;
	_maxSpeed = mobB._maxSpeed;
	return *this;
}
Mobile::Mobile(Mobile const& mobB) {
	std::weak_ptr<Mobile> wptr(GameLogic::instance()->findMob(this->_id));
	_edgeBehavior = std::shared_ptr<EdgeBehavior>(
			new EdgeBehavior(mobB._edgeBehavior->_behavior, wptr));

	if (mobB._steeringBehavior)
		_steeringBehavior = std::shared_ptr<SteeringBehavior>(
				new SteeringBehavior(wptr,
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
						mobB._steeringBehavior->_steeringForce));
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
}

EdgeBehavior::EdgeBehavior(const edgeBehavior_t& behavior, std::weak_ptr<Mobile> parent) {
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
	try {
		auto parent = _parent.lock();
		if (Screen::instance()) {
			Vector2D<int32_t> *position = &parent->_screenPosition;
			Vector2D<Double> *velocity = &parent->_velocity;

			if (position->getX() > Screen::instance()->getWidth()) {
				position->setX(Screen::instance()->getWidth());
				velocity->setX(velocity->getX() * -1.0);
			} else if (position->getX() < 0) {
				position->setX(0);
				velocity->setX(velocity->getX() * -1.0);
			}

			if (position->getY() > Screen::instance()->getHeight()) {
				position->setY(Screen::instance()->getHeight());
				velocity->setY(velocity->getY() * -1.0);
			} else if (position->getY() < 0) {
				position->setY(0);
				velocity->setY(velocity->getY() * -1.0);
			}
		}
	} catch (std::bad_weak_ptr bad) {
		//TODO Implement behavior for when the weak pointer holds an expired pointer
	}
}

void EdgeBehavior::wrap() {
	try {
		auto parent = _parent.lock();
		if (Screen::instance()) {
			Vector2D<int32_t> *position = &parent->_screenPosition;

			if (position->getX() > Screen::instance()->getWidth())
				position->setX(0);
			if (position->getX() < 0)
				position->setX(Screen::instance()->getWidth());

			if (position->getY() > Screen::instance()->getHeight())
				position->setY(0);
			if (position->getY() < 0)
				position->setY(Screen::instance()->getHeight());
		}
	} catch (std::bad_weak_ptr bad) {
		//TODO Implement behavior for when the weak pointer holds an expired pointer
	}
}

edgeBehavior_t Mobile::getEdgeBehavior() const {
	return _edgeBehavior->_behavior;
}

void Mobile::setEdgeBehavior(const edgeBehavior_t& edgeBehavior) {
	if (_edgeBehavior.get())
		_edgeBehavior.get()->_behavior = edgeBehavior;
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

const Vector2D<int32_t>& Mobile::getScreenPosition() const {
	return _screenPosition;
}

std::weak_ptr<SteeringBehavior> Mobile::getSteering() const {
	return _steeringBehavior;
}

const Vector2D<Double>& Mobile::getVelocity() const {
	return _velocity;
}

void Mobile::setVelocity(const Vector2D<Double>& velocity) {
	_velocity = velocity;
}
