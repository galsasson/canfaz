//
//  RainDrop.h
//  ofxControlEase_example
//
//  Created by Gal Sasson on 5/1/14.
//
//

#ifndef __ofxControlEase_example__RainDrop__
#define __ofxControlEase_example__RainDrop__

#include <iostream>
#include "Params.h"
#include "ofMain.h"

class RainDrop
{
public:
    RainDrop();
    void setup(const ofVec2f& p);
    
    void applyGravity(const ofVec2f& gravity);
    void applyForce(const ofVec2f& force);
    
    void update();
    void draw();
    
    bool isAlive() { return life > 0; }

    ofVec2f pos;
    float mass;
    ofFloatColor color;

private:
    void checkBounds();
    
    float origAlpha;
    float life;
    ofVec2f vel;
    ofVec2f acc;
};


#endif /* defined(__ofxControlEase_example__RainDrop__) */
