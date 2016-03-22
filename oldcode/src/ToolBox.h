//
//  ToolBox.h
//  performance
//
//  Created by Gal Sasson on 5/19/14.
//
//

#ifndef __performance__ToolBox__
#define __performance__ToolBox__

#include <iostream>
#include "ofMain.h"

class ToolBox
{
public:
    ToolBox();
    ~ToolBox();
    void setup(ofVec2f p);
    void draw();
    
    bool contains(ofVec2f p);
    int getButton(ofVec2f p);
    
    int currentTool;
    
private:
    ofVec2f pos;
    ofVec2f size;
    
    ofImage lineImg;
    ofImage rubberImg;
    ofImage multiImg;
    ofImage partImg;
    ofImage polyImg;
    ofImage cutImg;
    ofImage dropLineImg;
    ofImage dropPartImg;
};

#endif /* defined(__performance__ToolBox__) */
