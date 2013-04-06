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

private:
	uint32_t _i;
	uint32_t _j;
	char _s[256];
	char _keystream[4];

	//Takes a KEYLENGTH byte key
	void init(char key[KEYLENGTH]);

	//Generates the next 16 bytes
	void nextRound();

};

#endif /* RANDOM_H_ */
