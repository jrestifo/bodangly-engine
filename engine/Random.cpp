/*
 * Random.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: demian
 */
#define _WINDOWS_


#include "Random.h"
#include <time.h>
#include <stdio.h>

//Ensure that the class is a singleton
Random* Random::_pInstance = NULL;

#ifdef _WINDOWS_ //Use CryptGenRandom... requires some setup
#pragma comment(lib, "crypt32.lib")
#include <WinDef.h>
#include <windows.h>
#include <WinBase.h>
#include <Wincrypt.h>

/* Error handler for windows */
void MyHandleError(char *s) {
	printf("An error occurred in running the program.\n");
	printf("%s\n", s);
	printf("Error number %x\n.", (unsigned int)GetLastError());
	printf("Program terminating.\n");
}
#endif // Windows

Random::Random() {
	init();
}

/* instance()
 * returns a pointer to the singleton Random instance
*/
Random* Random::instance() {
	if (!_pInstance)
		_pInstance = new Random;
	return _pInstance;
}

Random::~Random() {
}

/* init()
 * Initialize the internal rc4 rng with KEYLENGTH bytes from either
*  /dev/urandom - Linux
*  CryptGenRandom - Windows
*/
void Random::init() {
	char key[KEYLENGTH];

#ifdef _WINDOWS_
	HCRYPTPROV hCryptProv;

	if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
		printf("CryptAcquireContext succeeded. \n");
	} else
		MyHandleError("Error during CryptAcquireContext!\n");

	if (CryptGenRandom(hCryptProv, KEYLENGTH / 2, (BYTE*) key)) {
		printf("Random sequence generated\n");
	} else
		MyHandleError("Error during CryptGenRandom.");

#endif //Windows
#ifdef _LINUX_
	if ((FILE fUrandom = fopen("/dev/urandom", r)) != NULL)
	fscanf(fUrandom, "%16c", pbData);
	else
	fprintf(stderr, "Error opening /dev/urandom: %d", errno);
#endif

	//Initialize the internal state of the rc4 rng
	for (int i = 0; i < 256; ++i)
		_s[i] = i;

	_j = 0;
	for (int c = 0; c < 256; ++c) {
		_j = (_j + _s[c] + key[c % KEYLENGTH]) % 256;
		char temp = _s[_j];
		_s[_j] = _s[c];
		_s[c] = temp;
	}
	_i = 0;
	_j = 0;
	nextRound();
}

/* getNumber()
 * Retrieve four bytes from the rng and returns a single 32 bit int
 */
uint32_t Random::getNumber() {

	uint32_t ret = 0;

	ret |= _keystream << 24;
	nextRound();
	ret |= _keystream << 16;
	nextRound();
	ret |= _keystream << 8;
	nextRound();
	ret |= _keystream;

	nextRound();
	return ret;
}

/* nextRound()
 * Performs the next round of the rc4 algorithm
 */
void Random::nextRound() {
	_i = (_i + 1) % 256;
	_j = (_j + _s[_i]) % 256;
	char temp = _s[_j];
	_s[_j] = _s[_i];
	_s[_i] = temp;
	_keystream = _s[(_s[_i] + _s[_j]) % 256];
}
