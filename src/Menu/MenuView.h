/*
 * MenuView.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MENU_MENUVIEW_H_
#define SRC_GAME_MENU_MENUVIEW_H_

#include "Utill/View.h"
#include "Menu/Menu.h"

class MenuView : public View
{
public:
	MenuView(const Menu& m);
	MenuView(const MenuView& mv);
	~MenuView();

	void draw();
private:
	void drawButton(const Button& b) const;
	void drawBackground(const ofImage& image) const;
	void drawTitle(const ofImage& title) const;

	const Menu& source_;
};



#endif /* SRC_GAME_MENU_MENUVIEW_H_ */
