/*
 * View.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_VIEW_H_
#define SRC_VIEW_H_

#include "ofVec3f.h"
#include "ofEvents.h"

class ofEventArgs;

class View
{
public:
	View();
	virtual ~View();

	static ofVec3f xAxis();
	static ofVec3f yAxis();
	static ofVec3f zAxis();
private:
	virtual void onDraw(ofEventArgs&) = 0;
};




#endif /* SRC_VIEW_H_ */
