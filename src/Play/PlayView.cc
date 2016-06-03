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
	ofHideCursor();
	Registrable::registerMe();
}

PlayView::PlayView(const PlayView& pw) :
	View(pw), source_(pw.source_)
{
	ofHideCursor();
	Registrable::registerMe();
}

PlayView::~PlayView()
{
	Registrable::unregisterMe();
	ofShowCursor();
}

void PlayView::registerMe(const do_register_trait& a)
{
	//View::unregisterMe();
	ofAddListener(ofEvents().update, this, &PlayView::onUpdate);
	ofAddListener(ofEvents().draw, this, &PlayView::onDraw);
}

void PlayView::unregisterMe(const do_register_trait&)
{
	ofRemoveListener(ofEvents().update, this, &PlayView::onUpdate);
	ofRemoveListener(ofEvents().draw, this, &PlayView::onDraw);
}

void PlayView::onUpdate(ofEventArgs&)
{
	camera_.resetTransform();
	camera_.setGlobalPosition(ofVec3f(source_.getPlayer().getEyePosition()));
	camera_.rotate(source_.getPlayer().getVerticalAngle(), xAxis());
	camera_.rotate(source_.getPlayer().getHorizontalAngle()+180, yAxis());
}

void PlayView::onDraw(ofEventArgs&)
{
	drawWorld();
	drawInterface();
}

void PlayView::drawWorld()
{
	draw3DGuard guard(camera_);
	for(const auto& itX : source_.getBufferManager().getBuffer())
	for(const auto& itY : itX)
	for(const auto& itZ : itY)
	for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
	{
		source_.getWorldManager().getBlock(BlockType(i)).getTexture().bind();
		itZ[i].draw();
	}
	source_.getWorldManager().getBlock(BlockType(unsigned(BlockType::COUNT)-1)).getTexture().unbind();
}

void PlayView::drawInterface() const
{
	ofDrawCircle(ofPoint(ofApp::WINDOW_X_SIZE/2, ofApp::WINDOW_Y_SIZE/2), 2);
	for(unsigned i = 1; i < unsigned(BlockType::COUNT); ++i)
		source_.getWorldManager().getBlock(BlockType(i)).getTexture()
		.draw(BLOCK_LIST_X, BLOCK_LIST_Y + BlockPrototype::SIZE*i);

	const ofPoint TRIANGLE_POS(BLOCK_LIST_X + BlockPrototype::SIZE,
							 int(source_.getEquipmentManager().getCurrentChoice())*BlockPrototype::SIZE + BLOCK_LIST_Y);
	ofDrawTriangle(TRIANGLE_POS+ofPoint(0, BlockPrototype::SIZE/2),
				   TRIANGLE_POS+ofPoint(BlockPrototype::SIZE, 0),
				   TRIANGLE_POS+ofPoint(BlockPrototype::SIZE, BlockPrototype::SIZE));
}


PlayView::draw3DGuard::draw3DGuard(ofCamera& camera)
	: guarded_camera_(camera)
{
	ofEnableDepthTest();
	guarded_camera_.begin();
}

PlayView::draw3DGuard::~draw3DGuard()
{
	guarded_camera_.end();
	ofDisableDepthTest();
}

