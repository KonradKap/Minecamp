/*
 * MenuView.cc
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#include "Game/Menu/MenuView.h"

MenuView::MenuView(const Menu& m) :
	View(), source_(m)
{
}

MenuView::MenuView(const MenuView& mv) :
	View(mv), source_(mv.source_)
{
}

MenuView::~MenuView()
{
}

void MenuView::draw() const
{
	drawBackground(source_.getBackground());
	drawTitle(source_.getTitle());
	drawButton(source_.getButton(Menu::ButtonType::PLAY));
	drawButton(source_.getButton(Menu::ButtonType::QUIT));
}

void MenuView::drawButton(const Button& button) const
{
	const ofVec2f POSITION = button.getPosition();
	const int INDEX = button.getState();
	const ofRectangle STRING_BOX = button.getModel()->getFont().getStringBoundingBox(button.getTitle(), 0, 0);
	button.getModel()->getImageArray()[INDEX].draw(POSITION);
	button.getModel()->getFont().drawString(button.getTitle(),
										    POSITION.x + button.getModel()->getImageArray()[INDEX].getWidth()/2 - STRING_BOX.getWidth()/2,
											POSITION.y + button.getModel()->getImageArray()[INDEX].getHeight()/2 + STRING_BOX.getHeight()/2);
}

void MenuView::drawBackground(const ofImage& image) const
{
	image.draw(0, 0);
}

void MenuView::drawTitle(const ofImage& title) const
{
	title.draw(ofApp::WINDOW_X_SIZE/2 - title.getWidth()/2, Menu::TITLE_OFFSET);
}


