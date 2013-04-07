/*
 * MobileFactory.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */

#include "MobileFactory.h"
#include <map>
#include "Mobile.h"
#include "EngineMath.h"
#include <memory>

//Ensure that the class is a singleton
MobileFactory* MobileFactory::_pInstance = NULL;

MobileFactory::MobileFactory() {
}

MobileFactory::~MobileFactory() {
	delete _pInstance;
}

/* instance()
 * returns a pointer to the singleton MobileFactory instance
 */
MobileFactory* MobileFactory::instance() {
	if (!_pInstance)
		_pInstance = new MobileFactory;
	return _pInstance;
}

/* spawn(mob_t mobType)
 * Generates a new mob of type mob_t, gives it a unique ID and adds it to the mob map
 * Returns a pointer to the new mob
 */

shared_ptr<Mobile> MobileFactory::spawn(mob_t mobType) {
	Mobile* pNewMob = new Mobile();
	pNewMob->_id = registerMob(pNewMob);

	return pNewMob;
}

/* registerMob(Mobile* pMob)
 * Generates a unique ID and registers the mob in the mob map
 */
uint32_t MobileFactory::registerMob(Mobile* pMob) {
	uint32_t new_id = _clRandom.getNumber();
	while (_pMobs.find(new_id) != _pMobs.end() && INVALID_ID != new_id)
		new_id = _clRandom.getNumber();
	_pMobs[new_id] = pMob;
	return new_id;
}
