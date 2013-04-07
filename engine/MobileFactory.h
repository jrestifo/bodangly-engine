/*
 * MobileFactory.h
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */

#ifndef MOBILEFACTORY_H_
#define MOBILEFACTORY_H_
#include <map>
#include <memory>

#include "EngineMath.h"
#include "enum_mob.h"

#define INVALID_ID 0

class Mobile;

class MobileFactory {
public:
	static MobileFactory* instance();
	virtual ~MobileFactory();

	//Creates a mob and returns a pointer to it, accepting a mob type
	std::shared_ptr<Mobile> spawn(mob_t mobType);

	//Registers a mob, adding it to the Mobs map
	//Returns: an ID representing the map key
	uint32_t registerMob(std::shared_ptr<Mobile> pMob);

private:
	MobileFactory();
	MobileFactory(MobileFactory const&){};
	MobileFactory& operator=(MobileFactory const&){};
	static MobileFactory* _pInstance;
	Random _clRandom;
	std::map<uint32_t, std::shared_ptr<Mobile>> _pMobs;
};


#endif /* MOBILEFACTORY_H_ */
