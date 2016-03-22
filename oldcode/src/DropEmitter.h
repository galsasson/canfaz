//
//  DropEmitter.h
//  ofxControlEase_example
//
//  Created by Gal Sasson on 5/1/14.
//
//

#ifndef __ofxControlEase_example__DropEmitter__
#define __ofxControlEase_example__DropEmitter__

#include <iostream>
#include "ofMain.h"
#include "Params.h"
#include "ResourceManager.h"
#include "RainDrop.h"

class DropEmitter
{
public:
    DropEmitter();
    void setup(const ofVec2f& pos);
    void follow(ofVec2f* pos);
    
    void update();
    void draw();
    
private:
    ofVec2f pos;
    bool bFollowing;
    ofVec2f* target;
    float counter;
    
    vector<RainDrop*> drops;
    
    void emitDrop();
    
    ofEasyCam cam;
    ofTexture dotTexture;
    ofVboMesh mesh;
    ofVbo vbo;
    ofShader shader;
};


#endif /* defined(__ofxControlEase_example__DropEmitter__) */
