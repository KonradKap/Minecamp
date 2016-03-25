/*
 * Play.cc
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#include "Game/Play.h"

Play::Play()
{
}

Play::Play(const Play& p)
{
}

Play::~Play()
{
}

GameState* Play::update(float elapsed_time)
{
	return this;
}

void Play::draw() const
{
	cam.begin();

		w_.draw();

	cam.end();
}




