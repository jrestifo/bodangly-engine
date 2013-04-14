/*
 * Area.h
 *
 *  Created on: Apr 11, 2013
 *      Author: demian
 */

#ifndef AREA_H_
#define AREA_H_
#include "EngineMath.h"
#include <list>

//An area represents a map or a level
//TODO Implement more advanced spatial partitioning, likely a quadtree
//For now an area is just a single grid, multiple Areas may be needed to represent one map
class Area {
public:
	Area();
	virtual ~Area();

private:
	uint32_t _length;
	uint32_t _width;

	//Mobiles within the grid represented as a list of lists
};

#endif /* AREA_H_ */
