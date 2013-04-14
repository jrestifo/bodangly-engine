/*
 * ScriptedMobile.h
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#ifndef SCRIPTEDMOBILE_H_
#define SCRIPTEDMOBILE_H_

#include "Mobile.h"
#include "TclInterp.h"

class ScriptedMobFactory;

class ScriptedMobile: public Mobile {
friend class ScriptedMobFactory;

public:
	ScriptedMobile();
	virtual ~ScriptedMobile();

private:
	void attachTclProcedures();

	TclInterp _interp;

	//TODO Define a structure for the exchange of data between ScriptedMobile and Tcl
	void* _scriptContext;
};

#endif /* SCRIPTEDMOBILE_H_ */
