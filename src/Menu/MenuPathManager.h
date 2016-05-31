/*
 * MenuPathManager.h
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MENU_MENUPATHMANAGER_H_
#define SRC_GAME_MENU_MENUPATHMANAGER_H_

#include "PathManager.h"

enum class MenuResources
{
	BACKGROUND_T,
	TITLE_T,
	WIDE_BUTTON_D,
	SMALL_BUTTON_D,
	FONT_F
};

class MenuPathManager : public PathManager<const MenuResources>
{
public:
	MenuPathManager() :
		PathManager<const MenuResources>(std::map<const MenuResources, const std::string>(
				{
						{MenuResources::BACKGROUND_T, texture("background_2.png")},
						{MenuResources::TITLE_T, texture("title.png")},
						{MenuResources::WIDE_BUTTON_D, ofFilePath::addTrailingSlash(texture("menu_button_2"))},
						{MenuResources::SMALL_BUTTON_D, ofFilePath::addTrailingSlash(texture("small_button"))},
						{MenuResources::FONT_F, font("menu_font.ttf")}
				}
		))
	{
	}
	~MenuPathManager() {}
};



#endif /* SRC_GAME_MENU_MENUPATHMANAGER_H_ */
