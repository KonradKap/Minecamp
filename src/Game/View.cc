/*
 * View.cc
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#include "../Game/View.h"

View::View() :
	Registrable()
{

}

View::~View()
{

}

void View::registerMe(const do_register_trait&)
{
	ofAddListener(ofEvents().draw, this, &View::onDraw);
}

void View::unregisterMe(const do_register_trait&)
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


void View::drawButton(const Button& button) const
{
	const ofVec2f POSITION = button.getPosition();
	const int INDEX = button.getState();
	const ofRectangle STRING_BOX = button.getPrototype().getFont().getStringBoundingBox(button.getTitle(), 0, 0);
	button.getPrototype().getImageArray()[INDEX].draw(POSITION);
	button.getPrototype().getFont().drawString(button.getTitle(),
										    POSITION.x + button.getPrototype().getImageArray()[INDEX].getWidth()/2 - STRING_BOX.getWidth()/2,
											POSITION.y + button.getPrototype().getImageArray()[INDEX].getHeight()/2 + STRING_BOX.getHeight()/2);
}


