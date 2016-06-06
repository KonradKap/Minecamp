/*
 * Menu.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MENU_H_
#define SRC_GAME_MENU_H_

#include <memory>

#include "Button/Button.h"
#include "Button/ButtonPrototype.h"
#include "Button/ButtonPrototypeLoader.h"
#include "ofImage.h"
#include "ofEvents.h"

#include "Game/Model.h"
#include "Menu/MenuPathManager.h"

class MenuView;

//TODO: Delete save buttons
class MenuModel : public Model
{
public:
	enum class MenuState
	{
		MAIN,
		LEVEL_SELECT,
		PAUSE,
		COUNT
	};

	MenuModel(MenuState starting_state);
	virtual ~MenuModel();

	const ofImage& getBackground() const;
	const ofImage& getTitle() const;
	const std::vector<Button>& getButtons() const;

	static const int FONT_SIZE = 14;
	static const int TITLE_OFFSET = 50;
	static const int BUTTON_OFFSET = 25;
	static const int BUTTONSET_OFFSET = 250;

	static const int MAIN_BUTTON_COUNT = 2;
	static const int PAUSE_BUTTON_COUNT = 3;
	static const int SELECT_WIDE_BUTTON_COUNT = 6;
	static const int SELECT_SMALL_BUTTON_COUNT = 5;

	static const int SELECT_BUTTON_COUNT = SELECT_WIDE_BUTTON_COUNT + SELECT_SMALL_BUTTON_COUNT;
private:


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
		SAVE_AND_QUIT,
		NO_SAVE_QUIT,
		RESUME,
		COUNT
	};

	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	void switchState(MenuState new_state);
	void switchToMain();
	void switchToLevelSelect();
	void switchToPause();

	void onButtonPress(const Button& pressed);

	void onPlayPressed();
	void onLevelSelect(const Button& pressed);
	void onQuitPressed();
	void onLevelDeletion(const Button& pressed);

	void onSaveAndQuitPressed();
	void onNoSaveAndQuitPressed();
	void onResumePressed();

	void setUpPaths();
	void setUpButtons(const std::vector<std::string>& titles);
	void setUpSmallButtons(const std::string& title);

	MenuState state_;

	static const std::array<std::string, MenuButtonTitles::COUNT> TITLES_;

	ofImage background_;
	ofImage title_;

	ButtonPrototype wide_model_;
	ButtonPrototype small_model_;
	std::vector<Button> buttons_;
};

#include "MenuView.h"


#endif /* SRC_GAME_MENU_H_ */
