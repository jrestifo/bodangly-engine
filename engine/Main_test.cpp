/*
 * Main_test.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: demian
 */
#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include "EngineMath.h"

using namespace std;

int main() {
	Vector2D<Double> vecA(Double(4.1289839714), Double(2.0));
	Vector2D<Double> vecB(Double(3.0), Double(1.0));

	for (int i = 0; i < 10; i++) {
		cout << setiosflags(ios::fixed) << setprecision(2) << vecA << ": "
				<< vecA.dotProduct(vecB) << "\n";
		vecA = vecA + vecB;
		if (vecA != vecA * 1) {
			cout << "Floating point math failed!\n";
			break;
		}
	}


	Random rand;


	uint32_t num = rand.getNumber();
	while (num != 0) {
		//printf("%u\r\n", num);
		num = rand.getNumber();
	}

	 printf("%u", clock());
	return 0;
}
