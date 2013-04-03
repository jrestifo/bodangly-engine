/*
 * Screen.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: demian
 */

#include "Screen.h"

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
