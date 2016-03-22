//
//  Spring.cpp
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#include "Spring.h"

Spring::Spring()
{
}

Spring::~Spring()
{
    
}

void Spring::setup(Particle *source, Particle *target)
{
    p1 = source;
    p2 = target;
    
    restLength = (*p2-*p1).length();
}

void Spring::update()
{
    ofVec2f force = (*p2-*p1);
    float currentLength = force.length();
    float x = currentLength - restLength * Params::springRestLengthFactor;
    
    force.normalize();
    
    force *= Params::springCoeff * x;

    p1->applyForce(force*Params::springForceFactor);
    p2->applyForce(force*-Params::springForceFactor);
}
