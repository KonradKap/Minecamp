/*
 * Menu.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MENU_H_
#define SRC_GAME_MENU_H_

#include <memory>

#include "ofImage.h"
#include "ofApp.h"
#include "ofEvents.h"

#include "Game/GameState.h"
#include "Play/Play.h"
#include "Menu/ButtonModel.h"
#include "Menu/Button.h"
#include "Menu/MenuPathManager.h"

class MenuView;

class Menu : public GameState
{
public:
	enum class ButtonType
	{
		PLAY,
		QUIT,
		COUNT
	};
	Menu();
	virtual ~Menu();

	void update(float elapsed_time);

	const ofImage& getBackground() const;
	const ofImage& getTitle() const;
	const Button& getButton(const ButtonType type) const;
	std::unique_ptr<View> getDefaultView() const;

	static const int FONT_SIZE = 14;
	static const int TITLE_OFFSET = 50;
	static const int BUTTON_OFFSET = 25;
	static const int BUTTONSET_OFFSET = 250;
private:
	void onPlayPressed();
	void onQuitPressed();

	void setUpPaths();
	void setUpButtons();

	ofImage background_;
	ofImage title_;

	ButtonModel model_;
	std::array<Button, unsigned(ButtonType::COUNT)> buttons_;
};

#include "Menu/MenuView.h"


#endif /* SRC_GAME_MENU_H_ */
