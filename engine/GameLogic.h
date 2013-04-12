/*
 * GameLogic.h
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include <memory>
#include <map>

#include "Mobile.h"

class GameLogic {
	friend class MobileFactory;
public:
	static GameLogic* instance();
	virtual ~GameLogic();

	std::shared_ptr<Mobile> findMob(uint32_t id);
private:

	GameLogic();
	GameLogic(GameLogic const&) {};
	GameLogic& operator=(GameLogic const&) {};
	static GameLogic* _pInstance;

	//Stored as a hash map for now
	//TODO Grid-based partitioning
	std::map<uint32_t, std::shared_ptr<Mobile>> _pMobs;
};

#endif /* GAMELOGIC_H_ */
