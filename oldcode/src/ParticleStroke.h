//
//  ParticleStroke.h
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#ifndef __performance__ParticleStroke__
#define __performance__ParticleStroke__

#include <iostream>
#include "ofMain.h"
#include "ResourceManager.h"
#include "Params.h"
#include "FlowField.h"
#include "Particle.h"

class ParticleStroke
{
public:
    ParticleStroke();
    ~ParticleStroke();
    void addPoint(const ofVec2f& p);
    
    void update();
    void draw();
    
    void applyFlowField(FlowField& flowField);
    
    void releaseAllParticles();
    void releaseRandomParticles();
    
    vector<Particle*>& getParticles() { return points; }
    
private:
    void rebuildVbo();
    float getDistanceToClosestParticle(const ofVec2f& p);
    
    vector<Particle*> points;
    float t;
    
    ofVbo vbo;
    
};

#endif /* defined(__performance__ParticleStroke__) */
