#ifndef drawableImage_h
#define drawableImage_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"



class drawableImage
{

public:

	drawableImage(string imageName);
	~drawableImage();

	ofColor color;

	float maxLife;
	float age;
	float size;
	float mass;
	int y;
	int x;
	int ticksToMovePictureToRight;
	int counterToMovePicctureToRight;
	bool pL;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;

	void updateImage(float sceneSizeX, float sceneSizeY);

	ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

	int getHeight();

	ofImage fileImageHex;
	ofImage imageToDraw;


private:

};
#endif 
#pragma once
