#ifndef _MONSTER
#define _MONSTER

#include "ofMain.h"

//this addon is a very lovely png/jpg sequencer. 
//Rather than working with sprite-sheets[laborious] or loading in slow .mov files[requiring a lot of memory], it loads in image sequences into a simple enough array but makes calling the images a breeze.
#include "ofxImageSequence.h"

class Monster {
public:
	
	//methods
	void update();
	void draw();
	
	//constructor
	Monster();
	
	//variables
	float y, x, lasty, lastx;
	bool lit, house;
	float xDist, yDist;
	float xSpeed, ySpeed;
	float xDir, yDir;
	float startf, endf;
	float rate;
	
	ofxImageSequence monsterstand;
	ofxImageSequence monsterrun;
	ofxImageSequence monstereat;
	
	ofSoundPlayer roar;
	

	
private:
};

#endif