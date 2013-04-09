/*
 * SteeringBehavior.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: demian
 */
#include <cmath>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <cstdio>
#include <vector>

#include "SteeringBehavior.h"
#include "Mobile.h"
#include "Log.h"

//These behaviors are mostly re-implemented from
//AdvancED ActionScript 3.0 Animation by Keith Peters
//TODO Implement time-based integration
//TODO Comment SteeringBehaviors
//TODO Change steering behaviors to all accept weak_ptr's

class Mobile;

SteeringBehavior::SteeringBehavior() {
//	_parent = NULL;
	_maxForce = 1.0;
	_steeringForce = Vector2D<Double>(0, 0);
	_approachDistance = 100.0;
	_wanderAngle = 0.0;
	_wanderDistance = 10.0;
	_wanderRadius = 5.0;
	_wanderRange = 1.0;
	_pathIndex = 0;
	_pathThreshold = 20.0;
	_avoidDistance = 300.0;
	_avoidBuffer = 20.0;
	_viewDistance = 200.0;
	_comfortDistance = 60.0;
}

SteeringBehavior::SteeringBehavior(std::weak_ptr<Mobile> parent) {
	_parent = parent;
	_approachDistance = 100.0;
	_avoidBuffer = 20.0;
	_avoidDistance = 300.0;
	_comfortDistance = 60.0;
	_maxForce = 1.0;
	_pathIndex = 0;
	_pathThreshold = 20.0;
	_viewDistance = 200.0;
	_wanderDistance = 10.0;
	_wanderRadius = 5.0;
	_wanderRange = 1.0;
	_wanderAngle = 0.0;
	_steeringForce = Vector2D<Double>(0.0, 0.0);
}

SteeringBehavior::SteeringBehavior(std::weak_ptr<Mobile> parent,
		const Double& approachDistance, const Double& avoidBuffer,
		const Double& avoidDistance, const Double& comfortDistance,
		const Double& maxForce, const int32_t& pathIndex,
		const Double& pathThreshold, const Double& viewDistance,
		const Double& wanderDistance, const Double& wanderRadius,
		const Double& wanderRange, const Double& wanderAngle,
		const Vector2D<Double>& steeringForce) {
	_parent = parent;
	_approachDistance = approachDistance;
	_avoidBuffer = avoidBuffer;
	_avoidDistance = avoidDistance;
	_comfortDistance = comfortDistance;
	_maxForce = maxForce;
	_pathIndex = pathIndex;
	_pathThreshold = pathThreshold;
	_viewDistance = viewDistance;
	_wanderDistance = wanderDistance;
	_wanderRadius = wanderRadius;
	_wanderRange = wanderRange;
	_wanderAngle = wanderAngle;
	_steeringForce = steeringForce;
}

SteeringBehavior::~SteeringBehavior() {
}

/* Getters/Setters */

const Vector2D<Double>& SteeringBehavior::getSteeringForce() const {
	return _steeringForce;
}

void SteeringBehavior::setSteeringForce(const Vector2D<Double>& steeringForce) {
	_steeringForce = steeringForce;
}

const Double& SteeringBehavior::getApproachDistance() const {
	return _approachDistance;
}

void SteeringBehavior::setApproachDistance(const Double& approachDistance) {
	_approachDistance = approachDistance;
}

const Double& SteeringBehavior::getAvoidBuffer() const {
	return _avoidBuffer;
}

void SteeringBehavior::setAvoidBuffer(const Double& avoidBuffer) {
	_avoidBuffer = avoidBuffer;
}

const Double& SteeringBehavior::getAvoidDistance() const {
	return _avoidDistance;
}

void SteeringBehavior::setAvoidDistance(const Double& avoidDistance) {
	_avoidDistance = avoidDistance;
}

const Double& SteeringBehavior::getComfortDistance() const {
	return _comfortDistance;
}

void SteeringBehavior::setComfortDistance(const Double& comfortDistance) {
	_comfortDistance = comfortDistance;
}

const Double& SteeringBehavior::getMaxForce() const {
	return _maxForce;
}

void SteeringBehavior::setMaxForce(const Double& maxForce) {
	_maxForce = maxForce;
}

std::weak_ptr<Mobile> SteeringBehavior::getParent() const {
	return _parent;
}

