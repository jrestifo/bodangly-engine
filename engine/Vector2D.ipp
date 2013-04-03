/*
 * Vector2D.ipp
 *
 * Implementation file for Vector2D templated class
 *
 *  Created on: Mar 27, 2013
 *      Author: Jordan Restifo
 */

#include <math.h>

template<typename TFloat> Vector2D<TFloat>::Vector2D() {
	_x = 0;
	_y = 0;
}

template<typename TFloat> Vector2D<TFloat>::~Vector2D() {

}

template<typename TFloat> Vector2D<TFloat>::Vector2D(const TFloat& x,
		const TFloat& y) {
	_x = x;
	_y = y;
}

template<typename TFloat> Vector2D<TFloat>& Vector2D<TFloat>::operator=(
		const Vector2D<TFloat>& vecB) {
	_x = vecB._x;
	_y = vecB._y;
	return *this;
}

template<typename TFloat> Vector2D<TFloat> Vector2D<TFloat>::operator+(
		const Vector2D<TFloat>& vecB) const {
	return Vector2D(_x + vecB._x, _y + vecB._y);
}

template<typename TFloat> Vector2D<TFloat>& Vector2D<TFloat>::operator+=(
		const Vector2D<TFloat>& vecB) {
	_x = _x + vecB._x;
	_y = _y + vecB._y;
	return *this;
}

template<typename TFloat> Vector2D<TFloat> Vector2D<TFloat>::operator-(
		const Vector2D<TFloat>& vecB) const {
	return Vector2D(_x - vecB._x, _y - vecB._y);
}

template<typename TFloat> Vector2D<TFloat>& Vector2D<TFloat>::operator-=(
		const Vector2D<TFloat>& vecB) {
	_x = _x - vecB._x;
	_y = _y - vecB._y;
	return *this;
}

template<typename TFloat> Vector2D<TFloat> Vector2D<TFloat>::operator/(
		TFloat val) const {
	return Vector2D(_x / val, _y / val);
}

template<typename TFloat> Vector2D<TFloat>& Vector2D<TFloat>::operator/=(
		TFloat val) {
	_x = _x / val;
	_y = _y / val;
	return *this;
}

template<typename TFloat> Vector2D<TFloat> Vector2D<TFloat>::operator*(
		TFloat val) const {
	return Vector2D(_x * val, _y * val);
}

template<typename TFloat> Vector2D<TFloat>& Vector2D<TFloat>::operator*=(
		TFloat val) {
	_x = _x * val;
	_y = _y * val;
	return *this;
}

template<typename TFloat> bool Vector2D<TFloat>::operator==(
		const Vector2D<TFloat>& vecB) const {
	return (_x == vecB._x && _y == vecB._y);
}

template<typename TFloat> bool Vector2D<TFloat>::operator!=(
		const Vector2D<TFloat>& vecB) const {
	return (_x != vecB._x || _y != vecB._y);
}

template<typename TFloat> void Vector2D<TFloat>::flip() {
	_x = -_x;
	_y = -_y;
}

template<typename TFloat> TFloat Vector2D<TFloat>::getLength() const {
	return (TFloat) sqrt(double((_x * _x) + (_y * _y)));
}

template<typename TFloat> void Vector2D<TFloat>::setLength(const TFloat& val) {
	_x = val * cos(double(getAngle()));
	_x = val * sin(double(getAngle()));
}

template<typename TFloat> TFloat Vector2D<TFloat>::getAngle() const {
	return (TFloat) atan2(_x.getVal(), _y.getVal());
}

template<typename TFloat> void Vector2D<TFloat>::setAngle(const TFloat& val) {
	_x = getLength() * cos(double(val));
	_y = getLength() * sin(double(val));
}

template<typename TFloat> void Vector2D<TFloat>::zero() {
	_x = 0;
	_y = 0;
}

template<typename TFloat> TFloat Vector2D<TFloat>::dotProduct(
		const Vector2D<TFloat>& vecB) const {
	return (_x * vecB._x) + (_y * vecB._y);
}

template<typename TFloat> TFloat Vector2D<TFloat>::crossProduct(
		const Vector2D<TFloat>& vecB) const {
	return (_x * vecB._y) - (_y * vecB._x);
}

template<typename TFloat> TFloat Vector2D<TFloat>::phi(
		const Vector2D<TFloat> &vecB) const {
	Vector2D<TFloat> t_vecA;
	Vector2D<TFloat> t_vecB;

	if (!isNormal()) {
		t_vecA = this;
		t_vecA.normalize();
	}

	if (!&vecB->isNormal()) {
		t_vecB = vecB;
		t_vecB.normalize();
	}

	return acos(t_vecA.dotProduct(t_vecB));
}

template<typename TFloat> TFloat Vector2D<TFloat>::distance(
		const Vector2D<TFloat> &vecB) const {
	TFloat dx = vecB._x - _x;
	TFloat dy = vecB._y - _y;
	return sqrt(double(dx * dx + dy * dy));
}

template<typename TFloat> bool Vector2D<TFloat>::isNormal() const {
	return getLength() == 1.0;
}

template<typename TFloat> void Vector2D<TFloat>::normalize() {
	if (getLength() == 0.0) {
		_x = 1;
	} else {
		TFloat length = getLength();
		_x /= length;
		_y /= length;
	}
}

template<typename TFloat> short Vector2D<TFloat>::sign(
		const Vector2D<TFloat> &vecB) const {
	return (perp()).dotProduct(vecB) < TFloat(0.0) ? -1.0 : 1.0;
}

template<typename TFloat> Vector2D<TFloat> Vector2D<TFloat>::perp() const {
	return Vector2D<TFloat>(_y * -1.0, _x);
}

template<typename TFloat> void Vector2D<TFloat>::truncate(TFloat val) {
	setLength(getLength() < val ? getLength() : val);
}

