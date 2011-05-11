/*
 *  kid.h
 *  emptyExample
 *
 *  Created by Azil on 3/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _KID
#define _KID

#include "ofMain.h"
#include "ofxImageSequence.h"


class Kid {
public:
	
	//methods
	void update();
	void draw();
	void eaten();
	
	//constructor
	Kid();
	
	//variables
	float y, x, lastx, lasty;
	bool lit, dead, house;
	float xDir, yDir;
	float r;
	float ySpeed, xSpeed;
	float startf, endf;
	float rate;
	
	//BOY
	ofxImageSequence boyrun;
	ofxImageSequence boywalk;
	ofxImageSequence boystand;
	ofxImageSequence boydead;
	
	//sounds
	ofSoundPlayer laugh;

private:
};

#endif