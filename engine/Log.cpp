/*
 * Log.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */
#include <string>
#include <stdio.h>
#include "Log.h"

//Ensure that the class is a singleton
Log* Log::_pInstance = NULL;

Log::Log() {
_bStdout = true;
_bStderr = true;
}

Log::~Log() {
	_fLog.close();
	delete _pInstance;
}

bool Log::initLog(const std::string& sPath) {
	_fLog.open(sPath);
	if (_fLog.failbit) {
		std::cerr << "Couldn't open " << sPath << " for logging.\n";
		return false;
	}
	return true;
}

bool Log::changeFile(const std::string& sNewPath) {
	_fLog.close();
	_fLog.open(sNewPath);
	if (_fLog.failbit) {
		std::cerr << "Couldn't open " << sNewPath << " for logging.\n";
		return false;
	}
	return true;
}

void Log::postError(const std::string& sError) {
	_fLog << "\r\n" << sError << "\r\n";
	if (_bStderr)
		_fLog << "\r\n" << sError << "\r\n";
}

void Log::postMsg(const std::string& sMsg) {
	_fLog << "\r\n" << sMsg << "\r\n";
	if (_bStdout)
		_fLog << "\r\n" << sMsg << "\r\n";
}
