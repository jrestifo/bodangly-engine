/*
 * Vector2D.h
 *
 *  Created on: Mar 27, 2013
 *      Author: demian
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_
#include <iostream>

template<typename TFloat> class Vector2D {

public:
	Vector2D();
	Vector2D(const TFloat& x, const TFloat& y);
	virtual ~Vector2D();

	/* Operator overloads applicable to a Vector2D */

	Vector2D& operator=(const Vector2D& vecB);

	Vector2D operator+(const Vector2D& vecB) const;
	Vector2D& operator+=(const Vector2D& vecB);
	Vector2D operator-(const Vector2D& vecB) const;
	Vector2D& operator-=(const Vector2D& vecB);

	Vector2D operator/(TFloat val) const;
	Vector2D& operator/=(TFloat val);
	Vector2D operator*(TFloat val) const;
	Vector2D& operator*=(TFloat val);

	bool operator==(const Vector2D& vecB) const;
	bool operator!=(const Vector2D& vecB) const;

	/* Reverses the vector direction */
	void flip();

	TFloat getX() {
		return _x;
	}

	void setX(const TFloat& x) {
		_x = x;
	}

	TFloat getY() {
		return _y;
	}

	void setY(const TFloat& y) {
		_y = y;
	}

	/* Function: getLength
	 * Returns the length of this vector
	 */
	TFloat getLength() const;

	/* Function: setLength
	 * Sets the length of this vector
	 */
	void setLength(const TFloat& val);

	/* Function: getLength
	 * Returns the angle of this vector
	 */
	TFloat getAngle() const;

	/* Function: setLength
	 * Sets the angle of this vector
	 */
	void setAngle(const TFloat& val);

	/* Function: zero
	 * Sets the x and y components to zero
	 */
	void zero();

	/* Function: dotProduct
	 * Returns the dot product of this and a given Vector2D
	 */
	TFloat dotProduct(const Vector2D &vecB) const;

	/* Function: crossProduct
	 * Returns the cross product of this and a given Vector2D
	 */
	TFloat crossProduct(const Vector2D &vecB) const;

	/* Function: phi
	 * Returns phi, the angle between this and a given Vector2D
	 */
	TFloat phi(const Vector2D &vecB) const;

	/* Function: distance
	 * Returns the distance between this and a given Vector2D
	 */
	TFloat distance(const Vector2D &vecB) const;

	/* Function: isNormal
	 * Returns true if this Vector2D is normalized, false otherwise
	 */
	bool isNormal() const;

	/* Function: normalize
	 * Normalizes this vector (sets it to unit length)
	 */
	void normalize();

	/* Function: getSign
	 * Returns -1 if the given Vector2D is left of this, 1 if it is right of this
	 */
	short sign(const Vector2D &vecB) const;

	/* Function: perp
	 * Returns a Vector2D perpendicular to this one
	 */
	Vector2D perp() const;

	/* Function: truncate
	 * Truncates the vector to the given length
	 */
	void truncate(TFloat length);

	friend std::ostream& operator<<(std::ostream &os, const Vector2D &vec) {
		os << "(" << vec._x << "," << vec._y << ")";
		return os;
	}
private:
	TFloat _x;
	TFloat _y;

};

#include "Vector2D.ipp"

#endif /* VECTOR2D_H_ */
