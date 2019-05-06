#pragma once

#include "ofMain.h"
#include "ofxWarp.h"

#include "particleSwitch.h"

#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"
#include "ofxCv.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void startTornado();
		void updateTornado();

		void drawImageIntoScreen(ofImage imageToDraw);

		vector <ofVec2f> pixelInVector(ofImage a);
		ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

	
	private:
		//warp
		ofxWarpController warpController;
		ofTexture tex;
		ofRectangle area;
		ofVec2f sceneSize;
		ofVec2f force;

		ofFbo fbo;

		vector<ofVec2f>attractors;
		vector<particle02*> system;
		
		ofImage img;
		ofImage fileImage1;
		ofImage fileImage2;
		ofImage fileImage3;
		ofImage fileImage4;
		ofImage fileImage5;
		ofImage fileImage6;
		ofImage fileImage7;
		ofImage fileImage8;

		ofColor color;
		

		int maxParticle;
		int picPix;
		bool symbolAttractorIsSet;
		bool cloudAttractorIsSet;
		bool tornadoIsFinished;
		bool tornadoStarted;
		bool drawAllPixel;
		bool type1;
		bool type2;
		bool type3;
		bool editingWarp;
		

		//------------------------------------------
		float birthCnt;
		float maxLife;
		float parAmount;
		float height;
		double time;
		double tornadoStartTime;
		int status;
};
