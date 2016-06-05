/*
 * SaveFileManager.h
 *
 *  Created on: 31 maj 2016
 *      Author: konrad
 */

#ifndef SRC_PLAY_SAVEFILEMANAGER_H_
#define SRC_PLAY_SAVEFILEMANAGER_H_

#include <iostream>

class PlayModel;

class SaveFileManager
{
public:
	SaveFileManager(int save_state, PlayModel& source);

	void load();
	void save() const;
	static bool clear(int save_state);

private:
	void loadPlayer(std::istream& file);
	void loadPlayerPosition(std::istream& file);
	void loadPlayerDirection(std::istream& file);
	void savePlayer(std::ostream& file) const;
	static std::string getSaveFileName(int save_state);

	int save_state_;
	PlayModel& source_;

};




#endif /* SRC_PLAY_SAVEFILEMANAGER_H_ */
