#ifndef imageParticleSystem_h
#define imageParticleSystem_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "particle.h"
#include "drawableImage.h"

class imageParticleSystem
{

public:

	imageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageHex, string imageName);
	~imageParticleSystem();

	vector<ofVec2f>attractors;
	vector<particle*> particles;

	int sceneSizeX;
	int sceneSizeY;
	int imageHeight;
	int maxParticle;
	int picPix;
	int k;
	int ticksToMoveImageToTop;
	int counterToMoveImageToTop;
	bool tornadoStarted;
	bool editingWarp;
	//------------------------------------------
	float birthCnt;
	float maxLife;
	float parAmount;
	float height;
	double time;
	double tornadoStartTime;
	int status;
	bool imageReachedTopAndAttractorIsChanged;

	void setSymbolAttractorIsSet(bool value);
	void setCloudAttractorIsSet(bool value);

	void updateParticleSystem();
	void deleteParticlesForRocketEffect();
	void deleteParticlesForHexagon();
	void createParticlesForHexagonInSymbol();
	void createParticlesForHexagonInCloud();
	void deleteParticleAfterLeavingOntheRightAndCreateThemOnTheLeft(int p);
	void drawImageParticleSystem();

	ofImage fileImageHex;
	ofImage fileImageCloud;

	void changeAttractorImage(ofImage newAttractorImage);

private:
	drawableImage* imageToDraw;
	vector<ofVec2f> pixelInVector(ofImage a);
	void setAttractorsFromHexagonFromPicture();
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
};
#endif 
#pragma once
