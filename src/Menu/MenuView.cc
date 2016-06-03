/*
 * MenuView.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "MenuView.h"
#include "ofApp.h"

MenuView::MenuView(const MenuModel& m) :
	View(), source_(m)
{
	Registrable::registerMe();
}

MenuView::MenuView(const MenuView& mv) :
	View(mv), source_(mv.source_)
{
	Registrable::registerMe();
}

MenuView::~MenuView()
{
	Registrable::unregisterMe();
}

void MenuView::onDraw(ofEventArgs&)
{
	drawBackground(source_.getBackground());
	drawTitle(source_.getTitle());
	for(const auto& it : source_.getButtons())
		drawButton(it);
	//drawButton(source_.getButton(Menu::ButtonType::PLAY));
	//drawButton(source_.getButton(Menu::ButtonType::QUIT));
}

void MenuView::drawButton(const Button& button) const
{
	const ofVec2f POSITION = button.getPosition();
	const int INDEX = button.getState();
	const ofRectangle STRING_BOX = button.getPrototype().getFont().getStringBoundingBox(button.getTitle(), 0, 0);
	button.getPrototype().getImageArray()[INDEX].draw(POSITION);
	button.getPrototype().getFont().drawString(button.getTitle(),
										    POSITION.x + button.getPrototype().getImageArray()[INDEX].getWidth()/2 - STRING_BOX.getWidth()/2,
											POSITION.y + button.getPrototype().getImageArray()[INDEX].getHeight()/2 + STRING_BOX.getHeight()/2);
}

void MenuView::drawBackground(const ofImage& image) const
{
	image.draw(0, 0);
}

void MenuView::drawTitle(const ofImage& title) const
{
	title.draw(ofApp::WINDOW_X_SIZE/2 - title.getWidth()/2, MenuModel::TITLE_OFFSET);
}


