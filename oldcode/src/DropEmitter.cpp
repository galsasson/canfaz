//
//  DropEmitter.cpp
//  ofxControlEase_example
//
//  Created by Gal Sasson on 5/1/14.
//
//

#include "DropEmitter.h"

DropEmitter::DropEmitter()
{
}

void DropEmitter::setup(const ofVec2f& p)
{
    pos = p;
    counter = -1;
    
    bFollowing = false;
    target = NULL;
    
//    ofLoadImage(dotTexture, "dot_no_ring.png");
//    shader.load("shaders/shader");
}

void DropEmitter::follow(ofVec2f *p)
{
    target = p;
    bFollowing = true;
}

void DropEmitter::update()
{
    while (counter < 0) {
        emitDrop();
        counter += 10;
    }
    counter -= Params::emissionSpeed;
    
    vector<ofVec3f> vertices;
    vector<ofVec3f> sizes;
    vector<ofFloatColor> colors;
    
    for (int i=drops.size()-1; i>=0; i--)
    {
        drops[i]->applyGravity(Params::gravity);
        drops[i]->applyForce(Params::tempForce);
        drops[i]->update();
        
        if (!drops[i]->isAlive())
        {
            delete drops[i];
            drops.erase(drops.begin()+i);
            continue;
        }
        
        vertices.push_back(ofVec3f(drops[i]->pos.x, drops[i]->pos.y, 0));
        sizes.push_back(ofVec3f(drops[i]->mass, 0, 0));
        colors.push_back(drops[i]->color);
    }
    vbo.setVertexData(&vertices[0], vertices.size(), GL_DYNAMIC_DRAW);
    vbo.setNormalData(&sizes[0], sizes.size(), GL_DYNAMIC_DRAW);
    vbo.setColorData(&colors[0], colors.size(), GL_DYNAMIC_DRAW);
}

void DropEmitter::draw()
{
    glDepthMask(GL_FALSE);
    ofEnablePointSprites();
    ResourceManager::getInstance().particleShader.begin();
    ResourceManager::getInstance().particleTex.bind();
	vbo.draw(GL_POINTS, 0, (int)drops.size());
    ResourceManager::getInstance().particleTex.unbind();
    ResourceManager::getInstance().particleShader.end();
    
    ofDisablePointSprites();
}

void DropEmitter::emitDrop()
{
    RainDrop *rd = new RainDrop();
    ofVec2f p = ofVec2f(ofRandom(Params::emissionRadius), 0);
    p.rotate(ofRandom(360));
    
    if (bFollowing) {
        p += *target;
    }
    else {
        p += pos;
    }
    
    rd->setup(p);
    drops.push_back(rd);
}

