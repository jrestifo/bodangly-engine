/*
 * SteeringBehavior.h
 *
 *  Created on: Mar 31, 2013
 *      Author: demian
 */

#ifndef STEERING_H_
#define STEERING_H_
#include "EngineMath.h"
#include <vector>
#include <list>

class Mobile;

class SteeringBehavior {
	friend class Mobile;
public:
	SteeringBehavior();

	SteeringBehavior(Mobile* parent);

	SteeringBehavior(Mobile* parent, const Double& arriveThreshold,
			const Double& avoidBuffer, const Double& avoidDistance,
			const Double& comfortDistance, const Double& maxForce,
			const int32_t& pathIndex, const Double& pathThreshold,
			const Double& viewDistance, const Double& wanderDistance,
			const Double& wanderRadius, const Double& wanderRange,
			const Double& wanderAngle, const Vector2D<Double>& steeringForce);

	virtual ~SteeringBehavior();

	/* Getters/Setters
	 * TODO Finish commenting variables in Steering*/

	//Determines how close is close enough for arrival
	const Double& getApproachDistance() const;
	void setApproachDistance(const Double& approachDistance);

	const Double& getAvoidBuffer() const;
	void setAvoidBuffer(const Double& avoidBuffer);

	const Double& getAvoidDistance() const;
	void setAvoidDistance(const Double& avoidDistance);

	const Double& getComfortDistance() const;
	void setComfortDistance(const Double& comfortDistance);

	const Double& getMaxForce() const;
	void setMaxForce(const Double& maxForce);

	Mobile* getParent() const;
	void setParent(Mobile* parent);

	const uint32_t& getPathIndex() const;
	void setPathIndex(const int32_t& pathIndex);

	const Double& getPathThreshold() const;
	void setPathThreshold(const Double& pathThreshold);

	const Double& getViewDistance() const;
	void setViewDistance(const Double& viewDistance);

	const Double& getWanderDistance() const;
	void setWanderDistance(const Double& wanderDistance);

	const Double& getWanderRadius() const;
	void setWanderRadius(const Double& wanderRadius);

	const Double& getWanderRange() const;
	void setWanderRange(const Double& wanderRange);

	const Double& getWanderAngle() const;
	void setWanderAngle(const Double& wanderAngle);

	const Vector2D<Double>& getSteeringForce() const;
	void setSteeringForce(const Vector2D<Double>& steeringForce);

	void seek(const Vector2D<Double>& v2Target);

	void flee(const Vector2D<Double>& v2Target);

	void approach(const Vector2D<Double>& v2Target);

	void follow(const Mobile* &mobTarget);

	void avoid(const std::vector<Circle>& vCircles);

	void evade(const Mobile* &mobTarget);

	void followPath(const std::vector<Vector2D<Double> >& vv2Path, const bool& loop);

	void flock(const std::list<Mobile *> lstMobs);

	bool isViewable(Mobile* pMob);
private:
	Mobile* _parent;

	Vector2D<Double> _steeringForce;
	Double _approachDistance;

	Double _avoidBuffer;
	Double _avoidDistance;

	Double _viewDistance;

	Double _comfortDistance;

	Double _maxSpeed;
	Double _maxForce;

	uint32_t _pathIndex;
	Double _pathThreshold;

	Double _wanderDistance;
	Double _wanderRadius;
	Double _wanderRange;
	Double _wanderAngle;
};

#endif /* STEERING_H_ */
