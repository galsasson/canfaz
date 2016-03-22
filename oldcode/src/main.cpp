#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(600, 600, OF_WINDOW);
	ofSetupOpenGL(1920,1080,OF_FULLSCREEN);			// <-------- setup the GL
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());

}
