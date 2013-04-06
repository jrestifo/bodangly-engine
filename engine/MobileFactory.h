/*
 * MobileFactory.h
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */

#ifndef MOBILEFACTORY_H_
#define MOBILEFACTORY_H_
#include "EngineMath.h"
#include <map>

#define INVALID_ID 0

class Mobile;

class MobileFactory {
public:
	static MobileFactory* instance();
	virtual ~MobileFactory();

	//Registers a mob, adding it to the Mobs map
	//Returns: an ID representing the map key
	uint32_t registerMob(Mobile* pMob);

private:
	MobileFactory();
	MobileFactory(MobileFactory const&){};
	MobileFactory& operator=(MobileFactory const&){};
	static MobileFactory* _pInstance;

	Random _clRandom;
	std::map<uint32_t, Mobile*> _pMobs;
};


#endif /* MOBILEFACTORY_H_ */