void SteeringBehavior::setParent(std::weak_ptr<Mobile> parent) {
	_parent = parent;
}

const uint32_t& SteeringBehavior::getPathIndex() const {
	return _pathIndex;
}

void SteeringBehavior::setPathIndex(const int32_t& pathIndex) {
	_pathIndex = pathIndex;
}

const Double& SteeringBehavior::getPathThreshold() const {
	return _pathThreshold;
}

void SteeringBehavior::setPathThreshold(const Double& pathThreshold) {
	_pathThreshold = pathThreshold;
}

const Double& SteeringBehavior::getViewDistance() const {
	return _viewDistance;
}

void SteeringBehavior::setViewDistance(const Double& viewDistance) {
	_viewDistance = viewDistance;
}

const Double& SteeringBehavior::getWanderDistance() const {
	return _wanderDistance;
}

void SteeringBehavior::setWanderDistance(const Double& wanderDistance) {
	_wanderDistance = wanderDistance;
}

const Double& SteeringBehavior::getWanderRadius() const {
	return _wanderRadius;
}

void SteeringBehavior::setWanderRadius(const Double& wanderRadius) {
	_wanderRadius = wanderRadius;
}

const Double& SteeringBehavior::getWanderRange() const {
	return _wanderRange;
}

void SteeringBehavior::setWanderRange(const Double& wanderRange) {
	_wanderRange = wanderRange;
}

const Double& SteeringBehavior::getWanderAngle() const {
	return _wanderAngle;
}

void SteeringBehavior::setWanderAngle(const Double& wanderAngle) {
	_wanderAngle = wanderAngle;
}

/* Behavior Functions */

void SteeringBehavior::seek(const Vector2D<Double>& v2Target) {
	try {
		auto parent = _parent.lock();
		Vector2D<Double> desiredVelocity = v2Target - parent->_position;
		desiredVelocity.normalize();
		desiredVelocity *= _maxSpeed;
		_steeringForce += desiredVelocity - parent->_velocity;
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior seek: ").append(bad.what()));
	}
}

void SteeringBehavior::flee(const Vector2D<Double>& v2Target) {
	try {
		auto parent = _parent.lock();
		Vector2D<Double> desiredVelocity = v2Target - parent->_position;
		desiredVelocity.normalize();
		desiredVelocity *= _maxSpeed;
		_steeringForce -= desiredVelocity - parent->_velocity;
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior flee: ").append(bad.what()));
	}
}

void SteeringBehavior::approach(const Vector2D<Double>& v2Target) {
	try {
		auto parent = _parent.lock();
		Vector2D<Double> desiredVelocity = v2Target - parent->_position;
		desiredVelocity.normalize();
		Double distance = parent->_position.distance(v2Target);
		if (distance > _approachDistance) {
			desiredVelocity *= _maxSpeed;
		} else {
			desiredVelocity *= (_maxSpeed * distance / _approachDistance);
		}
		_steeringForce += desiredVelocity - parent->_velocity;
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior approach: ").append(bad.what()));
	}
}

void SteeringBehavior::follow(const Mobile* &mobTarget) {
	try {
		auto parent = _parent.lock();
		Double projectionDistance = parent->_position.distance(
				mobTarget->_position) / _maxSpeed;
		Vector2D<Double> projectedTarget = mobTarget->_position
				+ (mobTarget->_velocity * projectionDistance);
		seek(projectedTarget);
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior follow: ").append(bad.what()));
	}

}

void SteeringBehavior::evade(const Mobile* &mobTarget) {
	try {
		auto parent = _parent.lock();
		Double projectionDistance = parent->_position.distance(
				mobTarget->_position) / _maxSpeed;
		Vector2D<Double> projectedTarget = mobTarget->_position
				- (mobTarget->_velocity * projectionDistance);
		flee(projectedTarget);
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior evade: ").append(bad.what()));
	}

}

