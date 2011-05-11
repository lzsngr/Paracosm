/*
 *  Emitter.cpp
 *  ParticlesTuio
 *
 *  Created by Miguel Bermudez on 3/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Emitter.h"

Emitter::Emitter() {
	
}

Emitter::Emitter(int num, ofxVec2f v) {
	origin = v;
    loc.set( 0, 0 );
    vel.set( 0, 0 );
    velToMouse.set( 0, 0 );
	num_particles = num;
}

void Emitter::setup() {
	
    for (int i=0; i < num_particles; i++) {
		particles.push_back( new Particle( this, vel, origin ) );
	}
    
	particleImg.loadImage( "firefly4.png" );
    particleTex.allocate(128, 128, GL_RGBA);
    particleTex.loadData(particleImg.getPixels(), 128, 128, GL_RGBA);
	
	emitterImg.loadImage("emitter.png");
    emitterTex.allocate(256, 256, GL_RGBA);
    emitterTex.loadData(emitterImg.getPixels(), 256, 256, GL_RGBA);

	
}

void Emitter::run() {
	for (int i = particles.size()-1; i >= 0; i--) {
		particles[i]->run();
		
		if ( particles[i]->dead() ) {
			
			//if i=5 and we want to delete that from the vector, get the 1st iterator and add i-1 to it ( i.e 1+(5-1) = 5
			//c++ is weird and unforgiving
			particles.erase( particles.begin() + ( i-1 ) ); //get the first iterator and add "i" elements to delete "i" from vector
			
		}
	}
}

void Emitter::setVelToMouse(int mX, int mY) 
{
    
    velToMouse.set( mX - loc.x, mY - loc.y );
	vel = velToMouse.getInterpolated( velToMouse, 0.35f );

	//set position
    loc += vel;
}

void Emitter::addParticle() {

	particles.push_back( new Particle( this, vel, origin ) );
}

void Emitter::addParticle( float x, float y ) {
    
    //get velocity from mouse pos
    //velToMouse.set( x - loc.x, y - loc.y );
    //vel = velToMouse.getInterpolated( velToMouse, 0.35f );

	//setVelToMouse(x, y);
    
    //set position
    //loc += vel;
	

	//push particle to our particle vector
    particles.push_back( new Particle( this, vel, loc ) );
}

void Emitter::render() {	

	ofSetColor(255, 255, 255);
	emitterTex.setAnchorPoint( 0.5, 0.5 );
	emitterTex.draw(loc.x-75, loc.y-75, 150, 150);

}

void Emitter::clearAll() {
	particles.clear();
}

vector<Particle*> Emitter::getParticles() {
	return particles;
}


