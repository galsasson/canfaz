//
//  FlowFieldForce.h
//  performance
//
//  Created by Gal Sasson on 4/23/14.
//
//

#ifndef __performance__FlowFieldForce__
#define __performance__FlowFieldForce__

#include <iostream>
#include "ofMain.h"

class FlowFieldForce
{
public:
    FlowFieldForce();
    FlowFieldForce(float x, float y, const ofVec2f& f = ofVec2f(0, 0));
    
    ofVec2f force;
    ofVec2f screenPos;
    
};


#endif /* defined(__performance__FlowFieldForce__) */
