#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Emitter.h"
#include "BinParticle.h"
#include "ParticleSystem.h"

#include "ofxTuioClient.h"

#include "kid.h"
#include "monster.h"

#include <vector>
#include <list>

#define nKids 5
#define nMonster 5

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		
		//FOR TUIO
		ofxTuioClient myTuio;
		TuioClient* myTuioClient;
		list<TuioCursor*> touchList;
    
        bool isMouseDown;
		bool isTouching;
		bool firstTouch;
		float myTouchx;
		float myTouchy;
		int xOffset;
		int yOffset;
	
		Emitter emitter;	
		vector<Emitter*> allEmitters;
		void allEmitterSetup();
		void allEmitterSetVelToMouse(int x, int y);
		
		
		//TOUCH RELATED
		void touchDown( ofTouchEventArgs &touch );
		void touchUp( ofTouchEventArgs &touch);
		void touchMoved( ofTouchEventArgs &touch);
	

		//CHARACTER RELATED
		//Movement
		void kidMove();
		void monsterMove();
		void feedingTime();
		
		//Setting Arrays for AI
		Kid Boy[nKids];
		//Kid Girl[nKids];
		Monster Behemoth[nMonster];
		//Monster Shade[nMonster];
		
		int	width, height;
		float prevMouseX, prevMouseY;
		bool playing;
		
		ofImage spotlight;
		ofImage trees;
		ofSoundPlayer woods;
		
	
		//BINNED PARTICLE RELATED
		float timeStep;
		int lineOpacity, pointOpacity;
		float particleNeighborhood, particleRepulsion;
		float centerAttraction;
		
		int kParticles;
		bool isMousePressed, slowMotion;
		ParticleSystem particleSystem;
		void runBinnedParticleSystem();
	
	
};

#endif
