//
//  FlowFieldForce.cpp
//  performance
//
//  Created by Gal Sasson on 4/23/14.
//
//

#include "FlowFieldForce.h"

FlowFieldForce::FlowFieldForce()
{
    
}

FlowFieldForce::FlowFieldForce(float x, float y, const ofVec2f& f)
{
    screenPos = ofVec2f(x, y);
    force = f;
}
