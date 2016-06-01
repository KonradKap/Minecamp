/*
 * View.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "../Game/View.h"

View::View()
{
	ofAddListener(ofEvents().draw, this, &View::onDraw);
}

View::~View()
{
	ofRemoveListener(ofEvents().draw, this, &View::onDraw);
}

ofVec3f View::xAxis()
{
	return ofVec3f(1, 0, 0);
}

ofVec3f View::yAxis()
{
	return ofVec3f(0, 1, 0);
}

ofVec3f View::zAxis()
{
	return ofVec3f(0, 0, 1);
}

