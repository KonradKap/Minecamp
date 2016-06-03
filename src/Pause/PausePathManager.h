/*
 * PauseFileManager.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PAUSE_PAUSEPATHMANAGER_H_
#define SRC_PAUSE_PAUSEPATHMANAGER_H_

#include "Utill/PathManager.h"

enum class PauseResources
{
	BACKGROUND_T,
	BUTTON_D,
	FONT_F
};

class PausePathManager : public PathManager<const PauseResources>
{
public: //maybe we do different textures
	PausePathManager() :
		PathManager<const PauseResources>(std::map<const PauseResources, const std::string>(
				{
						{PauseResources::BACKGROUND_T, texture("background_2.png")},
						{PauseResources::BUTTON_D, ofFilePath::addTrailingSlash(texture("menu_button_2"))},
						{PauseResources::FONT_F, font("menu_font.ttf")}
				}
		))
	{
	}
	~PausePathManager() {}
};




#endif /* SRC_PAUSE_PAUSEPATHMANAGER_H_ */
