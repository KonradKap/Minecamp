/*
 * Player.h
 *
 *  Created on: 30 maj 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_PLAYER_H_
#define SRC_PLAY_PLAYER_H_

#include "ofEvent.h"
#include "ofCamera.h"

#include "World/WorldManager.h"

class Player
{
public:
	double getTop() const;
	double getBottom() const;
	double getLeft() const;
	double getRight() const;
	double getFront() const;
	double getBack() const;

	vec3Dd getEyePosition() const;

	void setPosition(const vec3Dd& position);

	ofEvent<WorldManager::blockEventArgs>& getPlacedBlockEvent();
	ofEvent<vec3Di>& getDestroyedBlockEvent();

	static const int HEIGHT = 30;
	static const int WIDTH  = 5;
	static const int EYE_HEIGHT = 28;
private:
	ofEvent<WorldManager::blockEventArgs> placedBlockEvent_;
	ofEvent<vec3Di> destroyedBlockEvent_;

	vec3Dd position_;
};




#endif /* SRC_PLAY_PLAYER_H_ */
