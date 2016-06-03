/*
 * MenuView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MENU_MENUVIEW_H_
#define SRC_GAME_MENU_MENUVIEW_H_

class ofEventArgs;

#include "Game/View.h"
#include "Menu/Button.h"
#include "Menu/MenuModel.h"

class MenuView : public View
{
public:
	MenuView(const MenuModel& m);
	MenuView(const MenuView& mv);
	~MenuView();

private:


	void onDraw(ofEventArgs&);
	void drawButton(const Button& b) const;
	void drawBackground(const ofImage& image) const;
	void drawTitle(const ofImage& title) const;

	const MenuModel& source_;
};



#endif /* SRC_GAME_MENU_MENUVIEW_H_ */
