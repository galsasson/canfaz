//
//  TurtleStep.cpp
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#include "TurtleStep.h"

TurtleStep::TurtleStep(float ang, float len)
{
    angle = ang;
    length = len;
    
    angleOffset = 0;
    lengthScale = 1;
}

