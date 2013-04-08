/*
 * ScriptedMobFactory.h
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#ifndef SCRIPTEDMOBFACTORY_H_
#define SCRIPTEDMOBFACTORY_H_

#include "MobileFactory.h"

class ScriptedMobFactory: public MobileFactory {
public:
	ScriptedMobFactory();
	virtual ~ScriptedMobFactory();

private:

	static ScriptedMobFactory* _pInstance;
};

#endif /* SCRIPTEDMOBFACTORY_H_ */
