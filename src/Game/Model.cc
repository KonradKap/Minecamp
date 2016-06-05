/*
 * Model.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "Model.h"

ofEvent<const GameStateEventType&> Model::event_;

Model::Model() :
	Registrable()
{
}

Model::~Model()
{
}

ofEvent<const GameStateEventType&>& Model::getEvent()
{
	return event_;
}

void Model::registerMe(const do_register_trait&)
{
}

void Model::unregisterMe(const do_register_trait&)
{
}



