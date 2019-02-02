//
//  Canvas.cpp
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#include "Canvas.h"

Canvas::Canvas()
{
    size = ofVec2f(0, 0);
    currentParticleStroke = NULL;
    currentRepeatableStroke = NULL;
    currentSpringStroke = NULL;
    
    nStrokes = 0;
    strokeControlIndex = 0;
    
    noiseTime.x = ofRandom(10000);
    noiseTime.y = ofRandom(10000);
    noiseRate = 0;
    randomLevel = 0;
    strokeType = 0;
    bShowFlowfield = false;
    
    RepeatableStroke::initTransformations();
}

Canvas::~Canvas()
{
    clear();
}

void Canvas::setup(float width, float height)
{
    size = ofVec2f(width, height);
    
    bgImg.loadImage("bgtexture.jpg");
    
    flowField.setup(width, height, 300, 300);
}

void Canvas::update()
{
    noiseTime.x += noiseRate/10;
    noiseTime.y += noiseRate/10;
    
//    handleControlMessages();
    
    // update spring strokes and flow field
    flowField.reset();
    for (int i=0; i<springStrokes.size(); i++)
    {
        springStrokes[i]->update();
        flowField.applyStrokeForces(springStrokes[i]->getPoints());
    }
    if (currentSpringStroke) {
        flowField.applyStrokeForces(currentSpringStroke->getPoints());
    }
    
    // update surfaces
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        surfaceStrokes[i]->update();
    }
    
    // update PARTICLE stroke
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->applyFlowField(flowField);
        particleStrokes[i]->update();
    }
    
    for (int i=0; i<repeatableStrokes.size(); i++)
    {
        repeatableStrokes[i]->update();
    }
    if (currentRepeatableStroke) {
        currentRepeatableStroke->update();
    }
    
    for (int i=0; i<emitters.size(); i++)
    {
        emitters[i]->update();
    }
//    if (currentParticleStroke) {
//        currentParticleStroke->applyFlowField(flowField);
//        currentParticleStroke->update();
//    }
    
//    flowField.update();
}

void Canvas::draw()
{
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(ResourceManager::getInstance().getBackgroundColor());
    ofFill();
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofDisableBlendMode();
    
//    bgImg.draw(0, 0);

    if (Params::colorMode == 0)
    {
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    }
    else {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    
    // Draw normal strokes (#1)
    for (int i=0; i<strokes.size(); i++)
    {
        strokes[i]->draw();
    }
    if (currentStroke) {
        currentStroke->draw();
    }
    
    // Draw surface strokes (#2)
    ofSetColor(Params::surfaceColor);
    ofFill();
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        surfaceStrokes[i]->drawSurface();
    }
    if (currentSurfaceStroke) {
        currentSurfaceStroke->drawSurface();
    }

    // Draw particle strokes (#3)
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->draw();
    }
    if (currentParticleStroke) {
        currentParticleStroke->draw();
    }
    
    // Draw repeatable strokes (#4)
    for (int i=0; i<repeatableStrokes.size(); i++)
    {
        repeatableStrokes[i]->draw();
    }
    if (currentRepeatableStroke) {
        currentRepeatableStroke->draw();
    }

    // Draw spring strokes (#5)
    for (int i=0; i<springStrokes.size(); i++)
    {
        springStrokes[i]->draw();
    }
    if (currentSpringStroke) {
        currentSpringStroke->draw();
    }
    
    // Draw particle emitters (#7)
    for (int i=0; i<emitters.size(); i++)
    {
        emitters[i]->draw();
    }
    
    // Draw flow field ('f')
    if (bShowFlowfield) {
        flowField.draw();
    }

    
    // draw cursor
    ofSetColor(ResourceManager::getInstance().getStrokeColor());
    ofNoFill();
    if (strokeType == 4) {
        ofDrawLine(ofGetMouseX()-7, ofGetMouseY()-7, ofGetMouseX()+7, ofGetMouseY()+7);
        ofDrawLine(ofGetMouseX()+7, ofGetMouseY()-7, ofGetMouseX()-7, ofGetMouseY()+7);
        ofDrawLine(bladePrev, blade);
    }
    else {
        ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), 15, 15);
    }
    
    ofDisableBlendMode();

}

