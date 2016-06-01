/*
 * Model.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "Model.h"

ofEvent<const GameStateEventType&> Model::event_;

Model::~Model()
{

}

ofEvent<const GameStateEventType&>& Model::getEvent()
{
	return event_;
}




