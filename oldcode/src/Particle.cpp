//
//  Particle.cpp
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#include "Particle.h"

Particle::Particle() : ofVec2f(), mass(1)
{
    setup();
}

Particle::Particle(float x, float y, float m) : ofVec2f(x, y), mass(m)
{
    setup();
}

Particle::Particle(const ofVec2f& p, float m) : ofVec2f(p), mass(m)
{
    setup();
}

Particle::~Particle()
{
    if (emitter != NULL) {
        delete emitter;
    }
}

void Particle::setup()
{
    vel = ofVec2f();
    acc = ofVec2f();
    stickiness = 0;
    t = ofRandom(1000);
    
    mSize = (mass-1)*30;
    mRadius = mSize/2;
    
    bHasEmitter = false;
    emitter = NULL;
}

void Particle::setupEmitter()
{
    emitter = new DropEmitter();
    emitter->setup(ofVec2f(x, y));
    emitter->follow(this);
    bHasEmitter = true;
}

void Particle::removeEmitter()
{
    if (emitter) {
        delete emitter;
        emitter = NULL;
    }
    bHasEmitter = false;
}

void Particle::applyForce(const ofVec2f& force)
{
    acc += force/mass;
}

void Particle::applyGravity(const ofVec2f& gravity)
{
    acc += gravity;
}

void Particle::update()
{
    t += 0.1;

    if (bHasEmitter) {
        emitter->update();
    }

    // movement
    if (stickiness > 0) {
        return;
    }
    
    // apply temporal velocity
    vel += Params::particleTemporalVelocity;
    
    
    vel += acc;
    vel.limit(Params::particleMaxSpeed);
    
    x += vel.x;
    y += vel.y;
    
    vel *= Params::particleFrictionCoeff;
    
    acc *= 0;
}

void Particle::draw()
{
    ofPushMatrix();
    ofTranslate(x, y);

    ofSetColor(getColor(), 255);

    ofEllipse(0, 0, getSize(), getSize());
    
    ofPopMatrix();
}

void Particle::drawEmitter() {
    if (bHasEmitter) {
        emitter->draw();
    }
}

void Particle::checkBounds()
{
    if (y > ofGetWindowHeight()) {
        vel.y *= -0.8 + ofRandom(0.2);
        y = ofGetWindowHeight();
    }
    else if (y < 0) {
        vel.y *= -0.8 + ofRandom(0.2);
        y = 0;
    }
    
    if (x > ofGetWindowWidth()) {
        vel.x *= -0.8 + ofRandom(0.2);
        x = ofGetWindowWidth();
    }
    else if (x < 0) {
        vel.x *= -0.8 + ofRandom(0.2);
        x = 0;
    }
}

ofFloatColor Particle::getColor()
{
    // color
    if (Params::randomParticleColors > 0) {
        if (ofGetFrameNum() % (int)Params::randomParticleColors == 0) {
            color = ofFloatColor(ofRandom(0.35), ofRandom(0.35), ofRandom(0.35));
        }
        return color;
    }
    else {
        return ResourceManager::getInstance().getParticleColor();
    }
}

