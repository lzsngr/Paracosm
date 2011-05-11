#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
	//ofBackground(50, 50, 50);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	xOffset = 82;
	yOffset = 67;
	
	
	//for binned particle system
	int binPower = 2;
	
	particleSystem.setup(ofGetWidth(), ofGetHeight(), binPower);
	
	kParticles = 32;
	float padding = 0;
	float maxVelocity = .5;
	for(int i = 0; i < kParticles * 1024; i++) {
		float x = ofRandom(padding, ofGetWidth() - padding);
		float y = ofRandom(padding, ofGetHeight() - padding);
		float xv = ofRandom(-maxVelocity, maxVelocity);
		float yv = ofRandom(-maxVelocity, maxVelocity);
		BinParticle bParticle(x, y, xv, yv);
		particleSystem.add(bParticle);
	}
	
	timeStep = 1;
	lineOpacity = 128;
	pointOpacity = 255;
	slowMotion = false;
	particleNeighborhood = 4;
	particleRepulsion = 1;
	centerAttraction = .01;

	prevMouseX = 0;
	prevMouseY = 0;
	
	height = ofGetHeight();		
	width = ofGetWidth();
	
	ofSetVerticalSync(true);

	//For TUIO Client 
	//Connect to Port
	myTuio.connect(3333);
	
	//Assign Global TUIO Callback Functions
	ofAddListener( ofEvents.touchDown, this, &testApp::touchDown );
	ofAddListener( ofEvents.touchUp, this, &testApp::touchUp );
	ofAddListener( ofEvents.touchMoved, this, &testApp::touchMoved );
	
	
	myTuioClient = myTuio.client;
	
	ofxVec2f aPos;
	aPos.set(ofGetWidth()/2, ofGetHeight()/2);
	
	
    //3/23/11: ALL REFERENCES TO FIREFLY EMITTER REMOVED
	//Emitter* emitter = new Emitter(1, aPos);
	//allEmitters.push_back ( emitter );
	//emitter = Emitter(1, aPos);
	//emitter.setup();


	isMouseDown = false;
	isTouching = false;
	firstTouch = false;
    emitter.ALLOWGRAVITY = false;
    emitter.ALLOWPERLIN = false;
    emitter.ALLOWTRAILS = false;
	
	//img sequence
	spotlight.loadImage("spotlightb.png");
	//spotlight.loadImage("spotlightbsmall.png");
	//trees.loadImage("trees.h");
	
	//music
	woods.loadSound("sounds/woods.mp3");
	woods.play();

}

//--------------------------------------------------------------
void testApp::update(){
	
	for(int i=0; i<nKids; i++){
		Behemoth[i].update();
		if (!Boy[i].dead){
			Boy[i].update();
		}
	}
	
	//Movement and Interactions Functions - in future iterations this will be moved into a separate AI class system.
	kidMove();
	monsterMove();
	feedingTime();
	
	touchList = myTuioClient->getTuioCursors();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
	glDepthMask(false);
	
	//enable additive blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	//draw spotlight with mouse
	spotlight.draw(mouseX-200,mouseY-200);	
	//spotlight.getFrameForTime(ofGetElapsedTimef())->draw(mouseX-200,mouseY-200);
	
	/*
	if( isTouching ){
		
		for(list<TuioCursor*>::iterator tit = touchList.begin(); tit != touchList.end(); tit++) 
		{
			TuioCursor* cur = (*tit);
			spotlight.draw( ( cur->getX()*ofGetWidth() )-200, ( cur->getY()*ofGetHeight() )-200);
			//spotlight.draw( ( cur->getX()*ofGetWidth() )-xOffset, ( cur->getY()*ofGetHeight() )-yOffset);
		}
		//spotlight.draw(myTouchx-200,myTouchy-200);	
	}
	*/
	
	for(int i=0; i<nKids; i++){
		Boy[i].draw();
		Behemoth[i].draw();
	}
	
	//run binned particle system
	runBinnedParticleSystem();
	
	//debugging
	//render TUIO Cursors and Objs 
	//myTuio.drawCursors();
	//myTuio.drawObjects();
	
    
	if( isMouseDown )
    {
        //emitter.setVelToMouse(mouseX, mouseY);
		//emitter.run();
        //emitter.addParticle(mouseX, mouseY);
    }
	
	//are touches present
	if( isTouching )
    {
		//emitter.run();
        //emitter.addParticle(myTouchx, myTouchy);

		//why doesn't this work? keep getting "BAD ACCESS"
		//draw spotlight with touch
		//list<TuioCursor*>::iterator it = touchList.begin();
		//TuioCursor* tcur = (*it);
		//float xPos = tcur->getX()*ofGetWidth();
		//spotlight.draw(tcur->getX()-200, tcur->getY()-200);	

		//spotlight.draw(myTouchx-200,myTouchy-200);	
    }
	
	//render emitter
	//emitter.render();
	
	prevMouseY = myTouchy;
	prevMouseX = myTouchx;	
	
	ofNoFill();
	ofSetColor(255,255,255,150);
	
	
	if (!woods.getIsPlaying())
		woods.play();
	
	//debugging: get list of tuio objects
	//list<TuioObject*> objectlist = myTuio.getObjects();
	//cout << objectlist.size() << endl;
	
	//draw trees
	ofSetColor(255, 255, 255, 128);
	
	trees.draw(0, 0);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 's') {
		slowMotion = !slowMotion;
		if(slowMotion)
			timeStep = .05;
		else
			timeStep = 1;
	}
	
	if (key == OF_KEY_UP)
		yOffset++;
		
	if (key == OF_KEY_RIGHT)
		xOffset++;
	
	if (key == OF_KEY_DOWN)
		yOffset--;
	
	if (key == OF_KEY_LEFT)
		xOffset--;
	
	
	cout << "xOffset: " << xOffset << endl;
	cout << "yOffset: " << yOffset << endl;
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    isMouseDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    isMouseDown = false;
	emitter.clearAll();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::touchDown(ofTouchEventArgs & touch){
	//debugging
	//cout << " cursor added: " + ofToString(touch.id)+
	//" X: "+ofToString(touch.x)+
	//" Y: "+ofToString(touch.y)
	//<< endl;
	
	isTouching = true;
		
	//set touch cords
	//myTouchx = touch.x * ofGetWidth();
	//myTouchy = touch.y * ofGetHeight();
	
	
	//ofxVec2f pos;
	//pos.set( myTouchx, myTouchy );
	//Emitter* newEmitter = new Emitter(touch.id, pos);
	//emitter.run();
	//emitter.addParticle(touch.x, touch.y);
}

