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

	imageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageForAttractors,  string imageName);
	~imageParticleSystem();

	vector<ofVec2f>attractors;
	vector<particle*> particles;

	int sceneSizeX;
	int sceneSizeY;
	int imageHeight;
	int maxParticle;
	int picPix;
	int k;
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

	void setSymbolAttractorIsSet(bool value);
	void setCloudAttractorIsSet(bool value);

	void updateParticleSystem();
	void drawImageParticleSystem();

	void imageParticleSystem::changeAttractorImage(ofImage newAttractorImage);

private:
	drawableImage* imageToDraw;
	vector<ofVec2f> pixelInVector(ofImage a);
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
};
#endif 
#pragma once