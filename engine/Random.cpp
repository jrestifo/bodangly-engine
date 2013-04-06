/*
 * Random.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: demian
 */

#include "Random.h"
#include <time.h>
#include <stdio.h>

#define _WINDOWS_

#ifdef _WINDOWS_ //Use CryptGenRandom... requires some setup
#pragma comment(lib, "crypt32.lib")
#include <WinDef.h>
#include <windows.h>
#include <WinBase.h>
#include <Wincrypt.h>

void MyHandleError(char *s) {
	printf("An error occurred in running the program.\n");
	printf("%s\n", s);
	printf("Error number %x\n.", GetLastError());
	printf("Program terminating.\n");
}
#endif // Windows

Random::Random() {

	char pbData[KEYLENGTH];

#ifdef _WINDOWS_
	HCRYPTPROV hCryptProv;

	if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
		printf("CryptAcquireContext succeeded. \n");
	} else
		MyHandleError("Error during CryptAcquireContext!\n");

	if (CryptGenRandom(hCryptProv, KEYLENGTH / 2, (BYTE*) pbData)) {
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

	init((char*) pbData);
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
	uint32_t ret = *(uint32_t*) &_keystream;
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
		_keystream[c] = _s[(_s[_i] + _s[_j]) % 256];
	}
}
