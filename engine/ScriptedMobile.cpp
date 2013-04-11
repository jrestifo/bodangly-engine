/*
 * ScriptedMobile.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#include "ScriptedMobile.h"
#include <tcl.h>
#include "EngineMath.h"
ScriptedMobile::ScriptedMobile() {
	_scriptContext = NULL;

}

ScriptedMobile::~ScriptedMobile() {
	// TODO Auto-generated destructor stub
}

/* attachTclProcedures
 * Creates procedures for our steering behavior functions in the Tcl interpreter
 * This will facilitate complex scripted AI behaviors built from these basic building blocks
 */
void ScriptedMobile::attachTclProcedures() {

	Tcl_CreateObjCommand(_interp.interp().get(), "seek",
			this->_steeringBehavior.get()->seekTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "flee",
			this->_steeringBehavior.get()->fleeTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "approach",
			this->_steeringBehavior.get()->approachTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "follow",
			this->_steeringBehavior.get()->followTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "avoid",
			this->_steeringBehavior.get()->avoidTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "evade",
			this->_steeringBehavior.get()->evadeTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "followPath",
			this->_steeringBehavior.get()->followPathTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "flock",
			this->_steeringBehavior.get()->flockTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "isViewable",
			this->_steeringBehavior.get()->isViewableTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "isTooClose",
			this->_steeringBehavior.get()->isTooCloseTcl,
			(ClientData *) _scriptContext, NULL);
}
