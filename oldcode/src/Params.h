//
//  Params.h
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#ifndef __performance__Params__
#define __performance__Params__

#include <iostream>
#include "ofMain.h"

class Params
{
public:
    static float angleOffset;
    static float angleOffsetPerIndex;
    
    static float lengthScale;
    static float lengthIndexScale;
    
    static float repeatTimes;
    static float repeatRotateCoeff;
    static float repeatScaleXCoeff;
    static float repeatScaleYCoeff;
    static float repeatTransXCoeff;
    static float repeatTransYCoeff;
    
    static ofVec2f springGravity;
    static ofVec2f springTemporalForce;
    static float springForceFactor;
    static float springRestLengthFactor;
    static float springCoeff;
    
    static float particleMaxSpeed;
    static float particleFrictionCoeff;
    static ofVec2f particleTemporalVelocity;
    static ofVec2f particleGravity;
    static float particleFlowfieldForce;
    
    static ofVec2f lineNoise;
    
    static float globalReleaseAmount;
    
    static ofFloatColor surfaceColor;
    
    static float colorMode;
    static float randomParticleColors;
    
    
    //################### Drop Emitter #
    //################### Drop Emitter #

    static float emissionSpeed;
    static float emissionRadius;
    static float dropSize;
    static float dropSizeVariation;
    static float dropLife;
    static ofFloatColor dropColor;
    static float maxInitialForce;
    static float frictionCoeff;
    
    static ofVec2f gravity;
    static ofVec2f tempForce;

};

#endif /* defined(__performance__Params__) */
