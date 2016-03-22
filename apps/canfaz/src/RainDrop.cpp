//
//  RainDrop.cpp
//  ofxControlEase_example
//
//  Created by Gal Sasson on 5/1/14.
//
//

#include "RainDrop.h"

RainDrop::RainDrop()
{
    mass = 1;
}

void RainDrop::setup(const ofVec2f &p)
{
    life = Params::dropLife - ofRandom(30);
    color = Params::dropColor;
    origAlpha = Params::dropColor.a;
    
    pos = p;
    mass = ofRandom(Params::dropSize)+ofRandom(5);
    vel = ofVec2f(ofRandom(Params::maxInitialForce), 0);
    vel.rotate(ofRandom(360));
}

void RainDrop::applyGravity(const ofVec2f &gravity)
{
    acc += gravity;
}

void RainDrop::applyForce(const ofVec2f &force)
{
    acc += force/mass;
}

void RainDrop::update()
{
    vel += acc;
    pos += vel;
    
    vel *= Params::frictionCoeff;
    
    acc *= 0;
    
    life -= 1;
    if (life < 10) {
        color.a = origAlpha - life/10;
    }
    
    checkBounds();
}

void RainDrop::draw()
{
//    ofSetColor(color, 0.5);
    float s = Params::dropSize + ofRandom(Params::dropSizeVariation);
    ofEllipse(pos.x, pos.y, s, s);
}

void RainDrop::checkBounds()
{
    if (pos.y > ofGetWindowHeight()) {
        pos.y = ofGetWindowHeight();
        vel.y *= -ofRandom(1);
    }
    else if (pos.y < 0) {
        pos.y = 0;
        vel.y *= -ofRandom(1);
    }
    
    if (pos.x > ofGetWindowWidth()) {
        pos.x = ofGetWindowWidth();
        vel.x *= -ofRandom(1);
    }
    else if (pos.x < 0) {
        pos.x = 0;
        vel.x *= -ofRandom(1);
    }
}
