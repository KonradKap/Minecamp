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

//TODO: Delete save buttons
class Menu : public GameState
{
public:
	//enum class ButtonType
	//{
	//	PLAY,
	//	QUIT,
	//	LEVEL_SELECT,
	//	COUNT
	//};
	Menu();
	virtual ~Menu();

	void update(float elapsed_time);

	const ofImage& getBackground() const;
	const ofImage& getTitle() const;
	const std::vector<Button>& getButtons() const;
	std::unique_ptr<View> getDefaultView() const;

	static const int FONT_SIZE = 14;
	static const int TITLE_OFFSET = 50;
	static const int BUTTON_OFFSET = 25;
	static const int BUTTONSET_OFFSET = 250;

	static const int MAIN_BUTTON_COUNT = 2;
	static const int SELECT_WIDE_BUTTON_COUNT = 6;
	static const int SELECT_SMALL_BUTTON_COUNT = 5;

	static const int SELECT_BUTTON_COUNT = SELECT_WIDE_BUTTON_COUNT + SELECT_SMALL_BUTTON_COUNT;
private:
	enum class MenuState
	{
		MAIN,
		LEVEL_SELECT,
		COUNT
	};

	enum MenuButtonTitles
	{
		PLAY,
		QUIT,
		SELECT_1,
		SELECT_2,
		SELECT_3,
		SELECT_4,
		SELECT_5,
		RETURN,
		DELETE,
		COUNT
	};

	void switchState(MenuState new_state);
	void switchToMain();
	void switchToLevelSelect();

	void onButtonPress(const Button& pressed);

	void onPlayPressed();
	void onLevelSelect(const Button& pressed);
	void onQuitPressed();
	void onLevelDeletion(const Button& pressed);

	void setUpPaths();
	void setUpButtons(const std::vector<std::string>& titles);
	void setUpSmallButtons(const std::string& title);

	MenuState state_;

	const std::array<std::string, MenuButtonTitles::COUNT> TITLES_;

	ofImage background_;
	ofImage title_;

	ButtonModel wide_model_;
	ButtonModel small_model_;
	std::vector<Button> buttons_;
};

#include "Menu/MenuView.h"


#endif /* SRC_GAME_MENU_H_ */
