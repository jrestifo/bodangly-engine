/*
 * Random.h
 *
 *  Created on: Apr 4, 2013
 *      Author: demian
 */

#ifndef RANDOM_H_
#define RANDOM_H_
#define KEYLENGTH 16
#include <inttypes.h>

class Random {

public:
	Random();
	virtual ~Random();

	uint32_t getNumber();
	void init();

private:
	uint8_t _i;
	uint8_t _j;
	uint8_t _s[256];
	uint8_t _keystream;

	//Takes a KEYLENGTH byte key


	//Generates the next 16 bytes
	void nextRound();

};

#endif /* RANDOM_H_ */
