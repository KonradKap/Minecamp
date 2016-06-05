/*
 * Controller.cc
 *
 *  Created on: 4 cze 2016
 *      Author: konrad
 */

#include "Game/Controller.h"
#include "ofAppGLFWWindow.h"
#include "ofApp.h"

void Controller::setCursorOnMiddle()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(ofGetWindowPtr()->getWindowContext());
	glfwSetCursorPos(window, ofApp::WINDOW_X_SIZE/2 ,ofApp::WINDOW_Y_SIZE/2);
}

Controller::~Controller()
{

}


