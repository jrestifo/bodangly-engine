/*
 * QuadTree.h
 *
 *  Created on: Apr 13, 2013
 *      Author: demian
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_
#include <memory>
#include <array>

#include "EngineMath.h"

#define NODE_CAPACITY 4


template<typename T> class QuadTree {
public:
	QuadTree();
	virtual ~QuadTree();

	bool insert(T data);
	std::shared_ptr<std::array<std::shared_ptr<T>, NODE_CAPACITY>> getImmediateData();
	std::shared_ptr<std::array<std::shared_ptr<T>, NODE_CAPACITY>> getRangeData(const BoundingBox& bounds);

private:
	std::shared_ptr<QuadTree> _nw;
	std::shared_ptr<QuadTree> _ne;
	std::shared_ptr<QuadTree> _sw;
	std::shared_ptr<QuadTree> _se;

	std::array<std::shared_ptr<T>, NODE_CAPACITY> _aData;
};

#include "QuadTree.ii"
#endif /* QUADTREE_H_ */
