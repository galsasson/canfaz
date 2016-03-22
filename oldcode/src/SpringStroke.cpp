//
//  SpringStroke.cpp
//  performance
//
//  Created by Gal Sasson on 4/21/14.
//
//

#include "SpringStroke.h"

SpringStroke::SpringStroke()
{
    lockDistance = 2;
    color = ResourceManager::getInstance().getStrokeColor();
    line = new SmoothLine();
}

SpringStroke::~SpringStroke()
{
    for (int i=0; i<springs.size(); i++)
    {
        delete springs[i];
    }
    springs.clear();
    
    for (int i=0; i<paintDrops.size(); i++)
    {
        delete paintDrops[i];
    }
    paintDrops.clear();
    
    delete line;
}

void SpringStroke::setLockDistance(float distance)
{
    lockDistance = distance;
}

void SpringStroke::addPoint(float x, float y)
{
    line->addPoint(x, y);
    
    vector<Particle*> particles = line->getPoints();
    int newIndex = particles.size()-1;
    Particle* newPar = particles[newIndex];
    if (newIndex > 0) {
        Spring *s = new Spring();
        Particle *prevPar = particles[newIndex-1];
        s->setup(prevPar, newPar);
        springs.push_back(s);
        
        // lock particle if close to previous one
        if ((*prevPar - *newPar).length() < lockDistance) {
            newPar->stickiness = 100;
//            newPar->locked = true;
        }
        
    }
    else {
        newPar->stickiness = 100;
//        newPar->locked = true;
    }
}

void SpringStroke::update()
{
    for (int i=0; i<paintDrops.size(); i++)
    {
        paintDrops[i]->update();
    }
    
    for (int i=0; i<springs.size(); i++)
    {
        springs[i]->update();
    }
    
    vector<Particle*> particles = line->getPoints();
    for (int i=0; i<particles.size(); i++)
    {
        particles[i]->applyGravity(Params::springGravity);
        if (i==particles.size()-1) {
            // applly outside forces to last particle
            particles[i]->applyForce(Params::springTemporalForce);
        }
        particles[i]->update();
        particles[i]->checkBounds();
    }
    
    line->update();
    line->rebuildMesh();
}

void SpringStroke::draw()
{
    line->draw();

    if (bEmitter) {
        vector<Particle*> particles = line->getPoints();
        for (int i=0; i<particles.size(); i++)
        {
            particles[i]->drawEmitter();
        }
    }
}

void SpringStroke::drawSurface()
{
    vector<Particle*> pars = line->getPoints();
    ofBeginShape();
    for (int i=0; i<pars.size(); i++)
    {
        ofVertex(pars[i]->x, pars[i]->y);
    }
    ofEndShape();
}

void SpringStroke::dropColor(const ofColor &c)
{
    paintDrops.push_back(new PaintDrop(line, c));
}

void SpringStroke::releaseAnchors()
{
    vector<Particle*> pars = line->getPoints();
    for (int i=0; i<pars.size(); i++)
    {
        pars[i]->stickiness = 0;
    }
}

void SpringStroke::setupParticleEmitters()
{
    if (bEmitter) {
        // already have an emitter
        return;
    }
    
    vector<Particle*> pars = line->getPoints();
    for (int i=0; i<pars.size(); i++)
    {
        pars[i]->setupEmitter();
    }
    bEmitter = true;
}

ofVec2f SpringStroke::getLastPoint()
{
    if (line->getPoints().empty()) {
        return ofVec2f();
    }
    
    return *line->getPoints()[line->getPoints().size()-1];
}

int SpringStroke::getIntersection(const ofVec2f &p1, const ofVec2f &p2)
{
    // check if the line intersects with any line we have
    vector<Particle*> particles = line->getPoints();
    for (int i=2; i<particles.size(); i++)
    {
        if (isIntersects(p1, p2, *particles[i-1], *particles[i])) {
            return i;
        }
    }
    
    return -1;
}

SpringStroke* SpringStroke::cutStroke(int index)
{
    vector<Particle*> pars = line->getPoints();
    if (index >= pars.size()) {
        cout<<"error: index out of bounds in cutStroke"<<endl;
        return NULL;
    }
    
    Particle *p = pars[index-1];
    Particle *q = pars[index];
    SpringStroke* newStroke = new SpringStroke();
    newStroke->line = line->cutLine(index);

    // move all springs starting from index to the new stroke
    for (int i=index; i<springs.size(); i++)
    {
        newStroke->springs.push_back(springs[i]);
    }
    // delete the spring that connected the two strokes
    delete springs[index-1];
    springs.erase(springs.begin()+(index-1), springs.end());
    
    // set emitter
    newStroke->bEmitter = bEmitter;
    
    return newStroke;
}

bool SpringStroke::isIntersects(const ofVec2f& p, const ofVec2f& p2,
                  const ofVec2f& q, const ofVec2f& q2)
{
	ofVec2f r = p2 - p;
	ofVec2f s = q2 - q;
    
	float uNumerator = crossProduct((q-p), r);
	float denominator = crossProduct(r, s);
    
	if (uNumerator == 0 && denominator == 0) {
		// colinear, so do they overlap?
		return ((q.x - p.x < 0) != (q.x - p2.x < 0) != (q2.x - p.x < 0) != (q2.x - p2.x < 0)) ||
        ((q.y - p.y < 0) != (q.y - p2.y < 0) != (q2.y - p.y < 0) != (q2.y - p2.y < 0));
	}
    
	if (denominator == 0) {
		// lines are paralell
		return false;
	}
    
	float u = uNumerator / denominator;
	float t = crossProduct((q - p), s) / denominator;
    
	return (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1);
}

float SpringStroke::crossProduct(const ofVec2f &p, const ofVec2f &q)
{
    return p.x * q.y - p.y * q.x;
}


