/*
 * Screen.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: demian
 */

#include "Screen.h"

//Ensure that the class is a singleton
Screen* Screen::_pInstance = NULL;


Screen::Screen() {

	_width = 640;
	_height = 480;

}

Screen::~Screen() {
}

const int32_t& Screen::getWidth() const {
	return _width;
}

const int32_t& Screen::getHeight() const {
	return _height;
}

Screen* Screen::instance() {
	if (!_pInstance)
		_pInstance = new Screen;
	return _pInstance;
}
