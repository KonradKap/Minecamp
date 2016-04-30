/*
 * Play.cc
 *
 *  Created on: 12 mar 2016
 *      Author: konrad
 */

#include "Play/Play.h"

Play::Play()
{
}

Play::Play(const Play& p)
{
}

Play::~Play()
{
}

void Play::update(float elapsed_time)
{
	return;
}

std::unique_ptr<View> Play::getDefaultView() const
{
	return std::unique_ptr<View>(new PlayView(w_));
}
/*
void Play::draw() const
{
	cam.begin();

		w_.draw();

	cam.end();
}
*/



