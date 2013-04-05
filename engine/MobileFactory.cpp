/*
 * MobileFactory.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */

#include "MobileFactory.h"
#include <map>
MobileFactory* MobileFactory::_pInstance = NULL;

MobileFactory::MobileFactory() {
}

MobileFactory::~MobileFactory() {
}

MobileFactory* MobileFactory::Instance() {
	if (!_pInstance)
		_pInstance = new MobileFactory;
	return _pInstance;
}

uint32_t MobileFactory::RegisterMob(Mobile* pMob) {
	uint32_t new_id = _cRandom.getNumber();
	while (_pMobs.find(new_id) != _pMobs.end() && INVALID_ID != new_id)
		new_id = _cRandom.getNumber();
	_pMobs[new_id] = pMob;
	return new_id;
}
