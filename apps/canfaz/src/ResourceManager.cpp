//
//  ResourceManager.cpp
//  Controlease
//
//  Created by Gal Sasson on 2/19/14.
//
//

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    scatImg.loadImage("scat.png");
    scatImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    circleImg.loadImage("circle.png");
    circleImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    
    ofDisableArbTex();
    ofLoadImage(particleTex, "dot_no_ring.png");
    particleShader.load("shaders/shader");
}

ofColor ResourceManager::getStrokeColor()
{
    return ofColor(230, 230, 230);
    
    if (Params::colorMode == 0) {
        return ofColor(230, 230, 230);
    }
    else {
        return ofColor(0, 0, 0, 255);
    }
}

ofColor ResourceManager::getBackgroundColor()
{
    if (Params::colorMode == 0) {
        return ofColor(230, 230, 230, 100);
    }
    else {
        return ofColor(0, 0, 0, 100);
    }
}

ofColor ResourceManager::getParticleColor()
{
//    if (Params::colorMode == 0) {
        return ofColor(230, 230, 230);
//    }
//    else {
//        return ofColor(50, 50, 50);
//    }
}