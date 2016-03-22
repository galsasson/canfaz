//
//  ParticleStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/18/14.
//
//

#include "ParticleStroke.h"

ParticleStroke::ParticleStroke()
{
    t = ofRandom(1000);
}

ParticleStroke::~ParticleStroke()
{
    for (int i=0; i<points.size(); i++)
    {
        delete points[i];
    }
    points.clear();
    
    vbo.clear();
}

#define CIRCLE_PACKING

void ParticleStroke::addPoint(const ofVec2f &p)
{
#ifdef CIRCLE_PACKING
    float mass = 1;
    if (!points.empty()) {
        float radFromLast = getDistanceToClosestParticle(p) * 0.8;
        if (radFromLast < 0) {
            return;
        }
        mass = Particle::getMassFromRadius(radFromLast);
        if (mass > 2) {
            mass = 2;
        }
    }
    else {
        mass = ofRandom(1)+1;
    }
#else
    float mass = ofRandom(1)+0.5;
#endif
    
    Particle *newP = new Particle(p, mass);
    newP->stickiness = ofRandom(100);
//    newP->locked = true;
//    newP->setColor(Params::springStrokeColor);
    points.push_back(newP);
    
    rebuildVbo();
}

void ParticleStroke::update()
{
    
    vector<ofVec3f> vertices;
    vertices.reserve(points.size());
    vector<ofVec3f> sizes;
    sizes.reserve(points.size());
    vector<ofFloatColor> colors;
    colors.reserve(points.size());

    for (int i=0; i<points.size(); i++)
    {
        if (points[i]->stickiness > 0)
        {
            points[i]->stickiness -= Params::globalReleaseAmount;
        }
        points[i]->applyGravity(Params::particleGravity);
        points[i]->update();
        points[i]->checkBounds();
        
        vertices.push_back(*points[i]);
        sizes.push_back(ofVec3f(points[i]->mSize, 0, 0));
        if (Params::colorMode == 0) {
            colors.push_back(points[i]->getColor());
        }
        else {
            colors.push_back(points[i]->getColor() + ofFloatColor(0.35, 0.35, 0.35));
        }
    }
    
    vbo.setVertexData(&vertices[0], vertices.size(), GL_DYNAMIC_DRAW);
    vbo.setNormalData(&sizes[0], sizes.size(), GL_DYNAMIC_DRAW);
    vbo.setColorData(&colors[0], colors.size(), GL_DYNAMIC_DRAW);
    
    t+=0.1;
}

void ParticleStroke::draw()
{
//    glDepthMask(GL_FALSE);
    ofEnablePointSprites();
    ResourceManager::getInstance().particleShader.begin();
    ResourceManager::getInstance().particleTex.bind();
    vbo.draw(GL_POINTS, 0, (int)points.size());
    ResourceManager::getInstance().particleTex.unbind();
    ResourceManager::getInstance().particleShader.end();
    
    ofDisablePointSprites();
}

void ParticleStroke::applyFlowField(FlowField &flowField)
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->applyForce(flowField.getForce(*points[i]));
        flowField.addRepulsion(*points[i], 8, Params::particleFlowfieldForce);
    }
}

void ParticleStroke::releaseAllParticles()
{
    for (int i=0; i<points.size(); i++)
    {
        points[i]->stickiness = 0;
    }
}

void ParticleStroke::releaseRandomParticles()
{
    for (int i=0; i<points.size(); i++)
    {
        if (ofRandom(2) > 1) {
            points[i]->stickiness = 0;
        }
    }
}

float ParticleStroke::getDistanceToClosestParticle(const ofVec2f &p)
{
    float minLength = 10000;
    
    int start = points.size()-50;
    if (start<0) {
        start = 0;
    }
    
    for (int i=start; i<points.size(); i++)
    {
        float l = (p-*points[i]).length() - points[i]->getRadius();
        if (l < minLength) {
            minLength = l;
        }
    }
    
    return minLength*1.4;
}

void ParticleStroke::rebuildVbo()
{
    vector<ofVec3f> vertices;
    vertices.reserve(points.size());
    vector<ofVec3f> sizes;
    sizes.reserve(points.size());
    vector<ofFloatColor> colors;
    colors.reserve(points.size());
    
    for (int i=0; i<points.size(); i++)
    {
        vertices.push_back(*points[i]);
        sizes.push_back(ofVec3f(points[i]->mSize, 0, 0));
        if (Params::colorMode == 0) {
            colors.push_back(points[i]->getColor());
        }
        else {
            colors.push_back(points[i]->getColor() + ofFloatColor(0.35, 0.35, 0.35));
        }
    }
    
    vbo.setVertexData(&vertices[0], vertices.size(), GL_DYNAMIC_DRAW);
    vbo.setNormalData(&sizes[0], sizes.size(), GL_DYNAMIC_DRAW);
    vbo.setColorData(&colors[0], colors.size(), GL_DYNAMIC_DRAW);
}
