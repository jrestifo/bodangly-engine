/*
 * MobileFactory.h
 *
 *  Created on: Apr 3, 2013
 *      Author: demian
 */

#ifndef MOBILEFACTORY_H_
#define MOBILEFACTORY_H_

class MobileFactory {
public:
	MobileFactory();
	virtual ~MobileFactory();
	uint32_t GenerateNewID();
};

#endif /* MOBILEFACTORY_H_ */
