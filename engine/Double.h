/*
 * Double.h
 *
 *  Created on: Mar 29, 2013
 *      Author: demian
 */

#ifndef DOUBLE_H_
#define DOUBLE_H_
#define EPSILOND 400000000
#include <iostream>

union Double_t {
	Double_t(double num = 0.0) :
			f(num) {
	}
	// Portable extraction of components.
	bool isNegative() const {
		return (i >> 63) != 0;
	}
	int32_t RawMantissa() const {
		return i & (((int64_t)1 << 52) - 1);
	}
	int32_t RawExponent() const {
		return (i >> 52) & 0xFF;
	}

	int64_t i;
	double f;
#ifdef _DEBUG
	struct
	{   // Bitfields for exploration. Do not use in production code.
		uint32_t mantissa : 52;
		uint32_t exponent : 11;
		uint32_t sign : 1;
	}parts;
#endif
};

class Double {
public:
	Double();
	Double(const double& val);
	virtual ~Double();

	Double& operator=(const Double& dblB);

	Double operator+(const Double& dblB) const;
	Double& operator+=(const Double& dblB);
	Double operator-(const Double& dblB) const;
	Double& operator-=(const Double& dblB);
	Double operator/(const Double& dblB) const;
	Double& operator/=(const Double& dblB);
	Double operator*(const Double& dblB) const;
	Double& operator*=(const Double& dblB);

	bool operator==(const Double& dblB) const;
	bool operator!=(const Double& dblB) const;
	bool operator<=(const Double& dblB) const;
	bool operator<(const Double& dblB) const;
	bool operator>=(const Double& dblB) const;
	bool operator>(const Double& dblB) const;

	Double& operator=(const double& dblB);

	Double operator+(const double& dblB) const;
	Double& operator+=(const double& dblB);
	Double operator-(const double& dblB) const;
	Double& operator-=(const double& dblB);
	Double operator/(const double& dblB) const;
	Double& operator/=(const double& dblB);
	Double operator*(const double& dblB) const;
	Double& operator*=(const double& dblB);

	bool operator==(const double& dblB) const;
	bool operator!=(const double& dblB) const;
	bool operator<=(const double& dblB) const;
	bool operator<(const double& dblB) const;
	bool operator>=(const double& dblB) const;
	bool operator>(const double& dblB) const;

	operator double() const;
	operator float() const;

	void setVal(const double& val);
	const double& getVal(void) const;

	friend std::ostream& operator<<(std::ostream &os, const Double &flt) {
		os << flt._val;
		return os;
	}

private:

	inline bool almostEqualUlps(Double_t& uA, Double_t& uB, int* ulpsDiff) const;
	inline bool almostEqualAbs(const double& dblB) const;
	const static int _maxUlpsDiff = EPSILOND;

	double _val;

};

#endif /* DOUBLE_H_ */
