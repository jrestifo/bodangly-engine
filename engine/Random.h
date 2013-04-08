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
	Random(Random const& randB);
	Random& operator=(Random const& randB);

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

	//rc4 internal state variables
	uint8_t _s[256];
	uint8_t _i;
	uint8_t _j;
	//Contains the output of the rc4 algorithm
	uint8_t _keystream;

	/* nextRound()
	 * Performs the next round of the rc4 algorithm
	 */
	void nextRound();

};

#endif /* RANDOM_H_ */
