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

//Random is a singleton
//This aids in synchronization as well as facilitating saving the game

class Random {

public:
	static Random* instance();
	virtual ~Random();

	void init();
	uint32_t getNumber();

private:
	Random();
	Random(Random const&) {};
	Random& operator=(Random const&) {};

	static Random* _pInstance;

	uint8_t _i;
	uint8_t _j;
	uint8_t _s[256];
	uint8_t _keystream;

	//Generates the next 16 bytes
	void nextRound();

};

#endif /* RANDOM_H_ */
