//
//  FlowField.cpp
//  performance
//
//  Created by Gal Sasson on 4/17/14.
//
//

#include "FlowField.h"

FlowField::FlowField()
{
    field = NULL;
}

FlowField::~FlowField()
{
    if (field) {
        for (int i=0; i<nWidth; i++)
        {
            delete field[i];
        }
        delete field;
    }
}

void FlowField::setup(int w, int h, int nw, int nh)
{
    size = ofVec2f(w, h);
    squareSize = ofVec2f(size.x / nw, size.y / nh);
    squareLength = squareSize.length();
    nWidth = nw+1;
    nHeight = nh+1;
    
    
    field = new FlowFieldForce*[nWidth];
    for (int i=0; i<nWidth; i++)
    {
        field[i] = new FlowFieldForce[nHeight];
    }
    
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            field[x][y].screenPos = ofVec2f(x, y)*squareSize;
        }
    }
    
    reset();
}

void FlowField::update()
{
    
}

void FlowField::draw()
{
    ofSetColor(150);
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            drawArrow(field[x][y].screenPos, field[x][y].force);
        }
    }
}

void FlowField::reset()
{
    for (int x=0; x<nWidth; x++)
    {
        for (int y=0; y<nHeight; y++)
        {
            field[x][y].force = ofVec2f(0, 0);
        }
    }
}

void FlowField::addAttractor(ofVec2f p, float rad, float force)
{
    int minX = max((int)((p.x-rad) / squareSize.x), 0);
    int minY = max((int)((p.y-rad) / squareSize.y), 0);
    int maxX = min((int)((p.x+rad) / squareSize.x), nWidth-1);
    int maxY = min((int)((p.y+rad) / squareSize.y), nHeight-1);

    for (int x=minX; x<maxX; x++)
    {
        for (int y=minY; y<maxY; y++)
        {
            ofVec2f pos = ofVec2f(x, y)*squareSize;
            ofVec2f offset = p-pos;
            float distance = offset.length();
            if (distance < rad) {
                float f = ((rad - distance) / rad) * force;
                offset.normalize();
                field[x][y].force += offset * f;
                field[x][y].force.limit(10);
            }
        }
    }
}

void FlowField::addForce(ofVec2f p, float rad, ofVec2f force)
{
    int minX = max((int)((p.x-rad) / squareSize.x), 0);
    int minY = max((int)((p.y-rad) / squareSize.y), 0);
    int maxX = min((int)((p.x+rad) / squareSize.x), nWidth-1);
    int maxY = min((int)((p.y+rad) / squareSize.y), nHeight-1);

    for (int x=minX; x<maxX; x++)
    {
        for (int y=minY; y<maxY; y++)
        {
            ofVec2f offset = p-field[x][y].screenPos;
            float distance = offset.length();
            if (distance < rad) {
                ofVec2f f = force * ((rad - distance) / rad);
                if (field[x][y].force.length() < f.length())
                {
                    field[x][y].force = f;
                }
            }
        }
    }
}

void FlowField::addRepulsion(const ofVec2f &p, float rad, float strength)
{
    int minX = max((int)((p.x-rad) / squareSize.x), 0);
    int minY = max((int)((p.y-rad) / squareSize.y), 0);
    int maxX = min((int)((p.x+rad) / squareSize.x)+1, nWidth-1);
    int maxY = min((int)((p.y+rad) / squareSize.y)+1, nHeight-1);
    
    for (int x=minX; x<maxX; x++)
    {
        for (int y=minY; y<maxY; y++)
        {
            ofVec2f offset = field[x][y].screenPos - p;
            float distance = offset.length();
            if (distance < rad) {
                ofVec2f f = offset.normalize() * ((rad - distance) / rad * strength);
                if (field[x][y].force.length() < f.length())
                {
                    field[x][y].force = f;
                }
            }
        }
    }
}

void FlowField::addLineRepulsion(const ofVec2f &p, const ofVec2f &q, float strength)
{
    ofVec2f line = q-p;
    ofVec2f perp = line.getPerpendicular();
    ofVec2f perp2 = line.getPerpendicular() * -1;
    
    for (float t=0; t<1; t+=0.2)
    {
        addForce(p + line*t + perp*5, 10, perp*strength);
        addForce(p + line*t + perp2*5, 10, perp2*strength);
    }
}

void FlowField::applyStrokeForces(const vector<Particle*>& points)
{
    for (int i=0; i<points.size()-1; i++)
    {
        addLineRepulsion(*points[i], *points[i+1], 10);
    }
}

ofVec2f FlowField::getForce(const ofVec2f& p) const
{
    int minX = min(max((int)(p.x / squareSize.x), 0), nWidth-2);
    int minY = min(max((int)(p.y / squareSize.y), 0), nHeight-2);
    int maxX = min(minX+1, nWidth-1);
    int maxY = min(minY+1, nHeight-1);
    
    ofVec2f tlPos = field[minX][minY].screenPos;
    ofVec2f trPos = field[maxX][minY].screenPos;
    ofVec2f blPos = field[minX][maxY].screenPos;
    ofVec2f brPos = field[maxX][maxY].screenPos;
    
    float tlf = 1-(p-tlPos).length()/squareLength;
    float trf = 1-(p-trPos).length() / squareLength;
    float blf = 1-(p-blPos).length() / squareLength;
    float brf = 1-(p-brPos).length() / squareLength;

    return field[minX][minY].force * tlf +
            field[maxX][minY].force * trf +
            field[minX][maxY].force * blf +
            field[maxX][maxY].force * brf;
}

void FlowField::drawArrow(ofVec2f s, ofVec2f t)
{
    float length = t.length();
    if (length == 0) {
        ofLine(s, s+ofVec2f(1, 0));
        return;
    }
    
    ofPushMatrix();
    ofTranslate(s);
    
    ofRotate(ofRadToDeg(atan2(t.y, t.x)));
    ofLine(0, 0, length, 0);
    ofLine(length, 0, length-3, -2);
    ofLine(length, 0, length-3, 2);
    
    ofPopMatrix();
}


