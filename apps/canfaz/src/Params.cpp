//
//  Params.cpp
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#include "Params.h"

float Params::angleOffset = 0;
float Params::angleOffsetPerIndex = 0;

float Params::lengthScale = 1;
float Params::lengthIndexScale = 1;

float Params::repeatTimes = 150;
float Params::repeatRotateCoeff = 1;
float Params::repeatScaleXCoeff = 1;
float Params::repeatScaleYCoeff = 1;
float Params::repeatTransXCoeff = 2;
float Params::repeatTransYCoeff = 2;

ofVec2f Params::springGravity(0, 0.1f);
float Params::springForceFactor = 1;
float Params::springRestLengthFactor = 0.05f;
ofVec2f Params::springTemporalForce(0, 0);
float Params::springCoeff = 0.61;

float Params::particleMaxSpeed = 10;
float Params::particleFrictionCoeff = 0.96f;
ofVec2f Params::particleTemporalVelocity(0, 0);
ofVec2f Params::particleGravity(0, 0.4f);
float Params::particleFlowfieldForce = 0.2f;

ofVec2f Params::lineNoise = ofVec2f(0, 0);

float Params::globalReleaseAmount = 0;

ofFloatColor Params::surfaceColor(0.1f, 0.02f, 0.08f);

float Params::colorMode = 0;
float Params::randomParticleColors = 0;







//################### Drop Emitter #

float Params::emissionSpeed = 50;
float Params::emissionRadius = 4;
float Params::dropSize = 10;
float Params::dropSizeVariation = 30;
float Params::dropLife = 30;
ofFloatColor Params::dropColor(0.5, 0.5, 0.5, 0.14);

float Params::maxInitialForce = 0.6;
float Params::frictionCoeff = 0.9;

ofVec2f Params::gravity(0, -0.05);
ofVec2f Params::tempForce(0, 0);
