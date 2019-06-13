#ifndef drawableImage_h
#define drawableImage_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"



class DrawableImage
{

public:

	DrawableImage(string imageName, float sceneSizeX, float sceneSizeY);
	~DrawableImage();

	ofColor color;
	ofImage fileImageHex;
	ofImage imageToDraw;

	float maxLife;
	float age;
	float size;
	float mass;
	int yToMoveIntoCloud;
	int xToMoveInCloud;
	int maxYpositionForPicture;
	int redImageColor;
	int greenImageColor;
	int blueImageColor;
	int ticksToMovePictureToRight;
	int counterToMovePictureToRight;
	int imageHeight;
	int newMaxHeight;
	int getHeight();
	int getWidth();
	int getMaxHeight();
	bool pL;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
	bool pastMiddle;

	void updateImage(float sceneSizeX, float sceneSizeY);
	void drawImage(float sceneSizeX, float sceneSizeY);
	void doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY);
	int setMaxHeightPosition(float sceneSizeY);
	bool imageIsOnTop(float sceneSizeY);
	float getImagePosX(float sceneSizeX);
	float getImagePosY(float sceneSizeY);
	vector<float>maxHeightPositions;
	ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

private:

};
#endif 
#pragma once
