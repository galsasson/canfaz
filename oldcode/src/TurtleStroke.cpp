//
//  TurtleStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/13/14.
//
//

#include "TurtleStroke.h"

TurtleStroke::TurtleStroke()
{
    privateSeed = 0;//ofRandom(1000);
}

TurtleStroke::~TurtleStroke()
{
    for (int i=0; i<steps.size(); i++)
    {
        delete steps[i];
    }
    
    steps.clear();
}

void TurtleStroke::setup(ofVec3f p)
{
    anchor = p;
}


void TurtleStroke::addPoint(ofVec3f p)
{
    ofVec3f lastPos = getWorldSpace(steps.size()-1);
    float lastAng = getLastAngleRad();
    
    ofVec3f diff = (p-lastPos);
    float distance = diff.length();
    float angle = atan2(diff.y, diff.x) - lastAng;
    steps.push_back(new TurtleStep(angle, distance));
}

void TurtleStroke::update()
{
    for (int i=0; i<steps.size(); i++)
    {
        float index = (float)i/steps.size();
        steps[i]->angleOffset = Params::angleOffset + sin(privateSeed + Params::angleOffsetPerIndex*index);
        steps[i]->lengthScale = Params::lengthScale * (pow(Params::lengthIndexScale,1+index));
    }
}

void TurtleStroke::draw()
{
    ofBeginShape();
    ofVertex(anchor);
    for (int i=0; i<steps.size(); i++)
    {
        ofVec3f pos = getWorldSpace(i);
        ofVertex(pos);
    }
    ofEndShape();
}

ofVec3f TurtleStroke::getWorldSpace(int index)
{
    ofVec3f pos = anchor;
    float angle = 0;
    
    for (int i=0; i<=index; i++) {
        ofVec3f s(steps[i]->getLength(), 0, 0);
        angle += steps[i]->getAngleDeg();
        s.rotate(angle, ofVec3f(0, 0, 1));
        pos += s;
    }
    
    return pos;
}

float TurtleStroke::getLastAngleRad()
{
    float ang=0;
    for (int i=0; i<steps.size(); i++)
    {
        ang += steps[i]->getAngleRad();
    }
    
    return ang;
}