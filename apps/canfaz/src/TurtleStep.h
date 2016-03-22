//
//  TurtleStep.h
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#ifndef __performance__TurtleStep__
#define __performance__TurtleStep__

#include <iostream>
#include "ofMain.h"

class TurtleStep
{
public:
    TurtleStep(float ang, float length);
    
    float getAngleDeg() { return (angle + angleOffset)*180/PI; }
    float getAngleRad() { return (angle + angleOffset); }
    float getLength() { return length * lengthScale; };
    
    float angle;
    float length;
    
    float angleOffset;
    float lengthScale;
};
#endif /* defined(__performance__TurtleStep__) */
