#ifndef particle_h
#define particle_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"



class particle
{
public:
    
    particle();
    ~particle();
    
    ofVec2f vel;
	ofVec2f velocity2;
    ofVec2f pos;
    ofVec2f pos2;
    ofVec2f force;
	ofVec2f force2;

	ofColor color;
    ofColor color2;

    float maxLife;
    float age;
    float getAgeNorm();
	float size;
	float mass;
	float deleteAfterLeavingSceneY();
	bool deleteAfterLeavingSceneX();
	
	int k;
	int l;
	int ticksToMoveParticlesToRight;
	int counterToMoveParticlesToRight;
	bool pL;
	bool particleLeftScene;
  
    void setup(ofVec2f pos, ofVec2f pos2, float maxAge);
    void startTornado();
    void startStage1();
    void updateStage1();
    void updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool tornadoIsFinished, int imageHeight, float sceneSizeX, float sceneSizeY);
    void draw();
    void draw2();
    void keyReleased(int key);
    void keyPressed(int key);
  
private: 

};
#endif 
