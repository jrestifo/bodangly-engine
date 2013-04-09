/*
 * TclInterp.h
 *
 *  Created on: Apr 8, 2013
 *      Author: demian
 */

#ifndef TCLINTERP_H_
#define TCLINTERP_H_
#include <memory>
#include <tcl.h>

class TclInterp {
public:
	TclInterp();
	virtual ~TclInterp();
	std::shared_ptr<Tcl_Interp*> interp();

private:
	std::shared_ptr<Tcl_Interp*> _interp;
};

#endif /* TCLINTERP_H_ */
