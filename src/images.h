#ifndef images_h
#define images_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"



class images
{
public:

	images();
	~images();

	ofVec2f vel;
	ofVec2f velocity2;
	ofVec2f pos;
	ofVec2f force;
	ofVec2f force2;

	ofColor color;

	float maxLife;
	float age;
	float getAgeNorm();
	float size;
	float mass;
	float shallBeKilled();
	bool pL;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
	bool tornadoIsFinished;

	void setup();
	void drawImageIntoScreen(float sceneSizeX, float sceneSizeY);
	void updateImage();
	void draw();
	void keyReleased(int key);
	ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

	ofImage fileImage1;
	ofImage fileImage2;
	ofImage fileImage3;
	ofImage fileImage4;
	ofImage fileImage5;
	ofImage fileImage6;
	ofImage fileImage7;
	ofImage fileImage8;
	ofImage imageToDraw;

private:

};
#endif 
