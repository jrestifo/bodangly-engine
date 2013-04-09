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
	_interp = std::shared_ptr<Tcl_Interp>(new Tcl_Interp);

}

TclInterp::~TclInterp() {
}

std::shared_ptr<Tcl_Interp> TclInterp::interp() {
	return _interp;
}

