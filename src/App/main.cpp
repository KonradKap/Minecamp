#include "ofMain.h"
#include "ofApp.h"

#include <iostream>

//========================================================================
int main( )
{
	ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.width = ofApp::WINDOW_X_SIZE;
	settings.height = ofApp::WINDOW_Y_SIZE;
	ofCreateWindow(settings);

	//ofDisableBlendMode();
	ofRunApp(new ofApp());
}