void SteeringBehavior::avoid(const std::vector<Circle>& vCircles) {
	try {
		auto parent = _parent.lock();
		std::vector<Circle>::const_iterator ciiCircle;
		for (ciiCircle = vCircles.begin(); ciiCircle != vCircles.end();
				ciiCircle++) {
			Vector2D<Double> heading = parent->_velocity;
			heading.normalize();

			// Create a vector between the circle and our Mobile
			Vector2D<Double> difference = ciiCircle->getPosition()
					- parent->_position;
			Double differenceDotProduct = difference.dotProduct(heading);

			//Make sure circle is in front of our Mobile
			if (differenceDotProduct > 0.0) {
				Vector2D<Double> feeler = heading * _avoidDistance;

				//Project the difference on to the feeler arm
				Vector2D<Double> projection = heading * differenceDotProduct;

				//Distance from the circle to the feeler arm
				Double distanceToFeeler = (projection - difference).getLength();

				//If feeler intersects circle plus our buffer zone, and projections
				//is less than the feeler length, collision will occur - so steer away
				if (distanceToFeeler < ciiCircle->getRadius() + _avoidBuffer
						&& projection.getLength() < feeler.getLength()) {

					//Get a force that is 90 degrees from this vector to a circle
					Vector2D<Double> force = heading * _maxSpeed;
					force.setAngle(
							force.getAngle()
									+ (difference.sign(parent->_velocity) * M_PI
											/ 2.0));

					//Scale the force by the distance to the circle, inversely proportionate
					force *= Double(1.0)
							- projection.getLength() / feeler.getLength();

					//Adjust our steering
					_steeringForce += force;

					//Apply braking
					parent->_velocity *= projection.getLength()
							/ feeler.getLength();
				}
			}
		}
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior avoid: ").append(bad.what()));
	}
}

void SteeringBehavior::followPath(const std::vector<Vector2D<Double> >& vPath,
		const bool& loop) {
	try {
		auto parent = _parent.lock();
		Vector2D<Double> waypoint;
		if (vPath.size() > _pathIndex)
			waypoint = vPath[_pathIndex];

		if (parent->_position.distance(waypoint) < _pathThreshold) {
			if (_pathIndex > vPath.size()) {
				if (loop)
					_pathIndex = 0;
			} else
				_pathIndex++;
		}

		if (_pathIndex > vPath.size() && !loop)
			approach(waypoint);
		else
			seek(waypoint);
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior followPath: ").append(
						bad.what()));
	}
}

void SteeringBehavior::flock(std::list<Mobile *> lstMobs) {
	//TODO Change flock to accept a list of weak_ptr
	try {
		auto parent = _parent.lock();
		Vector2D<Double> averageVelocity = parent->_velocity;
		Vector2D<Double> averagePosition = Vector2D<Double>();
		uint32_t viewCount = 0;

		std::list<Mobile *>::const_iterator ciiMobile;
		for (ciiMobile = lstMobs.begin(); ciiMobile != lstMobs.end();
				ciiMobile++) {
			if ((*ciiMobile)->getId() != parent->getId()
					&& isViewable((*ciiMobile))) {
				averageVelocity += (*ciiMobile)->getVelocity();
				averagePosition += (*ciiMobile)->getPosition();
				if (isTooClose((*ciiMobile)))
					flee((*ciiMobile)->_position);
				viewCount++;
			}
		}

		if (viewCount > 0) {
			averageVelocity /= viewCount;
			averagePosition /= viewCount;
			seek(averagePosition);
			_steeringForce += averageVelocity - parent->_velocity;
		}
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior flock: ").append(bad.what()));
	}

}

bool SteeringBehavior::isViewable(Mobile* pMob) {
	try {
		auto parent = _parent.lock();
		if (parent->_position.distance(pMob->_position) > _viewDistance)
			return false;
		Vector2D<Double> heading = parent->_velocity;
		heading.normalize();
		Vector2D<Double> difference = pMob->_position - parent->_position;
		Double dotProduct = difference.dotProduct(heading);
		if (dotProduct < 0.0)
			return true;
		return false;
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior isViewable: ").append(
						bad.what()));
	}
}

bool SteeringBehavior::isTooClose(Mobile* pMob) {
	try {
		auto parent = _parent.lock();
		return parent->_position.distance(pMob->_position) < _comfortDistance;
	} catch (const std::bad_weak_ptr& bad) {
		Log::instance()->postError(
				std::string("SteeringBehavior isTooClose: ").append(
						bad.what()));
	}
}
