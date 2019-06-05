#ifndef drawableImage_h
#define drawableImage_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"



class drawableImage
{

public:

	drawableImage(string imageName, float sceneSizeX, float sceneSizeY);
	~drawableImage();

	ofColor color;

	float maxLife;
	float age;
	float size;
	float mass;
	int y;
	int x;
	int maxYpositionForPicture;
	int redImageColor;
	int greenImageColor;
	int blueImageColor;
	int ticksToMovePictureToRight;
	int counterToMovePictureToRight;
	bool pL;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
	bool pastMiddle;

	void updateImage(float sceneSizeX, float sceneSizeY);

	void drawImage(float sceneSizeX, float sceneSizeY);

	void doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY);

	ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

	int getHeight();
	bool imageIsOnTop(float sceneSizeY);

	float getImagePosX(float sceneSizeX);
	float getImagePosY(float sceneSizeY);
	int getMaxHeight();

	ofImage fileImageHex;
	ofImage imageToDraw;


private:

};
#endif 
#pragma once