void testApp::touchUp(ofTouchEventArgs & touch){
	//debugging
	//cout << " cursor removed: " + ofToString(touch.id)+
	//" X: "+ofToString(touch.x)+
	//" Y: "+ofToString(touch.y)
	//<< endl;	
	
	isTouching = false;
}


void testApp::touchMoved(ofTouchEventArgs & touch){
	//cout << " cursor updated: " + ofToString(touch.id)+
	//" X: "+ofToString(touch.x)+
	//" Y: "+ofToString(touch.y)
	//<< endl;

	//set touch cords
	myTouchx = touch.x * ofGetWidth();
	myTouchy = touch.y * ofGetHeight();
	
	//emitter.setVelToMouse(myTouchx, myTouchy);
	//allEmitterSetVelToMouse(myTouchx, myTouchy);
}

void testApp::allEmitterSetup() {
	for (int i=0; i < allEmitters.size(); i++) {
		Emitter* e = allEmitters[i];
		e->setup();
	}
}

void testApp::allEmitterSetVelToMouse(int x, int y) {
	for (int i=0; i < allEmitters.size(); i++) {
		Emitter* e = allEmitters[i];
		e->setVelToMouse(x, y);
	}
}


//CHARACTER MOTION//

/*
 While I could have just as easily made a class for all movement, for ease and time I've stored all character motion here.
 
 The motion itself barely constitutes as anything beyond basic game mechanics, yet it needed quite a bit of calibration in order to make it feel natural. 
 */


//--------------------------------------------------------------s
//children run away
void testApp::kidMove(){
	for(int i=0; i<nKids; i++){
		
		//Simple boolean to test child's life
		if ((!Boy[i].dead)){
			
			//If the child moves outside of the table-top their location resets to the bottom.
			if ((Boy[i].x > 0) && (Boy[i].x < width)){
				if ((Boy[i].y > 0) && (Boy[i].y < height)){
					
					//If the child is within the unmasked area, collisions are detected. If not, monsters and children can pass one another freely in the dark.
					//We decided on this namely because the children being eaten would happen too often outside of the player's control. 
					//We wanted the user to control the results rather than the game playing itself out.
					if ((Boy[i].x < myTouchx+100) && (Boy[i].x > myTouchx-100)){
						if((Boy[i].y < myTouchy+100) && (Boy[i].y > myTouchy-100)){
							
							
							//This is not truly a collision detection as much as it signals that the child is within the target area in order for the monster to feast on them. 
							//Rather than having to have the child bump into the monster, the feeding takes place once there is enough proximity between the two, making it easier for the feeding to become an accidental consequence of one's actions.
							if ((Boy[i].x < myTouchx+50) && (Boy[i].x > myTouchx-50)){
								if((Boy[i].y < myTouchy+50) && (Boy[i].y > myTouchy-50)){
									Boy[i].lit = true;
								}
							}
							
							//Set variables to decipher the current location of the player's touches versus the character's x,y locations  
							float prevdist = abs((Boy[i].x-prevMouseX)/(Boy[i].y-prevMouseY));
							float distY = myTouchy-Boy[i].y;
							float distX = myTouchx-Boy[i].x;
							float dist = atan2(distY, distX);
							
							//Child runs in the opposite direction of the mouse. Their speed and directed basedon
							if (prevdist>dist) {
								Boy[i].x -= cos(dist)*7;
								Boy[i].y -= sin(dist)*7;
							}else{
								
							}
						}
					}else{
						//set bool to false
						Boy[i].lit = false;
					}
					//this all reset's the character's location to the opposite end of the screen once they travel off of it.
				}else if(Boy[i].y < 0){
					Boy[i].y = height - 10;
				}else{
					Boy[i].y = 10;
				}	
			}else if(Boy[i].x < 0){
				Boy[i].x = width - 10;
			}else{
				Boy[i].x = 10;
			}
		}else{
			
		}
	}
	
	
}

