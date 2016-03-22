//
//  SmoothLine.h
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#ifndef __performance__SmoothLine__
#define __performance__SmoothLine__

#include <iostream>
#include "ofMain.h"
#include "Params.h"
#include "Particle.h"
#include "ResourceManager.h"

class SmoothLine
{
public:
    SmoothLine();
    ~SmoothLine();
    
    void addPoint(float x, float y);
    
    void update();
    void draw();
    
    SmoothLine* cutLine(int index);
    
    vector<Particle*>& getPoints() { return points; }
    void rebuildMesh();
    
private:
    vector<Particle*> points;
    
    ofMesh mesh;
};

#endif /* defined(__performance__SmoothLine__) */
