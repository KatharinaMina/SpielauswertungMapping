#ifndef rainParticleSystem_h
#define rainParticleSystem_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "particle.h"
#include "drawableImage.h"

class RainParticleSystem
{

public:

	RainParticleSystem(float startSceneX, float sceneSizeX, float sceneSizeY);
	~RainParticleSystem(); 

	vector<ofVec2f>attractors;
	vector<Particle*> particles;

	int startSceneX;
	int sceneSizeX;
	int sceneSizeY;
	int maxParticle;
	int picPix;
	int k;
	int status;
	bool tornadoStarted;
	bool editingWarp;
	float birthCnt;
	float maxLife;
	float parAmount;
	float height;
	double time;
	double tornadoStartTime;
	
	void updateParticleSystem();
	void createParticlesForRain();
	void drawRainParticleSystem();


private:

};
#endif 

