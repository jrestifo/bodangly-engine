/*
 * ScriptedMobile.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#include "ScriptedMobile.h"
#include <tcl.h>
#include "EngineMath.h"
#include "SteeringBehavior.h"
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
typedef  int (SteeringBehavior::*SteeringBehaviorFn)(ClientData scriptContext, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]);
void ScriptedMobile::attachTclProcedures() {

	Tcl_CreateObjCommand(&_interp, "seek",seekTcl,
			(ClientData *) _scriptContext, (Tcl_CmdDeleteProc *) NULL);
	Tcl_CreateObjCommand(&_interp, "flee",
			fleeTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "approach",
			approachTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "follow",
			followTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "avoid",
			avoidTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "evade",
			evadeTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "followPath",
			followPathTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "flock",
			flockTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "isViewable",
			isViewableTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(&_interp, "isTooClose",
			isTooCloseTcl,
			(ClientData *) _scriptContext, NULL);
}
