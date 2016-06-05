/*
 * Controller.h
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_CONTROLLER_H_
#define SRC_GAME_CONTROLLER_H_

#include "Utill/Registrable.h"
#include "ofConstants.h"

class Controller : public Registrable
{
public:
	static void setCursorOnMiddle();
	virtual ~Controller();
};



#endif /* SRC_GAME_CONTROLLER_H_ */
