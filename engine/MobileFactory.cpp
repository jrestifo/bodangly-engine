/*
 * MobileFactory.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */
#include <map>
#include <memory>

#include "MobileFactory.h"
#include "Mobile.h"
#include "EngineMath.h"
#include "GameLogic.h"

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

std::shared_ptr<Mobile> MobileFactory::spawn(mob_t mobType) {
	std::shared_ptr<Mobile>pNewMob(new Mobile());
	pNewMob->_id = registerMob(pNewMob);

	return pNewMob;
}

/* registerMob(Mobile* pMob)
 * Generates a unique ID and registers the mob in the mob map
 */
uint32_t MobileFactory::registerMob(std::shared_ptr<Mobile> pMob) {
	uint32_t new_id = _clRandom.getNumber();
	while (GameLogic::instance()->_pMobs.find(new_id) != GameLogic::instance()->_pMobs.end() && INVALID_ID != new_id)
		new_id = _clRandom.getNumber();
	GameLogic::instance()->_pMobs[new_id] = pMob;
	return new_id;
}
