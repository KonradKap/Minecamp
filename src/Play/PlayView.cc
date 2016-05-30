/*
 * PlayView.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "Play/PlayView.h"

PlayView::PlayView(const WorldManager& world) :
	View(), source_(world)
{
	//std::cout << "Kappa" << std::endl;
	//ofDisableArbTex();
	ofEnableDepthTest();
}

PlayView::PlayView(const PlayView& pw) :
	View(pw), source_(pw.source_)
{
	//std::cout << "Kappa" << std::endl;
	//ofDisableArbTex();
	ofEnableDepthTest();
}

PlayView::~PlayView()
{
	//std::cout << "Keepo" << std::endl;
	//ofEnableArbTex();
	ofDisableDepthTest();
}

void PlayView::draw() const
{
	cam_.begin();
	for(const auto& itX : source_.getBuffer())
		for(const auto& itY : itX)
			for(const auto& itZ : itY)
				for(unsigned i = 0; i < unsigned(BlockType::COUNT); ++i)
				{
					source_.getModel(BlockType(i)).getTexture()./*getTexture().*/bind();
					itZ[i].draw();
					source_.getModel(BlockType(i)).getTexture()./*getTexture().*/unbind();
				}
	cam_.end();
}



