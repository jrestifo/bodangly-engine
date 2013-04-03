/*
 * Mobile.h
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */
#ifndef MOBILE_H_
#define MOBILE_H_

#include "EngineMath.h"
#include "Screen.h"
#include "enum_edgeBehaviors.h"

class EdgeBehavior;
class SteeringBehavior;

class Mobile {
	friend class EdgeBehavior;
	friend class SteeringBehavior;

public:
	Mobile();

	Mobile(const Screen* const screen, const Double& mass,
			const Double& maxSpeed, const Double& rotation,
			const Vector2D<Double>& position,
			const Vector2D<int32_t>& screenPosition,
			const Vector2D<Double>& velocity,
			const edgeBehavior_t& edgeBehavior, const bool& isSteered);

	virtual ~Mobile();

	void update();

	const Screen* _screen;

	Double _mass;
	Double _maxSpeed;
	Double _rotation;

	Vector2D<Double> _position;
	Vector2D<int32_t> _screenPosition;
	Vector2D<Double> _velocity;

	EdgeBehavior* _edgeBehavior;
	SteeringBehavior* _steeringBehavior;
};

//Determines how the Mobile should act when hitting the edge of the screen
class EdgeBehavior {
public:
	EdgeBehavior();
	EdgeBehavior(const edgeBehavior_t& behavior, Mobile* parent);

	virtual ~EdgeBehavior();

	void execute();

private:
	Mobile* _parent;
	edgeBehavior_t _behavior;

	void bounce(void);
	void wrap(void);
};

#endif /* MOBILE_H_ */
