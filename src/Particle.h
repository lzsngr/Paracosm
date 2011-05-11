/*
 *  Particle.h
 *  FirefliesTuio
 *
 *  Created by Miguel Bermudez on 3/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "ofMain.h"
#include "ofxVec2f.h"
#include <vector>

class Emitter;					//forward declaration of Emitter


class Particle {
	public:
		Emitter* pEmitter;      //pointer to particle's emitter
		
		Particle( Emitter *emitter, ofxVec2f v, ofxVec2f l);
	
		void update();
		void run();
		void render();
	
		bool dead();
		void displayVector( ofxVec2f v, float x, float y, float scalr, bool dispArrows );
		void drawParticle( float x, float y, bool png );
		void setPosition( ofxVec2f oPos );
    
        float minNoise;
        float maxNoise;

private:
	ofxVec2f loc;
	ofxVec2f vel;
	ofxVec2f acc;
	ofxVec2f gravity;
    ofxVec2f perlin;
	ofxVec2f randomVector;
	
	float timer;
	float particleSize;
	float heading2D( ofxVec2f v );
    void findPerlin();
	float getRads( float val1, float val2, float mult, float div );
};

#include "emitter.h"
#endif


