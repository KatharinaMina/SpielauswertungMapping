#ifndef drawableImage_h
#define drawableImage_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <stdio.h>



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
	int yToMoveInCloud;
	int maxYpositionForPicture;
	int redImageColor;
	int greenImageColor;
	int blueImageColor;
	int ticksToMovePictureToRight;
	int counterToMovePictureToRight;
	int imageHeight;
	int newMaxHeight;
	int newXToMoveInCloud;
	int newYToMoveInCloud;
	int maxYInWave;
	int minYInWave;
	float newCloudVelX;
	float newCloudVelY;
	float frameTime;
	int getHeight();
	int getWidth();
	int getMaxHeight();
	bool pL;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
	bool pastMiddle;
	bool pastYMax;
	bool pastMaxYInWave;
	bool test;


	void updateImage(float sceneSizeX, float sceneSizeY);
	void drawImage(float sceneSizeX, float sceneSizeY);
	void doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY);
	void doMovementOfImageIntoCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY);
	int setMaxHeightPosition(float sceneSizeY);

	int setSpeedAtCloud(float sceneSizeX);
	int setYAtCloud(float sceneSizeY);
	bool imageIsOnTop(float sceneSizeY);
	float getImagePosX(float sceneSizeX);
	float getImagePosY(float sceneSizeY);
	vector<float>maxHeightPositions;
	vector<float>cloudVelX;
	vector<float>cloudVelY;
	ofImage changeImageColor(ofImage imageToDraw, int r, int g, int b);

private:

};
#endif 
