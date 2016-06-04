/*
 * PauseView.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PAUSE_PAUSEVIEW_H_
#define SRC_PAUSE_PAUSEVIEW_H_

#include "ofEvents.h"

#include "Game/View.h"
#include "Pause/PauseModel.h"


class PauseView : public View
{
public:
	PauseView(const PauseModel& source);
	~PauseView();
private:
	void onDraw(ofEventArgs&);

	const PauseModel& source_;
};


#endif /* SRC_PAUSE_PAUSEVIEW_H_ */
