/*
 * View.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_VIEW_H_
#define SRC_VIEW_H_

class View
{
public:
	virtual ~View() {}

	virtual void draw() const = 0;
};




#endif /* SRC_VIEW_H_ */
