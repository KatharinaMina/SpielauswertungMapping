#ifndef rainParticleSystem_h
#define rainParticleSystem_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "particle.h"
#include "drawableImage.h"

class rainParticleSystem
{

public:

	rainParticleSystem(float startSceneX, float sceneSizeX, float sceneSizeY);
	~rainParticleSystem(); 

	vector<ofVec2f>attractors;
	vector<particle*> particles;

	int startSceneX;
	int sceneSizeX;
	int sceneSizeY;
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

	void updateParticleSystem();
	void createParticlesForRain();
	void drawRainParticleSystem();


private:

};
#endif 