void Canvas::doCut(const ofVec2f &p, const ofVec2f &q)
{
    for (int i=0; i<springStrokes.size(); i++)
    {
        int index = springStrokes[i]->getIntersection(p, q);
        if (index < 0) {
            continue;
        }
        
        // do the cut
        SpringStroke *newStroke = springStrokes[i]->cutStroke(index);
        springStrokes.push_back(newStroke);
        history.push_back(4);
    }
}

void Canvas::clear()
{
    for (int i=0; i<strokes.size(); i++)
    {
        delete strokes[i];
    }
    strokes.clear();
    if (currentStroke) {
        delete currentStroke;
        currentStroke = NULL;
    }
    
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        delete surfaceStrokes[i];
    }
    surfaceStrokes.clear();
    
    for (int i=0; i<particleStrokes.size(); i++)
    {
        delete particleStrokes[i];
    }
    particleStrokes.clear();
    
    for (int i=0; i<repeatableStrokes.size(); i++)
    {
        delete repeatableStrokes[i];
    }
    repeatableStrokes.clear();
    for (int i=0; i<springStrokes.size(); i++)
    {
        delete springStrokes[i];
    }
    springStrokes.clear();
    for (int i=0; i<emitters.size(); i++)
    {
        delete emitters[i];
    }
    emitters.clear();
    
    if (currentSurfaceStroke) {
        delete currentSurfaceStroke;
        currentSurfaceStroke = NULL;
    }
    if (currentParticleStroke) {
        delete currentParticleStroke;
        currentParticleStroke = NULL;
    }
    if (currentRepeatableStroke) {
        delete currentRepeatableStroke;
        currentRepeatableStroke = NULL;
    }
    if (currentSpringStroke) {
        delete currentSpringStroke;
        currentSpringStroke = NULL;
    }
    
    flowField.reset();
}

void Canvas::mousePressed(int x, int y, int button)
{
    if (strokeType == 0)
    {
        currentSpringStroke = new SpringStroke();
        currentSpringStroke->setLockDistance(50);
        currentSpringStroke->addPoint(x, y);
    }
    else if (strokeType == 3) {
        currentSurfaceStroke = new SpringStroke();
        currentSurfaceStroke->setLockDistance(50);
        currentSurfaceStroke->addPoint(x, y);
    }
    else if (strokeType == 2) {
        currentParticleStroke = new ParticleStroke();
        currentParticleStroke->addPoint(ofVec2f(x, y));
    }
    else if (strokeType == 5) {
        if (repeatableStrokes.size() == 0) {
            repeatableAnchor = ofVec2f(x, y);
        }
        
        currentRepeatableStroke = new RepeatableStroke();
        currentRepeatableStroke->setAnchor(repeatableAnchor.x, repeatableAnchor.y);
        currentRepeatableStroke->addPoint(x, y);
    }
    else if (strokeType == 1) {
        currentSpringStroke = new SpringStroke();
        currentSpringStroke->addPoint(x, y);
    }
    else if (strokeType == 4) {
        // this is the blade that cuts
        blade = bladePrev = ofVec2f(x, y);
    }
    else if (strokeType == 6) {
        DropEmitter *de = new DropEmitter();
        de->setup(ofVec2f(x, y));
        emitters.push_back(de);
        history.push_back(6);
    }
}

