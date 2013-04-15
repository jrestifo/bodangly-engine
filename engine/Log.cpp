/*
 * Log.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */
#include <string>
#include <iostream>
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

/* instance()
 * returns a pointer to the singleton MobileFactory instance
 */
Log* Log::instance() {
	if (!_pInstance)
		_pInstance = new Log;
	return _pInstance;
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

void Log::startStdout() {
	_bStdout = true;
}


void Log::stopStdout() {
	_bStdout = false;
}

void Log::startStderr() {
	_bStderr = true;
}


void Log::stopStderr() {
	_bStderr = false;
}

