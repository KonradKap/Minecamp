/*
 * PathManager.h
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#ifndef SRC_PATHMANAGER_H_
#define SRC_PATHMANAGER_H_

#include <string>
#include <map>

#include "ofUtils.h"


template<class T>
class PathManager
{
public:
	virtual ~PathManager();

	const std::string get(const T arg) const;
protected:
	PathManager(const std::map<const T, const std::string>& map);

	inline static std::string texture(const std::string& target);
	inline static std::string font(const std::string& target);
	inline static std::string block(const std::string& target);
private:

	PathManager() = delete;
	PathManager(const PathManager& p) = delete;

	const std::map<const T, const std::string> paths_;
};

#include "Utill/PathManager.hpp"


#endif /* SRC_PATHMANAGER_H_ */
