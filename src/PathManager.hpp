/*
 * PathManager.hpp
 *
 *  Created on: 17 mar 2016
 *      Author: konrad
 */

#ifndef SRC_PATHMANAGER_HPP_
#define SRC_PATHMANAGER_HPP_

#include "PathManager.h"

template<class T>
PathManager<T>::~PathManager()
{
}

template<class T>
const std::string PathManager<T>::get(const T arg) const
{
	return paths_.at(arg);
}
/*
template<class T>
std::string PathManager<T>::resources()
{
	//return ofFilePath::join("..", "resources");
	return ofFilePath::join(ofFilePath::getCurrentWorkingDirectory(), "resources");
}
*/
template<class T>
std::string PathManager<T>::texture(const std::string& target)
{
	return ofFilePath::join("textures", target);
}

template<class T>
std::string PathManager<T>::font(const std::string& target)
{
	return ofFilePath::join("fonts", target);
}

template<class T>
std::string PathManager<T>::block(const std::string& target)
{
	return ofFilePath::join("blocks", target);
}
/*
template<class T>
std::string PathManager<T>::dir(const std::string& target)
{
	return ofFilePath::join(resources(), target);
}
*/
template<class T>
PathManager<T>::PathManager(const std::map<const T, const std::string>& map) :
	paths_(map)
	{
	}



#endif /* SRC_PATHMANAGER_HPP_ */
