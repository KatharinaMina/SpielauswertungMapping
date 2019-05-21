#ifndef particleSwitch_hpp
#define particleSwitch_hpp
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"



class particle02
{
public:
    
    particle02();
    ~particle02();
    
    ofVec2f vel;
	ofVec2f velocity2;
    ofVec2f pos;
    ofVec2f force;
	ofVec2f force2;

	ofColor color;

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
  
    void setup(ofVec2f pos, float maxAge);
    void startTornado();
    void startStage1();
    void updateStage1();
    void updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool tornadoIsFinished, int imageHeight, float sceneSizeX, float sceneSizeY);
    void draw();
    void keyReleased(int key);
    void keyPressed(int key);
  
private: 

};
#endif 
