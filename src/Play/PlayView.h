/*
 * PlayView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_PLAYVIEW_H_
#define SRC_GAME_PLAYVIEW_H_

#include "World/WorldManager.h"
#include "ofEasyCam.h"

#include "View.h"

class PlayView : public View
{
public:
	PlayView(const WorldManager& world);
	PlayView(const PlayView& pw);
	~PlayView();

	void draw() const;
private:
	const WorldManager& source_;
	mutable ofEasyCam cam_; //temporary
};



#endif /* SRC_GAME_PLAYVIEW_H_ */
