/*
 * Screen.h
 *
 *  Created on: Mar 31, 2013
 *      Author: demian
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include "Vector2D.h"

class Screen {
public:
	Screen();
	virtual ~Screen();

	const Vector2D<uint32_t>& getDimensions();
	void setDimensions(const Vector2D<uint32_t>& dimensions);

	const int32_t& getWidth() const;
	const int32_t& getHeight() const;

	void setWidth(const int32_t& width) const;
	void setHeight(const int32_t& height) const;

private:
	int32_t _width;
	int32_t _height;
};

#endif /* SCREEN_H_ */
