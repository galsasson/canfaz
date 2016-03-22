//
//  Stroke.h
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#ifndef __performance__Stroke__
#define __performance__Stroke__

#include <iostream>
#include "ofMain.h"
#include "SmoothLine.h"

class Stroke
{
public:
    Stroke();
    ~Stroke();
    void addPoint(float x, float y);
    vector<Particle*>& getPoints() { return line.getPoints(); }
    
    void update();
    void draw();
    
private:
    SmoothLine line;
};

#endif /* defined(__performance__Stroke__) */
