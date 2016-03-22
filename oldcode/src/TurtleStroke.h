//
//  TurtleStroke.h
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#ifndef __performance__TurtleStroke__
#define __performance__TurtleStroke__

#include <iostream>
#include "ofMain.h"

#include "Params.h"
#include "TurtleStep.h"

class TurtleStroke
{
public:
    TurtleStroke();
    ~TurtleStroke();
    void setup(ofVec3f p);
    void addPoint(ofVec3f p);
    
    void update();
    void draw();
    
private:
    ofVec3f anchor;
    vector<TurtleStep*> steps;
    
    float privateSeed;
    
    ofVec3f getWorldSpace(int index);
    float getLastAngleRad();
};

#endif /* defined(__performance__TurtleStroke__) */
