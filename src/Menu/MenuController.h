/*
 * MenuController.h
 *
 *  Created on: 1 cze 2016
 *      Author: konrad
 */

#ifndef SRC_MENU_MENUCONTROLLER_H_
#define SRC_MENU_MENUCONTROLLER_H_

#include "Game/Controller.h"

class MenuModel;

class MenuController : public Controller
{
public:
	MenuController(MenuModel& model) {}

	void registerMe(const do_register_trait&) {}
	void unregisterMe(const do_register_trait&) {}
};



#endif /* SRC_MENU_MENUCONTROLLER_H_ */
