/*
 * Pause.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PAUSE_PAUSEMODEL_H_
#define SRC_PAUSE_PAUSEMODEL_H_

#include "Game/Model.h"
#include "Game/GameState.h"

class PauseModel : public Model
{
public:
	PauseModel(GameState previousState);
	~PauseModel();
private:
	GameState previousState_;
};



#endif /* SRC_PAUSE_PAUSEMODEL_H_ */