//--------------------------------------
//MONSTER run away
//it is almost simmilar to the child's interactions, yet the feasting does not alter the conditions  of the movement. Also, the Behemoth moves slower than the children.
//We may add Reapers as another monster type in a future project iteration.
void testApp::monsterMove(){
	for(int i=0; i<nMonster; i++){
		if ((Behemoth[i].x > 0) && (Behemoth[i].x < width)){
			if ((Behemoth[i].y > 0) && (Behemoth[i].y < height)){
				if ((Behemoth[i].x < myTouchx+200) && (Behemoth[i].x > myTouchx-200)){
					if((Behemoth[i].y < myTouchy+200) && (Behemoth[i].y > myTouchy-200)){
						
						//set bool to true
						if ((Behemoth[i].x < myTouchx+50) && (Behemoth[i].x > myTouchx-50)){
							if((Behemoth[i].y < myTouchy+50) && (Behemoth[i].y > myTouchy-50)){
								Behemoth[i].lit = true;
							}
						}
						
						//set variables
						float Bprevdist = abs((Behemoth[i].x-prevMouseX)/(Behemoth[i].y-prevMouseY));
						float BdistY = myTouchy-Behemoth[i].y;
						float BdistX = myTouchx-Behemoth[i].x;
						float Bdist = atan2(BdistY, BdistX);
						
						//runs away
						if (Bprevdist>Bdist) {
							Behemoth[i].x -= cos(Bdist)*3;
							Behemoth[i].y -= sin(Bdist)*3;
						}else{
							
						}
					}
				}else{
					//set bool to false
					Behemoth[i].lit = false;
				}
			}else if(Behemoth[i].y < 0){
				Behemoth[i].y = height - 10;
			}else{
				Behemoth[i].y = 10;
			}	
		}else if(Behemoth[i].x < 0){
			Behemoth[i].x = width - 10;
		}else{
			Behemoth[i].x = 10;
		}
	}
	
}

//-----------------------
//FEEDING TIME
void testApp::feedingTime(){
	for(int j=0; j<nMonster; j++){
		for(int i=0; i<nKids; i++){
			if ((Behemoth[j].lit)&&(Boy[i].lit)){
						Boy[i].eaten();
					Boy[i].dead = true;
				
			}
		}
	}
}


void testApp::runBinnedParticleSystem() {
	
	particleSystem.setTimeStep(timeStep);
	
	//ofEnableAlphaBlending();
	//ofSetColor(255, 255, 255, lineOpacity);
	ofSetColor(0, 0, 0, lineOpacity);
	particleSystem.setupForces();
	// apply per-particle forces
	glBegin(GL_LINES);
	for(int i = 0; i < particleSystem.size(); i++) {
		BinParticle& cur = particleSystem[i];
		// global force on other particles
		particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
		// forces on this particle
		cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());
		cur.addDampingForce();
	}
	glEnd();
	// single global forces
	particleSystem.addAttractionForce(ofGetWidth() / 2, ofGetHeight() / 2, ofGetWidth(), centerAttraction);
	//if(isMousePressed)
	if(isMouseDown)
		particleSystem.addRepulsionForce(mouseX, mouseY, 100, 10);

	/*
	if(isTouching) {
		for(list<TuioCursor*>::iterator tit = touchList.begin(); tit != touchList.end(); tit++) 
		{
			TuioCursor* cur = (*tit);
			particleSystem.addRepulsionForce(cur->getX()*ofGetWidth(), cur->getY()*ofGetHeight(), 100, 10);
		}
		
		//particleSystem.addRepulsionForce(myTouchx, myTouchy, 100, 10);
	}
	*/
	particleSystem.update();
		
	//ofSetColor(255, 255, 255, pointOpacity);
	ofSetColor(100, 100, 100, pointOpacity);
	particleSystem.draw();
	//ofDisableAlphaBlending();
	
	ofSetColor(255, 255, 255);
	
	//Debugging
	//ofDrawBitmapString(ofToString(kParticles) + "k particles", 32, 32);
	//ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
	
}

