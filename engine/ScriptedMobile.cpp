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

	SteeringBehaviorFn pSeekTcl = &SteeringBehavior::seekTcl;
	SteeringBehaviorFn pFleeTcl = &SteeringBehavior::fleeTcl;
	SteeringBehaviorFn pApproachTcl = &SteeringBehavior::approachTcl;
	SteeringBehaviorFn pFollowTcl = &SteeringBehavior::followTcl;
	SteeringBehaviorFn pAvoidTcl = &SteeringBehavior::avoidTcl;
	SteeringBehaviorFn pEvadeTcl = &SteeringBehavior::evadeTcl;
	SteeringBehaviorFn pFollowPathTcl = &SteeringBehavior::followPathTcl;
	SteeringBehaviorFn pFlockTcl = &SteeringBehavior::flockTcl;
	SteeringBehaviorFn pIsViewableTcl = &SteeringBehavior::isViewableTcl;
	SteeringBehaviorFn pisTooCloseTcl = &SteeringBehavior::isTooCloseTcl;

	Tcl_CreateObjCommand(_interp.interp().get(), "seek", pSeekTcl,
			(ClientData *) _scriptContext, (Tcl_CmdDeleteProc *) NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "flee",
			pFleeTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "approach",
			pApproachTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "follow",
			pFollowTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "avoid",
			pAvoidTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "evade",
			pEvadeTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "followPath",
			pFollowPathTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "flock",
			pFlockTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "isViewable",
			pIsViewableTcl,
			(ClientData *) _scriptContext, NULL);
	Tcl_CreateObjCommand(_interp.interp().get(), "isTooClose",
			pisTooCloseTcl,
			(ClientData *) _scriptContext, NULL);
}
