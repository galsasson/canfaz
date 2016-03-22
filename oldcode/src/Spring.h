//
//  Spring.h
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#ifndef __performance__Spring__
#define __performance__Spring__

#include <iostream>
#include "ofMain.h"
#include "Params.h"
#include "Particle.h"

class Spring
{
public:
    Spring();
    ~Spring();
    
    void setup(Particle *source, Particle *target);
    void update();
    
    bool isConnecting(Particle *p, Particle *q) { return (p==p1 && q==p2) || (p==p2 && q==p1); }

    float restLength;
    
private:
    Particle* p1;
    Particle* p2;
};
#endif /* defined(__performance__Spring__) */
