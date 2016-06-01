/*
 * PlayView.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "Play/PlayView.h"

PlayView::PlayView(const World& world) :
	View(), source_(world), game_camera_()
{
	game_camera_.setup();
	game_camera_.setGlobalPosition(ofVec3f(-10, -10, -10));
	game_camera_.applyRotation = false;
	//std::cout << "Kappa" << std::endl;
	//ofDisableArbTex();
	ofEnableDepthTest();
	//ofDisableAntiAliasing();
}

PlayView::PlayView(const PlayView& pw) :
	View(pw), source_(pw.source_)
{
	//std::cout << "Kappa" << std::endl;
	//ofDisableArbTex();
	ofEnableDepthTest();
	//ofDisableAntiAliasing();
}

PlayView::~PlayView()
{
	//std::cout << "Keepo" << std::endl;
	//ofEnableArbTex();
	ofDisableDepthTest();
	//ofEnableAntiAliasing();
}

void PlayView::draw()
{
	//camera_.setGlobalPosition(ofVec3f(source_.getPlayer().getEyePosition()));
	//camera_.setOrientation(ofQuaternion(0, 0, 0, 0));
	//camera_.rotateAround()
	game_camera_.begin();
	for(const auto& itX : source_.getWorldManager().getBuffer())
		for(const auto& itY : itX)
			for(const auto& itZ : itY)
				for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
				{
					source_.getWorldManager().getModel(BlockType(i)).getTexture()./*getTexture().*/bind();
					itZ[i].draw();
					//source_.getWorldManager().getModel(BlockType(i)).getTexture()./*getTexture().*/unbind();
				}
	game_camera_.end();
}