void Canvas::mouseDragged(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentSpringStroke) {
            currentSpringStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 3) {
        if (currentSurfaceStroke) {
            currentSurfaceStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 2) {
        if (currentParticleStroke) {
            for (int i=0; i<10; i++) {
                currentParticleStroke->addPoint(ofVec2f(x+ofRandom(20)-10, y+ofRandom(20)-10));
            }
        }
    }
    else if (strokeType == 5) {
        if (currentRepeatableStroke) {
            currentRepeatableStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 1) {
        if (currentSpringStroke) {
            currentSpringStroke->addPoint(x, y);
        }
    }
    else if (strokeType == 4) {
        // blade
        bladePrev = blade;
        blade = ofVec2f(x, y);
        doCut(bladePrev, blade);
    }
    else if (strokeType == 6) {
        DropEmitter *de = new DropEmitter();
        de->setup(ofVec2f(x, y));
        emitters.push_back(de);
        history.push_back(6);
    }
}

void Canvas::mouseReleased(int x, int y, int button)
{
    if (strokeType == 0)
    {
        if (currentSpringStroke) {
            springStrokes.push_back(currentSpringStroke);
            currentSpringStroke = NULL;
            history.push_back(4);
        }
    }
    else if (strokeType == 3) {
        if (currentSurfaceStroke) {
            surfaceStrokes.push_back(currentSurfaceStroke);
            currentSurfaceStroke = NULL;
            history.push_back(1);
        }
    }
    else if (strokeType == 2) {
        if (currentParticleStroke) {
            particleStrokes.push_back(currentParticleStroke);
            currentParticleStroke = NULL;
            history.push_back(2);
        }
    }
    else if (strokeType == 5) {
        if (currentRepeatableStroke) {
            repeatableStrokes.push_back(currentRepeatableStroke);
            currentRepeatableStroke = NULL;
            history.push_back(3);
        }
    }
    else if (strokeType == 1) {
        if (currentSpringStroke) {
            springStrokes.push_back(currentSpringStroke);
            currentSpringStroke = NULL;
            history.push_back(4);
        }
    }
}

void Canvas::mouseMoved(int x, int y)
{
//    if (strokeType == 5) {
//        // blade
//        bladePrev = blade;
//    }
}

void Canvas::keyPressed(int key)
{
    if (key == 'r') {
        releaseAllParticles();
    }
    else if (key == ' ') {
        bShowFlowfield = !bShowFlowfield;
    }
    else if (key == 'c') {
        clear();
    }
    else if (key == 'd') {
        releaseAllStrokes();
    }
    else if (key == 'z') {
        undo();
    }
    else if (key == 'a') {
        Params::colorMode = (Params::colorMode)?0:1;
    }
    else if (key == 'p') {
        // make spring strokes emit particles
        for (int i=0; i<springStrokes.size(); i++)
        {
            springStrokes[i]->setupParticleEmitters();
        }
        for (int i=0; i<strokes.size(); i++)
        {
            strokes[i]->setupParticleEmitters();
        }
    }
    else if (key == 'q') {
        if (Params::randomParticleColors>0) {
            Params::randomParticleColors = 0;
        }
        else {
            Params::randomParticleColors = 8;
        }
    }
	else if (key == 'f') {
		bool currentState = (ofGetScreenSize() == ofGetWindowSize());
		ofSetFullscreen(!currentState);
		if (currentState) {
			ofSetWindowShape(800, 600);
		}
	}
}

void Canvas::releaseAllParticles()
{
    for (int i=0; i<particleStrokes.size(); i++)
    {
        particleStrokes[i]->releaseAllParticles();
    }
}

void Canvas::releaseAllStrokes()
{
    for (int i=0; i<springStrokes.size(); i++)
    {
        springStrokes[i]->releaseAnchors();
    }
    for (int i=0; i<surfaceStrokes.size(); i++)
    {
        surfaceStrokes[i]->releaseAnchors();
    }
}

void Canvas::undo()
{
    if (history.empty()) {
        return;
    }
    
    int lastStroke = history[history.size()-1];
    switch (lastStroke)
    {
        case 1:
            delete surfaceStrokes[surfaceStrokes.size()-1];
            surfaceStrokes.pop_back();
            break;
        case 2:
            delete particleStrokes[particleStrokes.size()-1];
            particleStrokes.pop_back();
            break;
        case 3:
            delete repeatableStrokes[repeatableStrokes.size()-1];
            repeatableStrokes.pop_back();
            break;
        case 4:
            delete springStrokes[springStrokes.size()-1];
            springStrokes.pop_back();
            break;
        case 6:
            delete emitters[emitters.size()-1];
            emitters.pop_back();
            break;
        default:
            break;
    }
    
    history.pop_back();
}

ofVec2f Canvas::getPointWithNoise(ofVec2f *p, int index)
{
    float time = noiseTime.x + index*noiseSpatialRate;

    return ofVec2f(p->x + (ofNoise(time)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel + sin(xFrequency*index)*xAmplitude,
                   p->y + (ofNoise(time + 1000)-0.5f)*noiseLevel + ofRandom(-0.5, 0.5)*randomLevel);
}
