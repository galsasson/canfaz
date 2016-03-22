//
//  FlowField.h
//  performance
//
//  Created by Gal Sasson on 4/17/14.
//
//

#ifndef __performance__FlowField__
#define __performance__FlowField__

#include <iostream>
#include "ofMain.h"
#include "Utilities.h"
#include "Particle.h"
#include "FlowFieldForce.h"

class FlowField
{
public:
    FlowField();
    ~FlowField();
    void setup(int w, int h, int nWidth, int nHeight);
    void update();
    void draw();
    
    void reset();
    
    void addAttractor(ofVec2f p, float rad, float force);
    void addForce(ofVec2f p, float rad, ofVec2f force);
    void addRepulsion(const ofVec2f& p, float rad, float strength=1);
    void addLineRepulsion(const ofVec2f& p, const ofVec2f& q, float strength);
    
    void applyStrokeForces(const vector<Particle*>& points);
    ofVec2f getForce(const ofVec2f& p) const;
    
private:
    int nWidth, nHeight;
    ofVec2f size;
    ofVec2f squareSize;
    float squareLength;
    FlowFieldForce **field;
    
    void drawArrow(ofVec2f s, ofVec2f t);
};

#endif /* defined(__performance__FlowField__) */
