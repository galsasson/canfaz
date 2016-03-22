//
//  PaintDrop.h
//  performance
//
//  Created by Gal Sasson on 4/22/14.
//
//

#ifndef __performance__PaintDrop__
#define __performance__PaintDrop__

#include <iostream>
#include "ofMain.h"
#include "Particle.h"
#include "SmoothLine.h"

class PaintDrop : public Particle
{
public:
    PaintDrop(SmoothLine *l, const ofColor& c);
    
    void update();
    void draw();
    
private:
    float t;
    
    int state;
    float linePos;
    float size;
    ofColor color;
    
    Particle* followParticle;
    
    SmoothLine* line;
//    Spring* spring;
};


#endif /* defined(__performance__PaintDrop__) */
