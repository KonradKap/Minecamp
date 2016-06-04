/*
 * Model.h
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MODEL_H_
#define SRC_GAME_MODEL_H_

#include "ofEvents.h"

#include "Utill/Registrable.h"
#include "Game/GameStateEventType.h"

class Model : public Registrable
{
public:
	Model();
	virtual ~Model();

	static ofEvent<const GameStateEventType&>& getEvent();
private:
	virtual void registerMe(const do_register_trait&);
	virtual void unregisterMe(const do_register_trait&);

	static ofEvent<const GameStateEventType&> event_;
};



#endif /* SRC_GAME_MODEL_H_ */
