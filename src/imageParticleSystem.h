#ifndef imageParticleSystem_h
#define imageParticleSystem_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "particle.h"
#include "drawableImage.h"
#include <stdio.h>

class ImageParticleSystem
{

public:

	ImageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageHex, string imageName);
	~ImageParticleSystem();

	vector<ofVec2f>attractors;
	vector<Particle*> particles;
	ofImage fileImageHex;
	ofImage fileImageCloud;

	int sceneSizeX;
	int sceneSizeY;
	int imageHeight;
	int imageWidth;
	int maxParticle;
	int picPix;
	int k;
	int ticksToMoveImageToTop;
	int counterToMoveImageToTop;
	int status;
	bool tornadoStarted;
	bool editingWarp;
	bool imageReachedTopAndAttractorIsChanged;
	float birthCnt;
	float maxLife;
	float parAmount;
	float height;
	double time;
	double tornadoStartTime;	

	void updateParticleSystem();
	void deleteParticlesForRocketEffect();
	void deleteParticlesForHexagon();
	void createParticlesForHexagonInSymbol();
	void createParticlesForHexagonInCloud();
	void deleteParticleAfterLeavingOntheRightAndCreateThemOnTheLeft(int p);
	void drawImageParticleSystem();
	void setSymbolAttractorIsSet(bool value);
	void setCloudAttractorIsSet(bool value);
	void changeAttractorImage(ofImage newAttractorImage);

private:
	DrawableImage* imageToDraw;
	vector<ofVec2f> pixelInVector(ofImage a);
	void setAttractorsFromHexagonFromPicture();
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
};
#endif 
#pragma once
