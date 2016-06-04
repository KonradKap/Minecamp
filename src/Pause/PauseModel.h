/*
 * Pause.h
 *
 *  Created on: 3 cze 2016
 *      Author: konrad
 */

#ifndef SRC_PAUSE_PAUSEMODEL_H_
#define SRC_PAUSE_PAUSEMODEL_H_

#include <vector>

#include "Button/Button.h"
#include "Button/ButtonPrototype.h"
#include "Button/ButtonPrototypeLoader.h"
#include "ofImage.h"

#include "Game/Model.h"
#include "Game/GameState.h"
#include "PausePathManager.h"

class PauseModel : public Model
{
public:
	enum class ButtonType
	{
		SAVE_AND_QUIT,
		NO_SAVE_QUIT,
		RESUME,
		COUNT
	};

	PauseModel(/*GameState previousState*/);
	~PauseModel();

	const std::array<Button, unsigned(ButtonType::COUNT)>& getButtons() const;
	const ofImage& getBackground() const;

	static const int FONT_SIZE = 14;
	static const int BUTTON_SET_Y = 200;
	static const int BUTTON_OFFSET_Y = 10;

	ofEvent<GameState>& getPauseBreakEvent();
private:
	void onButtonPress(const Button& b);

	void registerMe(const do_register_trait&);
	void unregisterMe(const do_register_trait&);

	void setupPaths();
	void setupButtons();

	ButtonPrototype prototype_;
	std::array<Button, unsigned(ButtonType::COUNT)> buttons_;

	ofImage background_;

	//GameState previousState_;
	//ofEvent<GameState>& pauseBreakEvent_;
};



#endif /* SRC_PAUSE_PAUSEMODEL_H_ */
