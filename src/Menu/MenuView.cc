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
}

MenuView::MenuView(const MenuView& mv) :
	View(mv), source_(mv.source_)
{
}

MenuView::~MenuView()
{
}

void MenuView::onDraw(ofEventArgs&)
{
	source_.getBackground().draw(0, 0);
	source_.getTitle().draw(ofApp::WINDOW_X_SIZE/2 - source_.getTitle().getWidth()/2, MenuModel::TITLE_OFFSET);
	for(const auto& button : source_.getButtons())
		drawButton(button);
}

