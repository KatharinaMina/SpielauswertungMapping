#pragma once

#include "ofMain.h"
#include "ofxWarp.h"

#include "particle.h"
#include "drawableImage.h"
#include "imageParticleSystem.h"
#include "rainParticleSystem.h"


#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"
#include "ofxCv.h"



class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


private:
	//warp
	ofxWarpController warpController;
	ofTexture tex;
	ofRectangle area;
	ofVec2f sceneSize;
	ofVec2f force;

	ofImage img;
	ofImage fileImageHex;
	ofImage imageToDraw;

	ofImage drawImage;

	ofColor color;

	ofFbo fbo;

	vector<ofVec2f>attractors;
	vector<Particle*> system;

	vector<ImageParticleSystem*> imageParticleSystems;
	vector<RainParticleSystem*> rainParticleSyst;

	int currentImage;
	int maxParticle;
	int picPix;
	int k;
	int ticksToMoveParticlesToRight;
	int counterToMoveParticlesToRight;
	bool rainIsActive;
	bool editingWarp;



};
