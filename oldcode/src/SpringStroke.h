//
//  SpringStroke.h
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#ifndef __performance__SpringStroke__
#define __performance__SpringStroke__

#include <iostream>
#include "ofMain.h"
#include "Params.h"
#include "SmoothLine.h"
#include "Spring.h"
#include "FlowField.h"
#include "PaintDrop.h"

class SpringStroke
{
    
public:
    
    SpringStroke();
    ~SpringStroke();
    void setLockDistance(float distance);
    void addPoint(float x, float y);
    void update();
    void draw();
    void drawSurface();
    void dropColor(const ofColor& c);
    void releaseAnchors();
    
    void setupParticleEmitters();
    
    vector<Particle*>& getPoints() { return line->getPoints(); }
    ofVec2f getLastPoint();
    
    int getIntersection(const ofVec2f& p, const ofVec2f& q);
    SpringStroke* cutStroke(int index);

    bool bEmitter;

private:
    bool isIntersects(const ofVec2f& p, const ofVec2f& p2,
                     const ofVec2f& q, const ofVec2f& q2);
    float crossProduct(const ofVec2f& p, const ofVec2f& q);
    
    float lockDistance;
    SmoothLine* line;
    vector<Spring*> springs;
    
    vector<PaintDrop*> paintDrops;
    
    
    ofColor color;
};


#endif /* defined(__performance__SpringStroke__) */
