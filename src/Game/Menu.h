/*
 * Menu.h
 *
 *  Created on: 11 mar 2016
 *      Author: konrad
 */

#ifndef SRC_GAME_MENU_H_
#define SRC_GAME_MENU_H_

#include "ofImage.h"
#include "ofApp.h"
#include "ofEvents.h"

#include "GameState.h"
#include "ButtonModel.h"
#include "Button.h"

class Menu : public GameState
{
public:
	Menu();
	//Menu(const Menu& m);
	virtual ~Menu();

	GameState* update(float elapsed_time);
	void handleInput();
	void draw() const;

	const int TITLE_OFFSET = 50;
	const int BUTTON_OFFSET = 25;
	const int BUTTONSET_OFFSET = 250;
private:
	void onPlayPressed();
	void onQuitPressed();

	enum Option
	{
		NOTHING,
		PLAY,
		QUIT,
		COUNT
	};
	Option chosen_option_;

	ofImage background_;
	ofImage title_;

	ButtonModel model_;
	Button play_button_;
	Button quit_button_;
};




#endif /* SRC_GAME_MENU_H_ */
