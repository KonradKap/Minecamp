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
		drawButton(button);
}


