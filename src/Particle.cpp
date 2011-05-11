/*
 *  Particle.cpp
 *  FirefliesTuio
 *
 *  Created by Miguel Bermudez on 3/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particle.h"

Particle::Particle( Emitter *emitter, ofxVec2f v, ofxVec2f l ) 
{
	//initialize gravity
	gravity.set( 0, 0.35f );

	acc.set( 0, 0.05f );

	randomVector = ofxVec2f( ofRandomf(), ofRandomf() );
	randomVector *= ofRandom( 0, 5.0 );
	vel += ( v + randomVector );
    
	//vel = v;
    loc = l;
    
    this->pEmitter = emitter;
	
	particleSize = ofRandom(20, 40);
	timer = 100.0;
    minNoise = 0.499;
    maxNoise = 0.501;
	
}

void Particle::run() {
	update();
	render();
}

void Particle::update() {
	//vel += acc;
    
    if ( pEmitter->ALLOWPERLIN )
    {
        findPerlin();
        vel += perlin;
    }

	loc += vel;
	timer -= 1.0;
	
}

void Particle::render() {
	//displayVector(vel, loc.x, loc.y, 2, true); //arrows on
	displayVector(vel, loc.x, loc.y, 2, false); //arrows off
	
}

bool Particle::dead() {
	if (timer <= 0.0) {
		return true;
	} else {
		return false;
	}
}

void Particle::findPerlin() {
    
	float xyRads = getRads( loc.x, 0, 10.0, 20.0 );
	float yRads = getRads( loc.x, loc.y, 10.0, 20.0 );

    perlin.set( cos(xyRads), -sin(yRads) );
    perlin *= 0.5;
}



float Particle::getRads( float val1, float val2, float mult, float div )
{
    float rads = ofNoise( val1/div, val2/div, ofGetFrameNum()/div );
	
    if ( rads < minNoise ) minNoise = rads;
    if ( rads > maxNoise ) maxNoise = rads;
		    
    rads -= minNoise;

    rads *= 1.0/( maxNoise - minNoise );

    return rads * mult;
}

void Particle::displayVector(ofxVec2f v, float x, float y, float scalr, bool dispArrows) {	
	
    ofPushMatrix();
		float arrowsize = 4;
		ofTranslate(x, y);
		v.normalized();
		ofRotate( heading2D(v) );
		
		
		float len = v.length() * scalr;
    
		//draw the particle
		drawParticle(0,0,true);
		
		if (dispArrows) {
			ofSetColor(255, 255, 255);
			ofNoFill();
			ofLine(0, 0, len, 0);
			ofLine(len, 0, len-arrowsize, arrowsize/2);
			ofLine(len, 0, len-arrowsize, -arrowsize/2);
		}
	ofPopMatrix();
	
}


void Particle::drawParticle(float x, float y, bool png) {
	ofSetColor(255, 255, 255, 128);
	if (png == false) {
		ofNoFill();
		ofEllipse(x, y, particleSize, particleSize);
	} else {
        //ofSetColor(255, 255, 255, ofMap( timer, 0, 100, 0, 256 ));
		ofSetColor(217, 237, 215, ofMap( timer, 0, 100, 0, 256 ));
        pEmitter->particleImg.setAnchorPoint( 0.5, 0.5 );
		//pEmitter->particleTex.setAnchorPoint( 0.5, 0.5 );
        //pEmitter->particleTex.draw(x, y, particleSize, particleSize);
		pEmitter->particleImg.draw(x, y, particleSize, particleSize);
	}
}

float Particle::heading2D(ofxVec2f vt) {
	float angle = atan2(-vt.y, vt.x);
	ofRadToDeg(-1*angle);
	return ofRadToDeg(-1*angle);
}

