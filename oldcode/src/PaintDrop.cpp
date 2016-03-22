//
//  PaintDrop.cpp
//  performance
//
//  Created by Gal Sasson on 4/22/14.
//
//

#include "PaintDrop.h"

PaintDrop::PaintDrop(SmoothLine *l, const ofColor& c) : Particle(*l->getPoints()[0])
{
    line = l;
    color = c;
    state = 1;
    linePos = 0;
    size = 0;
    followParticle = NULL;
    t = ofRandom(1000);
}

void PaintDrop::update()
{
    t += 0.1;
    
    if (state == 0) {
        // grow
        size += ofNoise(t);
        if (size > 3) {
            state = 1;
        }
    }
    else if (state == 1) {
        // follow down
        linePos += ofNoise(t)*0.2f;
        
        int si = (int)linePos;  // source index
        int ti = (int)linePos+1;    // target index
        
        if (si >= line->getPoints().size() ||
            ti >= line->getPoints().size()) {
            // we have reached the end of the line
            followParticle = line->getPoints()[line->getPoints().size()-1];
            state = 2;
            return;
        }
        
        // move along the line
        Particle* sp = line->getPoints()[si];
        Particle* tp = line->getPoints()[ti];
        
        if (tp->y < sp->y) {
            // we have reached a local minimum on the line
            followParticle = sp;
            size = sp->mass*2;
            state = 2;
            return;
        }
        
        set(*sp + (*tp-*sp)*(linePos-si));
//        sp->setTempColor(color);
        size += (sp->mass*2-size)*0.5;
    }
    else if (state == 2) {
        // follow the tip
        set(*followParticle);
//        followParticle->setTempColor(color);
        size += (followParticle->mass*2-size)*0.5;
    }
    
}

void PaintDrop::draw()
{
    ofSetColor(color);
    ofFill();
    ofEllipse(x, y, size, size);
}


