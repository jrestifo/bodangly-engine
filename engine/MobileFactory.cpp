/*
 * MobileFactory.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */

#include "MobileFactory.h"
#include <map>

//Ensure that the class is a singleton
MobileFactory* MobileFactory::_pInstance = NULL;

MobileFactory::MobileFactory() {
}

MobileFactory::~MobileFactory() {
	delete _pInstance;
}

MobileFactory* MobileFactory::instance() {
	if (!_pInstance)
		_pInstance = new MobileFactory;
	return _pInstance;
}

uint32_t MobileFactory::registerMob(Mobile* pMob) {
	uint32_t new_id = _clRandom.getNumber();
	while (_pMobs.find(new_id) != _pMobs.end() && INVALID_ID != new_id)
		new_id = _clRandom.getNumber();
	_pMobs[new_id] = pMob;
	return new_id;
}

