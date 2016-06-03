/*
 * PlayView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_PLAYVIEW_H_
#define SRC_GAME_PLAYVIEW_H_

class PlayModel;

#include "ofCamera.h"

#include "Game/View.h"

class PlayView : public View
{
public:
	PlayView(const PlayModel& model);
	PlayView(const PlayView& pw);
	~PlayView();

	static const int BLOCK_LIST_X = 10;
	static const int BLOCK_LIST_Y = 10;
private:
	struct draw3DGuard;

	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	void onUpdate(ofEventArgs&);
	void onDraw(ofEventArgs&);

	void drawWorld();
	void drawInterface() const;

	const PlayModel& source_;

	ofCamera camera_;
};

struct PlayView::draw3DGuard
{
public:
	draw3DGuard(ofCamera& guarded_camera);
	~draw3DGuard();
private:
	ofCamera& guarded_camera_;
};

#endif /* SRC_GAME_PLAYVIEW_H_ */
