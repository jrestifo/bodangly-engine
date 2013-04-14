/*
 * BoundingBox.h
 *
 *  Created on: Apr 13, 2013
 *      Author: demian
 */

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include "EngineMath.h"

class BoundingBox {
	friend class QuadTree;
public:
	BoundingBox();
	virtual ~BoundingBox();

private:
	Vector2D<uint32_t> _v2BottomLeft;
	Vector2D<uint32_t> _v2TopRight;
};

#endif /* BOUNDINGBOX_H_ */
