//
//  Canvas.h
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#ifndef __performance__Canvas__
#define __performance__Canvas__

#include <iostream>
#include "ofMain.h"

#include "Stroke.h"
#include "TurtleStroke.h"
#include "ParticleStroke.h"
#include "RepeatableStroke.h"
#include "SpringStroke.h"
#include "DropEmitter.h"

class Canvas
{
public:
    Canvas();
    ~Canvas();
    void setup(float width, float height);
    
    void update();
    void draw();
    
    void doCut(const ofVec2f& p, const ofVec2f& q);

    void clear();
    
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseMoved(int x, int y);
    void keyPressed(int key);
    
    void releaseAllParticles();
    void releaseAllStrokes();
    
    void undo();
    
    // parameters
    int nStrokes;
    int strokeControlIndex;
    
    float noiseLevel;
    float noiseRate;
    float noiseSpatialRate;
    float randomLevel;
    float xFrequency;
    float xAmplitude;
    
    int strokeType;
    void setStroke(int key) { strokeType = key-'1'; }

private:
    
    void handleControlMessages();
    float prevRandomRelease = 0;
    
    vector<int> history;
    
    ofVec2f size;
    
    ofImage bgImg;
    
    vector<SpringStroke*> strokes;
    SpringStroke* currentStroke;
//    vector<TurtleStroke*> turtleStrokes;
    vector<ParticleStroke*> particleStrokes;
    ParticleStroke* currentParticleStroke;

    vector<RepeatableStroke*> repeatableStrokes;
    RepeatableStroke* currentRepeatableStroke;

    vector<SpringStroke*> springStrokes;
    SpringStroke* currentSpringStroke;
    
    vector<SpringStroke*> surfaceStrokes;
    SpringStroke* currentSurfaceStroke;
    
    vector<DropEmitter*> emitters;
    
    ofVec2f noiseTime;
    
    ofVec2f blade;
    ofVec2f bladePrev;

    ofVec2f repeatableAnchor;
    
    FlowField flowField;
    
    bool bShowFlowfield;
    
    ofVec2f getPointWithNoise(ofVec2f *p, int index = 0);
};

#endif /* defined(__performance__Canvas__) */
