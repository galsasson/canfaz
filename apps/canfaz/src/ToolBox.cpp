//
//  ToolBox.cpp
//  performance
//
//  Created by Gal Sasson on 5/19/14.
//
//

#include "ToolBox.h"

ToolBox::ToolBox()
{
    
}

ToolBox::~ToolBox()
{
    
}

void ToolBox::setup(ofVec2f p)
{
    pos = p;
    size = ofVec2f(300, 50);
    currentTool = 0;
    
    lineImg.loadImage("toolbox/tool_line.png");
    rubberImg.loadImage("toolbox/tool_rubber.png");
    multiImg.loadImage("toolbox/tool_multi.png");
    partImg.loadImage("toolbox/tool_part.png");
    polyImg.loadImage("toolbox/tool_poly.png");
    cutImg.loadImage("toolbox/tool_cut.png");
    dropLineImg.loadImage("toolbox/drop_line.png");
    dropPartImg.loadImage("toolbox/drop_part.png");
}

void ToolBox::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    ofScale(0.5, 0.5);
    
    ofNoFill();
    ofSetColor(255);
    ofLine(0, 0, 600, 0);
    ofLine(0, 100, 600, 100);
    for (int i=0; i<7; i++)
    {
        ofLine(i*100, 0, i*100, 100);
    }
    
    ofFill();
    ofSetColor(255, 50);
    ofRect(currentTool*100, 0, 100, 100);
    
    lineImg.draw(0, 0);
    rubberImg.draw(100, 0);
    partImg.draw(200, 0);
    polyImg.draw(300, 0);
    cutImg.draw(400, 0);
    multiImg.draw(500, 0);
//    dropLineImg.draw(600, 0);
//    dropPartImg.draw(700, 0);
    
    ofPopMatrix();
}

bool ToolBox::contains(ofVec2f p)
{
    if (p.x > pos.x &&
        p.x < pos.x+size.x &&
        p.y > pos.y &&
        p.y < pos.y+size.y) {
        return true;
    }
    
    return false;
}

int ToolBox::getButton(ofVec2f p)
{
    ofVec2f local = (p-pos)/2;
    int button = (int)(local.x/25);
    return button;
}
