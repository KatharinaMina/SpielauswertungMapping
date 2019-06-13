#ifndef particle_h
#define particle_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxXmlSettings.h"
#include "ofxOpenCv.h"


enum particleMode {
	PARTICLE_MODE_DEFAULT,
	PARTICLE_MODE_ATTRACTOR,
	PARTICLE_MODE_RAIN,
	PARTICLE_MODE_RADIAL,
	PARTICLE_MODE_DETRACTOR,
	PARTICLE_MODE_POLY,
	PARTICLE_MODE_BRUNIG
};

class particle
{
public:
    
    particle();
    ~particle();
    
    ofVec2f vel;
	ofVec2f velocity2;
	ofVec2f pos;   
    ofVec2f force;
	ofColor color;

	void setMode(particleMode newMode);
	particleMode mode;

    float maxLife;
    float age;
    float getAgeNorm();
	float size;
	float mass;
	float deleteAfterLeavingSceneY();
	bool deleteAfterLeavingSceneX();
	
	int valueToMoveToTop;
	int valueToMoveToRight;
	int ticksToMoveParticlesToRight;
	int counterToMoveParticlesToRight;
	bool pL;
	bool particleLeftScene;
  
    void setup(ofVec2f pos, float maxAge);
    void updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool imageIsOnTop, bool tornadoIsFinished, int imageHeight, int imageWidth, float sceneSizeX, float sceneSizeY);
	void doMovementOfParticlesAtRain(bool tornadoIsFinished, double deltaT, float sceneSizeX);
	void doMovementOfParticlesAtSymbols(double deltaT, ofVec2f &attractor);
	void doMovementOfParticlesAtRocketEffect(float sceneSizeY, int imageHeight, int imageWidth, float sceneSizeX, ofVec2f &attractor, double deltaT);
	void doMovementOfHexagonOnTheTop(ofVec2f &attractor, float sceneSizeX, double deltaT);
    void draw();

  
private: 
    //ofImage tex;
};
#endif 
