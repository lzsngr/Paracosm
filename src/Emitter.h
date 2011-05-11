/*
 *  Emitter.h
 *  FirefliesTuio
 *
 *  Created by Miguel Bermudez on 3/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EMITTER_H
#define EMITTER_H

#include "ofMain.h"
#include "Particle.h"
#include <vector>


class Emitter {
public: 
	Emitter();
	Emitter(int num, ofxVec2f v);
	
	void setup();
	void run();
	void addParticle();
	void addParticle(float x, float y);
	void clearAll();
	
	void setVelToMouse(int mx, int my);
	void render();
	
	vector<Particle*> getParticles();

	ofImage particleImg;
	ofTexture particleTex;
	ofImage emitterImg;
	ofTexture emitterTex;
    
    bool ALLOWGRAVITY;
    bool ALLOWPERLIN;
    bool ALLOWTRAILS;
	
	
private:
	int num_particles;
	ofxVec2f origin;
    ofxVec2f loc;
    ofxVec2f vel;
    ofxVec2f velToMouse;
    
	vector<Particle*> particles;
	
    
};

#endif
