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
	float deleteAfterLeavingSceneY();
	int y;
	int x;
	int ticksToMovePictureToRight;
	int counterToMovePicctureToRight;
	bool pL;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
	bool tornadoIsFinished;

	void setup();
	void drawImageIntoScreen(float sceneSizeX, float sceneSizeY);
	void updateImage(float sceneSizeX, float sceneSizeY);
	void draw();
	void keyReleased(int key);
	ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

	ofImage fileImageHex;
	ofImage fileImageUT;
	ofImage fileImageTU;
	ofImage fileImageUW;
	ofImage fileImageAWU;
	ofImage fileImageATU;
	ofImage fileImageCloud;
	ofImage imageToDraw;
	ofImage attractorToDraw;
	ofImage ima;

private:

};
#endif 
