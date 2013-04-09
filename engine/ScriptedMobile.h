/*
 * ScriptedMobile.h
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#ifndef SCRIPTEDMOBILE_H_
#define SCRIPTEDMOBILE_H_

#include "Mobile.h"

class ScriptedMobile: public Mobile {
public:
	ScriptedMobile();
	virtual ~ScriptedMobile();

private:
	TclInterp _interp;
};

#endif /* SCRIPTEDMOBILE_H_ */
