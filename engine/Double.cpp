/*
 * Double.cpp
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */

#include "Double.h"
#include <assert.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>

Double::Double() {
	 assert(EPSILOND > 0 && EPSILOND < 2251799813685248);
	_val = 0;
}

Double::Double(const double& val) {
	assert(EPSILOND > 0 && EPSILOND < 2251799813685248);
	_val = val;
}

Double::~Double() {
}

/* Assignments
 * Double -> Double
 * = preserves the original epsilon
 * clone does not
 */

Double& Double::operator=(const Double& dblB) {
	_val = dblB._val;
	return *this;
}

/* Math operations
 * Double -> Double
 */
Double Double::operator+(const Double& dblB) const {
	return Double(_val + dblB._val);
}

Double& Double::operator+=(const Double& dblB) {
	_val = _val + dblB._val;
	return *this;
}

Double Double::operator-(const Double& dblB) const {
	return Double(_val - dblB._val);
}

Double& Double::operator-=(const Double& dblB) {
	_val = _val - dblB._val;
	return *this;
}

Double Double::operator/(const Double& dblB) const {
	return Double(_val / dblB._val);
}

Double& Double::operator/=(const Double& dblB) {
	_val = _val / dblB._val;
	return *this;
}

Double Double::operator*(const Double& dblB) const {
	return Double(_val * dblB._val);
}

Double& Double::operator*=(const Double& dblB) {
	_val = _val * dblB._val;
	return *this;
}

/* Handles the core of the double comparison algorithm as discussed at
 * http://randomascii.wordpress.com/2012/02/25/comparing-doubleing-point-numbers-2012-edition/
 */

inline bool Double::almostEqualAbs(const double& dblB) const {
	// Check if the numbers are really close -- needed
	// when comparing numbers near zero.
	double absDiff = fabs(_val - dblB);
	if (absDiff <= DBL_EPSILON)
		return true;
	return false;
}

inline bool Double::almostEqualUlps( Double_t& uA,  Double_t& uB, int* ulpsDiff) const {

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
 * Double <-> Double
 * Core of the algorithm taken from:
 * http://www.cygnus-software.com/papers/comparingdoubles/comparingdoubles.htm
 */



bool Double::operator==(const Double& dblB) const {
	if (almostEqualAbs(dblB._val))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB._val);
	return almostEqualUlps(uA, uB, &ulpsDiff);
}



bool Double::operator!=(const Double& dblB) const {
	if (*this == dblB)
		return false;
	return true;
}

bool Double::operator<=(const Double& dblB) const {
	if (almostEqualAbs(dblB._val))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Double::operator<(const Double& dblB) const {
	if (almostEqualAbs(dblB._val))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Double::operator>=(const Double& dblB) const {
	if (almostEqualAbs(dblB._val))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i > uB.i)
		return true;
	return false;
}

bool Double::operator>(const Double& dblB) const {
	if (almostEqualAbs(dblB._val))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB._val);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i > uB.i)
		return true;
	return false;
}

/* Assignment
 * double -> Double
 */

Double& Double::operator=(const double& dblB) {
	_val = dblB;
	return *this;
}

/* Math operations
 * double -> Double
 */
Double Double::operator+(const double& dblB) const {
	return Double(_val + dblB);
}

Double& Double::operator+=(const double& dblB) {
	_val = _val + dblB;
	return *this;
}

Double Double::operator-(const double& dblB) const {
	return Double(_val - dblB);
}

Double& Double::operator-=(const double& dblB) {
	_val = _val - dblB;
	return *this;
}

Double Double::operator/(const double& dblB) const {
	return Double(_val / dblB);
}

Double& Double::operator/=(const double& dblB) {
	_val = _val / dblB;
	return *this;
}

Double Double::operator*(const double& dblB) const {
	return Double(_val * dblB);
}

Double& Double::operator*=(const double& dblB) {
	_val = _val * dblB;
	return *this;
}

/* Comparison Overloads
 * Double -> double
 */

bool Double::operator==(const double& dblB) const {
	if (almostEqualAbs(dblB))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB);
	return almostEqualUlps(uA, uB, &ulpsDiff);
}

bool Double::operator!=(const double& dblB) const {
	if (*this == dblB)
		return false;
	return true;
}

bool Double::operator<=(const double& dblB) const {
	if (almostEqualAbs(dblB))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Double::operator<(const double& dblB) const {
	if (almostEqualAbs(dblB))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i < uB.i)
		return true;
	return false;
}

bool Double::operator>=(const double& dblB) const {
	if (almostEqualAbs(dblB))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return ret;
	if (uA.i > uB.i)
		return true;
	return false;
}

bool Double::operator>(const double& dblB) const {
	if (almostEqualAbs(dblB))
		return true;
	int ulpsDiff;
	Double_t uA(_val);
	Double_t uB(dblB);
	bool ret = almostEqualUlps(uA, uB, &ulpsDiff);
	if (ret)
		return false;
	if (uA.i > uB.i)
		return true;
	return false;
}

/* Cast Overloads */
Double::operator double() const {
	return _val;
}

Double::operator float() const {
	return (float) _val;
}

/* Getters/Setters */
void Double::setVal(const double& val) {
	_val = val;
}

const double& Double::getVal() const {
	return _val;
}
