/*
 * Float.h
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */

#ifndef FLOAT_H_
#define FLOAT_H_
#define EPSILONF 1000
#include <iostream>

union Float_t {
	Float_t(float num = 0.0) :
			f(num) {
	}
	// Portable extraction of components.
	bool isNegative() const {
		return (i >> 31) != 0;
	}
	int32_t RawMantissa() const {
		return i & ((1 << 23) - 1);
	}
	int32_t RawExponent() const {
		return (i >> 23) & 0xFF;
	}

	int64_t i;
	float f;
#ifdef _DEBUG
	struct
	{   // Bitfields for exploration. Do not use in production code.
		uint32_t mantissa : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;
	}parts;
#endif
};

class Float {
public:
	Float();
	Float(const float& val);
	virtual ~Float();

	Float& operator=(const Float& flB);
	Float& clone(const Float& flB);

	Float operator+(const Float& flB) const;
	Float& operator+=(const Float& flB);
	Float operator-(const Float& flB) const;
	Float& operator-=(const Float& flB);
	Float operator/(const Float& flB) const;
	Float& operator/=(const Float& flB);
	Float operator*(const Float& flB) const;
	Float& operator*=(const Float& flB);

	bool operator==(const Float& flB) const;
	bool operator!=(const Float& flB) const;
	bool operator<=(const Float& flB) const;
	bool operator<(const Float& flB) const;
	bool operator>=(const Float& flB) const;
	bool operator>(const Float& flB) const;

	Float& operator=(const float& flB);

	Float operator+(const float& flB) const;
	Float& operator+=(const float& flB);
	Float operator-(const float& flB) const;
	Float& operator-=(const float& flB);
	Float operator/(const float& flB) const;
	Float& operator/=(const float& flB);
	Float operator*(const float& flB) const;
	Float& operator*=(const float& flB);

	bool operator==(const float& flB) const;
	bool operator!=(const float& flB) const;
	bool operator<=(const float& flB) const;
	bool operator<(const float& flB) const;
	bool operator>=(const float& flB) const;
	bool operator>(const float& flB) const;

	operator float() const;
	operator double() const;

	void setVal(const float& val);
	const float& getVal(void) const;

	friend std::ostream& operator<<(std::ostream &os, const Float &flt) {
		os << flt._val;
		return os;
	}

private:

	inline bool almostEqualUlps(Float_t& uA, Float_t& uB, int* ulpsDiff) const;
	inline bool almostEqualAbs(const float& flB) const;
	const static int _maxUlpsDiff = EPSILONF;

	float _val;

};

#endif /* FLOAT_H_ */
