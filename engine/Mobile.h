/*
 * Mobile.h
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */
#ifndef MOBILE_H_
#define MOBILE_H_

#include <memory>

#include "EngineMath.h"
#include "Screen.h"
#include "enum_edgeBehaviors.h"

class EdgeBehavior;
class SteeringBehavior;
class MobileFactory;

class Mobile {
	friend class MobileFactory;
	friend class EdgeBehavior;
	friend class SteeringBehavior;

public:

	virtual ~Mobile();

	void update();

	Mobile& operator=(const Mobile& mobB);
	Mobile operator==(const Mobile& mobB) const;
	Mobile operator<(const Mobile& mobB) const;

	edgeBehavior_t getEdgeBehavior() const;
	void setEdgeBehavior(const edgeBehavior_t& edgeBehavior);

	const Double& getMass() const;
	void setMass(const Double& mass);

	const Double& getMaxSpeed() const;
	void setMaxSpeed(const Double& maxSpeed);

	const Vector2D<Double>& getPosition() const;
	void setPosition(const Vector2D<Double>& position);

	const Double& getRotation() const;
	void setRotation(const Double& rotation);

	const Vector2D<int32_t>& getScreenPosition() const;

	std::weak_ptr<SteeringBehavior> getSteering() const;

	const Vector2D<Double>& getVelocity() const;
	void setVelocity(const Vector2D<Double>& velocity);

	uint32_t getId() const {
		return _id;
	}

private:
	Mobile();
	Mobile(Mobile const& mobB);

	Mobile( const Double& mass,
			const Double& maxSpeed, const Double& rotation,
			const Vector2D<Double>& position,
			const Vector2D<int32_t>& screenPosition,
			const Vector2D<Double>& velocity,
			const edgeBehavior_t& edgeBehavior, const bool& isSteered);

	uint32_t _id;
	Double _mass;
	Double _maxSpeed;
	Double _rotation;

	Vector2D<Double> _position;
	Vector2D<int32_t> _screenPosition;
	Vector2D<Double> _velocity;

	std::shared_ptr<EdgeBehavior> _edgeBehavior;
	std::shared_ptr<SteeringBehavior> _steeringBehavior;
};

//Determines how the Mobile should act when hitting the edge of the screen
class EdgeBehavior {
	friend class Mobile;
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
