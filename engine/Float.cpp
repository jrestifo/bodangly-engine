/*
 * Float.cpp
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */

#include "Float.h"
#include <assert.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>

Float::Float() {
	 assert(EPSILONF > 0 && EPSILONF < 4 * 1024 * 1024);
	_val = 0;
}

Float::Float(const float& val) {
	assert(EPSILONF > 0 && EPSILONF < 4 * 1024 * 1024);
	_val = val;
}

Float::~Float() {
}

/* Assignments
 * Float -> Float
 */
Float& Float::operator=(const Float& flB) {
	_val = flB._val;
	return *this;
}

/* Math operations
 * Float -> Float
 */
Float Float::operator+(const Float& flB) const {
	return Float(_val + flB._val);
}

Float& Float::operator+=(const Float& flB) {
	_val = _val + flB._val;
	return *this;
}

Float Float::operator-(const Float& flB) const {
	return Float(_val - flB._val);
}

Float& Float::operator-=(const Float& flB) {
	_val = _val - flB._val;
	return *this;
}

Float Float::operator/(const Float& flB) const {
	return Float(_val / flB._val);
}

Float& Float::operator/=(const Float& flB) {
	_val = _val / flB._val;
	return *this;
}

Float Float::operator*(const Float& flB) const {
	return Float(_val * flB._val);
}

Float& Float::operator*=(const Float& flB) {
	_val = _val * flB._val;
	return *this;
}

/* Handles the core of the float comparison algorithm as discussed at
 * http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */

inline bool Float::almostEqualAbs(const float& flB) const {
	// Check if the numbers are really close -- needed
	// when comparing numbers near zero.
	float absDiff = fabs(_val - flB);
	if (absDiff <= DBL_EPSILON)
		return true;
	return false;
}

inline bool Float::almostEqualUlps(Float_t& uA,  Float_t& uB, int* ulpsDiff) const {

	// Different signs means they do not match.
	if (uA.isNegative() != uB.isNegative()) {
		// Check for equality to make sure +0==-0
		if (_val == uB.f)
			return true;
		return false;
	}

	// Find the difference in ULPs.
	*ulpsDiff = abs(uA.i - uB.i);
	if (*ulpsDiff <= _maxUlpsDiff)
		return true;

	return false;
}

/* Comparison Overloads
 * Float <-> Float
 */



bool Float::operator==(const Float& flB) const {
	if (almostEqualAbs(flB._val))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB._val);
	return almostEqualUlps(uA, uB, &ulpsDiff);
}



bool Float::operator!=(const Float& flB) const {
	if (*this == flB)
		return false;
	return true;
}

bool Float::operator<=(const Float& flB) const {
	if (almostEqualAbs(flB._val))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Float::operator<(const Float& flB) const {
	if (almostEqualAbs(flB._val))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Float::operator>=(const Float& flB) const {
	if (almostEqualAbs(flB._val))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i > uB.i)
		return true;
	return false;
}

bool Float::operator>(const Float& flB) const {
	if (almostEqualAbs(flB._val))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i > uB.i)
		return true;
	return false;
}

/* Assignment
 * float -> Float
 */

Float& Float::operator=(const float& flB) {
	_val = flB;
	return *this;
}

/* Math operations
 * float -> Float
 */
Float Float::operator+(const float& flB) const {
	return Float(_val + flB);
}

Float& Float::operator+=(const float& flB) {
	_val = _val + flB;
	return *this;
}

Float Float::operator-(const float& flB) const {
	return Float(_val - flB);
}

Float& Float::operator-=(const float& flB) {
	_val = _val - flB;
	return *this;
}

Float Float::operator/(const float& flB) const {
	return Float(_val / flB);
}

Float& Float::operator/=(const float& flB) {
	_val = _val / flB;
	return *this;
}

Float Float::operator*(const float& flB) const {
	return Float(_val * flB);
}

Float& Float::operator*=(const float& flB) {
	_val = _val * flB;
	return *this;
}

/* Comparison Overloads
 * Float -> float
 */

bool Float::operator==(const float& flB) const {
	if (almostEqualAbs(flB))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB);
	return almostEqualUlps(uA, uB, &ulpsDiff);
}

bool Float::operator!=(const float& flB) const {
	if (*this == flB)
		return false;
	return true;
}

bool Float::operator<=(const float& flB) const {
	if (almostEqualAbs(flB))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Float::operator<(const float& flB) const {
	if (almostEqualAbs(flB))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Float::operator>=(const float& flB) const {
	if (almostEqualAbs(flB))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i > uB.i)
		return true;
	return false;
}

bool Float::operator>(const float& flB) const {
	if (almostEqualAbs(flB))
		return true;
	int ulpsDiff;
	Float_t uA(_val);
	Float_t uB(flB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i > uB.i)
		return true;
	return false;
}

/* Cast Overloads */
Float::operator double() const {
	return (double)_val;
}

Float::operator float() const {
	return _val;
}

/* Getters/Setters */
void Float::setVal(const float& val) {
	_val = val;
}

const float& Float::getVal() const {
	return _val;
}
