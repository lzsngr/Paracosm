#include "kid.h"

Kid::Kid()
{
	x = ofRandom(0, ofGetWidth());      
	y = ofRandom(0, ofGetHeight());
	r = 0;
	xSpeed = ofRandom(-1, 1);     
	ySpeed = ofRandom(-1, 1); 
	xDir = 1;
	yDir = 1;
	rate = 30;

	boyrun.loadSequence("boy/run/run", "png", 0, 23, 1);
	boyrun.preloadAllFrames();
	boyrun.setFrameRate(rate); 
	
	
	boydead.loadSequence("boy/dead/dead", "png", 0, 11, 1);
	boydead.preloadAllFrames();
	boydead.setFrameRate(30); 
	
	
	boystand.loadSequence("boy/stand/laughing", "png", 0, 11, 1);
	boystand.preloadAllFrames();
	boystand.setFrameRate(30); 
	
	laugh.loadSound("sounds/laugh.mp3");

}


void Kid::update(){
	
	x = x + xSpeed;
	y = y + ySpeed;
	

}


void Kid::draw(){
	
	ofSetColor(255,255,255);
	/*
	 ofFill();
	ofCircle(x,y,5);
	*/
	
//	ofNoFill();

	if(lastx>x){
		xDir = 1;
	}else{
		xDir = -1;
	}
		
	if (!dead){
		if (lit){
			if (!laugh.getIsPlaying())
				laugh.play();
	
			if ((lastx-x)<1){
				boystand.getFrameForTime(ofGetElapsedTimef())->draw(x-(20*xDir),y-(15*yDir),50*xDir,100*yDir);
			}else{
				boyrun.getFrameForTime(ofGetElapsedTimef())->draw(x-(20*xDir),y-(15*yDir),100*xDir,100*yDir);
			}
		}else{
			boyrun.getFrameForTime(ofGetElapsedTimef())->draw(x-(20*xDir),y-(15*yDir),100*xDir,100*yDir);
		}
		
	}else{
		boydead.getFrameForTime(ofGetElapsedTimef())->draw(x-20,y-15,100,100);
		
		}
	rate = 5*abs(lastx-x);
	
	   lastx = x;
	   lasty = y;
}
	
void Kid::eaten(){
	r=255;
	dead = true;
	
}
