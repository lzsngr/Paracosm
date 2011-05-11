#include "monster.h"

Monster::Monster()
{
	x = ofRandom(0, ofGetWidth());     
	y = ofRandom(0, ofGetHeight());
	xSpeed = ofRandom(-1, 1);     
	ySpeed = ofRandom(-1, 1);     
	xDir = 1;
	yDir = 1;
	rate = 30;
	
	
	monsterstand.loadSequence("monster/behemoth/stand/stand", "png", 0, 1, 1);
	monsterstand.preloadAllFrames();
	monsterstand.setFrameRate(rate); 

	//monster run
	monsterrun.loadSequence("monster/behemoth/run/run", "png", 0, 23, 1);
	monsterrun.preloadAllFrames();
	monsterrun.setFrameRate(rate); 
	
	roar.loadSound("sounds/roar.mp3");

}


void Monster::update(){
	
	x = x + xSpeed;
	y = y + ySpeed;
	
}



void Monster::draw(){
	ofNoFill();
	
	if(lastx>x){
		xDir = 1;
	}else{
		xDir = -1;
	}
	monsterrun.getFrameForTime(ofGetElapsedTimef())->draw(x-(45*xDir),y-(35*yDir),200*xDir,200*yDir);
/*s
	if ((lastx-x)<.1){
		monsterstand.getFrameForTime(ofGetElapsedTimef())->draw(x-(20*xDir),y-(15*yDir),200*xDir,200*yDir);
	}else{
		monsterrun.getFrameForTime(ofGetElapsedTimef())->draw(x-(20*xDir),y-(15*yDir),200*xDir,200*yDir);
	}
*/	
	//
	rate = 5*abs(lastx-x);
	
	
	if (lit && !roar.getIsPlaying()){
		roar.play();
	}
	
	lastx = x;
	lasty = y;
}

