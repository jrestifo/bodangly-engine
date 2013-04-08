/*
 * GameLogic.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#include "GameLogic.h"

//Ensure that the class is a singleton
GameLogic* GameLogic::_pInstance = NULL;

GameLogic::GameLogic() {
	// TODO Auto-generated constructor stub

}

GameLogic::~GameLogic() {
	delete _pInstance;
}

GameLogic* GameLogic::instance() {
	if (!_pInstance)
		_pInstance = new GameLogic;
	return _pInstance;
}
