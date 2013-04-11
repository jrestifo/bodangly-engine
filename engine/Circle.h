/*
 * Circle.h
 *
 *  Created on: Apr 1, 2013
 *      Author: demian
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "Vector2D.h"
#include "Double.h"

class Circle {
public:
	Circle();
	virtual ~Circle();
	const Vector2D<Double>& getPosition() const;
	void setPosition(const Vector2D<Double>& position);
	const Double& getRadius() const;
	void setRadius(const Double& radius);

private:
	Double _radius;
	Vector2D<Double> _position;
};

#endif /* CIRCLE_H_ */
