#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSeedRandom();
    ofSetFrameRate(60);
	ofHideCursor();
//    ofSetVerticalSync(false);
//    CGDisplayHideCursor(NULL);

//    ofEnableSmoothing();
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    
//    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    
    control.setup("Performance", 6000);
    
//    control.addOutput("nStrokes", &canvas.nStrokes);
    control.addInput("Noise Level", &canvas.noiseLevel);
    control.addInput("Noise Rate", &canvas.noiseRate);
    control.addInput("Noise Spatial Rate", &canvas.noiseSpatialRate);
    control.addInput("Random Level", &canvas.randomLevel);
    control.addInput("X Frequency", &canvas.xFrequency);
    control.addInput("X Amplitude", &canvas.xAmplitude);
    control.addInput("Angle Offset", &Params::angleOffset);
    control.addInput("Angle Offset Per Index", &Params::angleOffsetPerIndex);
    control.addInput("lengthScale", &Params::lengthScale);
    control.addInput("lengthIndexScale", &Params::lengthIndexScale);
    
    control.addInput("Repeat Times", &Params::repeatTimes);
    control.addInput("Repeat rotation", &Params::repeatRotateCoeff);
    control.addInput("Repeat trans X", &Params::repeatTransXCoeff);
    control.addInput("Repeat trans Y", &Params::repeatTransYCoeff);
    control.addInput("Repeat scale X", &Params::repeatScaleXCoeff);
    control.addInput("Repeat scale Y", &Params::repeatScaleYCoeff);
    
    control.addInput("Spring gravity.x", &Params::springGravity.x);
    control.addInput("Spring gravity.y", &Params::springGravity.y);
    control.addInput("Spring temporal force.x", &Params::springTemporalForce.x);
    control.addInput("Spring temporal force.y", &Params::springTemporalForce.y);
    control.addInput("Sprint rest length factor", &Params::springRestLengthFactor);
    control.addInput("Spring force factor", &Params::springForceFactor);
    control.addInput("Spring coeff", &Params::springCoeff);
    control.addInput("Particle max speed", &Params::particleMaxSpeed);
    control.addInput("Particle friction coeff", &Params::particleFrictionCoeff);
    control.addInput("Particle temporal velocity", &Params::particleTemporalVelocity);
    control.addInput("Particle gravity", &Params::particleGravity);
    control.addInput("Particle flowfield force", &Params::particleFlowfieldForce);
    control.addInput("Global release", &Params::globalReleaseAmount);
    control.addInput("Line noise", &Params::lineNoise);
    
    control.addInput("Color mode", &Params::colorMode);
    control.addInput("Surface color", &Params::surfaceColor);
    control.addInput("Random particle colos", &Params::randomParticleColors);
    
    
    //## DROP EMITTER ##
    control.addInput("ParticleEmitter emission rate", &Params::emissionSpeed);
    control.addInput("ParticleEmitter radius", &Params::emissionRadius);
    control.addInput("Particle life", &Params::dropLife);
    control.addInput("Particle Size", &Params::dropSize);
    control.addInput("Particle color", &Params::dropColor);
    control.addInput("Friction Coeff", &Params::frictionCoeff);
    control.addInput("Max Initial Vel", &Params::maxInitialForce);
    control.addInput("Gravity", &Params::gravity);
    
    
    canvas.setup(ofGetWindowWidth(), ofGetWindowHeight());
    
    toolBox.setup(ofVec2f(0, 0));
    
    cout<<"Window size = "<<ofGetWindowWidth()<<"x"<<ofGetWindowHeight()<<endl;
    counter = 0;
    bDisplayToolbox = true;
    
    bUseSyphon = false;
#ifdef USE_SYPHON
    if (bUseSyphon) {
        syphonFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
        mainOutputSyphonServer.setName("Sketch Performance");
    }
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
    canvas.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
#ifdef USE_SYPHON
    if (bUseSyphon) {
        syphonFbo.begin();
    }
#endif

    canvas.draw();
    
    if (Params::colorMode == 0) {
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    }
    else {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    
    if (bDisplayToolbox) {
        toolBox.draw();
    }
    
    ofDisableBlendMode();

#ifdef USE_SYPHON
    if (bUseSyphon) {
        syphonFbo.end();
        mainOutputSyphonServer.publishTexture(&syphonFbo.getTextureReference());
        syphonFbo.draw(0, 0);
    }
#endif

//    stringstream ss;
//    ss << ofGetFrameRate();
//    ofDrawBitmapString(ss.str(), 0, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "key pressed: "<<key<<endl;
    
    if (key >= '1' &&
        key <= '7') {
        toolBox.currentTool = key - '1';
        canvas.setStroke(key);
    }
    else if (key == 'h') {
        bDisplayToolbox = !bDisplayToolbox;
    }
    if (key == 'e') {
        if (Params::randomParticleColors == 0) {
            Params::randomParticleColors = 8;
        }
        else {
            Params::randomParticleColors = 0;
        }
    }
    
    canvas.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    canvas.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    canvas.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (toolBox.contains(ofVec2f(x, y))) {
        int pressed = toolBox.getButton(ofVec2f(x, y));
        if (pressed <= 5) {
            toolBox.currentTool = pressed;
            canvas.strokeType = pressed;
        }
        else if (pressed == 6) {
            canvas.releaseAllStrokes();
        }
        else if (pressed == 7) {
            canvas.releaseAllParticles();
        }
    }
    else {
        canvas.mousePressed(x, y, button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    canvas.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
