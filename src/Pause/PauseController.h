/*
 * PauseController.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PAUSE_PAUSECONTROLLER_H_
#define SRC_PAUSE_PAUSECONTROLLER_H_

#include "Game/Controller.h"

class PauseController : public Controller
{

	void registerMe(const do_register_trait&) {}
	void unregisterMe(const do_register_trait&) {}
};



#endif /* SRC_PAUSE_PAUSECONTROLLER_H_ */
