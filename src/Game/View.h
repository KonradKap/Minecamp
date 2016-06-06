/*
 * View.h
 *
 *  Created on: 22 kwi 2016
 *      Author: konrad
 */

#ifndef SRC_VIEW_H_
#define SRC_VIEW_H_

#include "../Button/Button.h"
#include "ofVec3f.h"
#include "ofEvents.h"

#include "Utill/Registrable.h"

class ofEventArgs;

class View : public Registrable
{
public:
	View();
	virtual ~View();

	static ofVec3f xAxis();
	static ofVec3f yAxis();
	static ofVec3f zAxis();

protected:
	void drawButton(const Button& button) const;

private:
	virtual void registerMe(const do_register_trait&);
	virtual void unregisterMe(const do_register_trait&);

	virtual void onDraw(ofEventArgs&) = 0;
};



#endif /* SRC_VIEW_H_ */
