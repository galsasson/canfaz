//
//  Stroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/12/14.
//
//

#include "Stroke.h"

Stroke::Stroke()
{
    
}

Stroke::~Stroke()
{
}

void Stroke::addPoint(float x, float y)
{
    line.addPoint(x, y);
}

void Stroke::update()
{
    
}

void Stroke::draw()
{
    line.draw();
}

