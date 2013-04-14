/*
 * TclInterp.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: demian
 */

#include "TclInterp.h"
#include <memory>
#include <tcl.h>

TclInterp::TclInterp() {
	_interp = std::shared_ptr<Tcl_Interp>(Tcl_CreateInterp());
	Tcl_Init((Tcl_Interp*)_interp.get());
}

TclInterp::~TclInterp() {
}

std::shared_ptr<Tcl_Interp> TclInterp::interp() {
	return _interp;
}

