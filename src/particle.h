#ifndef particle_h
#define particle_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxXmlSettings.h"
#include "ofxOpenCv.h"


enum particleMode {

};

class Particle
{
public:
    
    Particle();
    ~Particle();
    
    ofVec2f vel;
	ofVec2f velocity2;
	ofVec2f pos;   
    ofVec2f force;
	ofColor color;
	particleMode mode;

    float maxLife;
    float age;
    float getAgeNorm();
	float size;
	float mass;
	float deleteAfterLeavingSceneY();
	bool deleteAfterLeavingSceneX();
	bool pL;
	bool particleLeftScene;
	
	int valueToMoveToTop;
	int valueToMoveToRight;
	int ticksToMoveParticlesToRight;
	int counterToMoveParticlesToRight;

  
    void setup(ofVec2f pos, float maxAge);
    void updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool imageIsOnTop, bool tornadoIsFinished, int imageHeight, int imageWidth, float sceneSizeX, float sceneSizeY);
	void doMovementOfParticlesAtRain(bool tornadoIsFinished, double deltaT, float sceneSizeX);
	void doMovementOfParticlesAtSymbols(double deltaT, ofVec2f &attractor);
	void doMovementOfParticlesAtRocketEffect(float sceneSizeY, int imageHeight, int imageWidth, float sceneSizeX, ofVec2f &attractor, double deltaT);
	void doMovementOfHexagonOnTheTop(ofVec2f &attractor, float sceneSizeX, double deltaT);
    void draw();
	void setMode(particleMode newMode);

  
private: 
    //ofImage tex;
};
#endif 
