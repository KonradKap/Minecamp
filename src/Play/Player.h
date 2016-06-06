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

#include "Utill/Registrable.h"
#include "World/WorldManager.h"
#include "Game/View.h"

class Player : public Registrable
{
public:
	Player();
	~Player();

	double getTop() const;
	double getBottom() const;
	double getLeft() const;
	double getRight() const;
	double getFront() const;
	double getBack() const;
	double getHeight() const;
	double getWidth() const;

	vec3Dd getEyePosition() const;

	void setPosition(const vec3Dd& position);
	vec3Dd getPosition() const;

	vec3Dd getDirectionVector(ofVec3f base = ofVec3f(0, 0, 1)) const;
	void setSteer(const vec3Di& steering);
	vec3Di getSteer() const;
	void setYVelocity(const double yVelocity);

	void rotate(float horizontal_rotation, float vertical_rotation);
	void horizontalRotate(float rotation);
	void verticalRotate(float rotation);

	float getHorizontalAngle() const;
	float getVerticalAngle() const;


	void moveUpdate();


	constexpr static const double HEIGHT = 1.9;
	constexpr static const double WIDTH  = 0.25;
	constexpr static const double EYE_HEIGHT = 1.5;
	static const int VELOCITY = 6;
	static const int TVELOCITY=20;
	static const int RANGE = 8;
	static const int GRAVITY = 10;
private:

	void onUpdate(ofEventArgs& args);




	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);




	vec3Dd position_;
	vec3Di steer_;

	float horizontal_angle_;
	float vertical_angle_;
	double y_velocity_= 0;
};




#endif /* SRC_PLAY_PLAYER_H_ */
