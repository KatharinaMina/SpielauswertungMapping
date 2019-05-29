#ifndef rainParticleSystem_h
#define rainParticleSystem_h
#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "particle.h"
#include "drawableImage.h"

class rainParticleSystemStele_2
{
    
public:
    
    rainParticleSystemStele_2(int sceneSizeX, int sceneSizeY);
    ~rainParticleSystemStele_2();
    
    vector<ofVec2f>attractors;
    vector<particle*> particles;
    
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
    void createParticleSystem();
    void deleteParticleSystem();
    void drawRainParticleSystem();
    
    
private:
    
};
#endif


