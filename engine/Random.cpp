/*
 * Random.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: demian
 */

#include "Random.h"
#include <time.h>

Random::Random() {
	time_t times[4];
	char key[KEYLENGTH];

	time(&times[0]);
	time(&times[1]);
	time(&times[2]);
	time(&times[3]);

	for (int i = 0; i < KEYLENGTH; ++i)
		key[i] = *(char*)&times[i];

	init(key);
}

Random::~Random() {
}

void Random::init(char key[KEYLENGTH]) {
	for (int i = 0; i < 256; ++i)
		_s[i] = i;

	_j = 0;
	for (int c = 0; c < 256; ++c) {
		_j = (_j + _s[c] + key[c & KEYLENGTH]) % 256;
		_s[c] ^= _s[_j];
		_s[_j] ^= _s[c];
		_s[c] ^= _s[_j];
	}
	_i = 0;
	_j = 0;
	nextRound();
}

uint32_t Random::getNumber() {
	uint32_t ret = *(uint32_t*)&_keystream;
	nextRound();
	return ret;
}

void Random::nextRound() {
	for (int c = 0; c < 4; c++) {
		_i = (_i + 1) % 256;
		_j = (_j + _s[_i]) % 256;
		_s[_i] ^= _s[_j];
		_s[_j] ^= _s[_i];
		_s[_i] ^= _s[_j];
		_keystream[c] = _s[ ( _s[_i] + _s[_j] ) % 256];
	}
}
