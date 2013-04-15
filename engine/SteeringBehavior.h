/*
 * SteeringBehavior.h
 *
 *  Created on: Mar 31, 2013
 *      Author: demian
 */

#ifndef STEERING_H_
#define STEERING_H_

#include <vector>
#include <list>
#include <memory>
#include <tcl.h>

#include "EngineMath.h"

class Mobile;

class SteeringBehavior {
	friend class Mobile;
public:
	SteeringBehavior();

	SteeringBehavior(std::weak_ptr<Mobile> parent);

	SteeringBehavior(std::weak_ptr<Mobile> parent, const Double& approachDistance,
			const Double& avoidBuffer, const Double& avoidDistance,
			const Double& comfortDistance, const Double& maxForce,
			const int32_t& pathIndex, const Double& pathThreshold,
			const Double& viewDistance, const Double& wanderDistance,
			const Double& wanderRadius, const Double& wanderRange,
			const Double& wanderAngle, const Vector2D<Double>& steeringForce);

	virtual ~SteeringBehavior();

	/* Getters/Setters
	 * TODO Finish commenting variables in Steering
	 * */

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

	std::weak_ptr<Mobile> getParent() const;
	void setParent(std::weak_ptr<Mobile> parent);

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

	void followPath(const std::vector<Vector2D<Double> >& vv2Path,
			const bool& loop);

	void flock(const std::list<Mobile *> lstMobs);

	bool isViewable(Mobile* pMob);

	bool isTooClose(Mobile* pMob);

private:
	std::weak_ptr<Mobile> _parent;

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

/* Tcl steering behaviors cannot be class member functions */
//TODO Implement proper namespace for Tcl steering behaviors
int seekTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int fleeTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int approachTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int followTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int avoidTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int evadeTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int followPathTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int flockTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
//TODO these boolean functions are intermediates and perhaps should be implemented within Tcl rather than crossing the C/Tcl barrier
int isViewableTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
int isTooCloseTcl(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);

#endif /* STEERING_H_ */
