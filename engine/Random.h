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

	/* instance()
	 * returns a pointer to the singleton Random instance
	*/
	static Random* instance();

	virtual ~Random();

	/* init()
	 * Initialize the internal rc4 rng with KEYLENGTH bytes from either
	*  /dev/urandom - Linux
	*  CryptGenRandom - Windows
	*/
	void init();

	/* getNumber()
	 * Retrieve four bytes from the rng and returns a single 32 bit int
	 */
	uint32_t getNumber();

private:
	Random();
	Random(Random const&) {};
	Random& operator=(Random const&) {};

	static Random* _pInstance;

	//rc4 internal state variables
	uint8_t _i;
	uint8_t _j;
	uint8_t _s[256];

	//Contains the output of the rc4 algorithm
	uint8_t _keystream;

	/* nextRound()
	 * Performs the next round of the rc4 algorithm
	 */
	void nextRound();

};

#endif /* RANDOM_H_ */
