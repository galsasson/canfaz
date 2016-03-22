#pragma once

#include <sstream>

#include "ofMain.h"
#include "ofxControlease.h"
#include "Params.h"
#include "Canvas.h"
#include "FlowField.h"
#include "ToolBox.h"

#ifdef USE_SYPHON
#include "ofxSyphon.h"
#endif

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofxControlease control;
    
    Canvas canvas;
    FlowField flowField;
    ToolBox toolBox;
    bool bDisplayToolbox;
    
    int counter;

	bool bUseSyphon;
#ifdef USE_SYPHON
    ofFbo syphonFbo;
    ofxSyphonServer mainOutputSyphonServer;
#endif
};
