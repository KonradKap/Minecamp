/*
 * PlayView.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "Play/PlayView.h"
#include "Play/PlayModel.h"

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
	ofDisableDepthTest();
	ofShowCursor();
	ofRemoveListener(ofEvents().update, this, &PlayView::onUpdate);
}

void PlayView::setup()
{
	ofAddListener(ofEvents().update, this, &PlayView::onUpdate);
	ofHideCursor();
	ofEnableDepthTest();
}

void PlayView::onUpdate(ofEventArgs&)
{
	camera_.resetTransform();
	camera_.setGlobalPosition(ofVec3f(source_.getPlayer().getEyePosition()));

	camera_.rotate(source_.getPlayer().getVerticalAngle(), xAxis());
	camera_.rotate(source_.getPlayer().getHorizontalAngle(), yAxis());
}

void PlayView::onDraw(ofEventArgs&)
{
	camera_.begin();
	for(const auto& itX : source_.getWorldManager().getBuffer())
		for(const auto& itY : itX)
			for(const auto& itZ : itY)
				for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
				{
					source_.getWorldManager().getModel(BlockType(i)).getTexture().bind();
					itZ[i].draw();
					//source_.getWorldManager().getModel(BlockType(i)).getTexture().unbind();
				}
	camera_.end();
}



