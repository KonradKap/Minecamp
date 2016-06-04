/*
 * PauseView.cc
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#include "Pause/PauseView.h"

PauseView::PauseView(const PauseModel& source) :
	source_(source)
{
}

PauseView::~PauseView()
{
}

void PauseView::onDraw(ofEventArgs&)
{
	source_.getBackground().draw(0, 0);
	for(const auto& button : source_.getButtons())
	{
		const ofVec2f POSITION = button.getPosition();
		const int INDEX = button.getState();
		const ofRectangle STRING_BOX = button.getPrototype().getFont().getStringBoundingBox(button.getTitle(), 0, 0);
		button.getPrototype().getImageArray()[INDEX].draw(POSITION);
		button.getPrototype().getFont().drawString(button.getTitle(),
											POSITION.x + button.getPrototype().getImageArray()[INDEX].getWidth()/2 - STRING_BOX.getWidth()/2,
											POSITION.y + button.getPrototype().getImageArray()[INDEX].getHeight()/2 + STRING_BOX.getHeight()/2);
	}
}


