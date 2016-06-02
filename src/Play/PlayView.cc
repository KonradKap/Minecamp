/*
 * PlayView.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "Play/PlayView.h"
#include "Play/PlayModel.h"
#include "ofApp.h"

PlayView::PlayView(const PlayModel& model) :
	View(), source_(model)
{
	setup();
}

PlayView::PlayView(const PlayView& pw) :
	View(pw), source_(pw.source_)
{
	setup();
}

PlayView::~PlayView()
{
//	camera_.setVFlip(false);

	ofShowCursor();
	ofRemoveListener(ofEvents().update, this, &PlayView::onUpdate);
}

void PlayView::setup()
{
	ofAddListener(ofEvents().update, this, &PlayView::onUpdate);
	ofHideCursor();

}

void PlayView::onUpdate(ofEventArgs&)
{
	camera_.resetTransform();
	//ofVec3f direction = ofVec3f(source_.getPlayer().getDirection());
	camera_.setGlobalPosition(ofVec3f(source_.getPlayer().getEyePosition()));
/*
	camera_.setGlobalOrientation(ofQuaternion(
			direction.angle(xAxis()), xAxis(),
			direction.angle(yAxis()), yAxis(),
			direction.angle(zAxis()), zAxis()));

	camera_.setGlobalOrientation(ofQuaternion(0, ofVec3f(source_.getPlayer().getDirection())));
*/
	camera_.rotate(source_.getPlayer().getVerticalAngle(), xAxis());
	camera_.rotate(source_.getPlayer().getHorizontalAngle()+180, yAxis());
}

void PlayView::onDraw(ofEventArgs&)
{
	ofEnableDepthTest();
	camera_.begin();
	for(const auto& itX : source_.getBufferManager().getBuffer())
		for(const auto& itY : itX)
			for(const auto& itZ : itY)
				for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
				{
					source_.getWorldManager().getBlock(BlockType(i)).getTexture().bind();
					itZ[i].draw();
					//source_.getWorldManager().getModel(BlockType(i)).getTexture().unbind();
				}
//DEBUG:
	ofDrawAxis(100);

	camera_.end();
	ofDisableDepthTest();

	ofSetColor(0);
	ofFill();

	ofDrawCircle(ofPoint(ofApp::WINDOW_X_SIZE/2, ofApp::WINDOW_Y_SIZE/2), 5);

	ofSetColor(255);
}



