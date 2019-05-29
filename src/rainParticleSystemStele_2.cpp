#include "rainParticleSystemStele_2.h"


rainParticleSystemStele_2::rainParticleSystemStele_2(int sceneSizeX, int sceneSizeY) {
    
    this->sceneSizeX = sceneSizeX;
    this->sceneSizeY = sceneSizeY;
    
    maxParticle = 50;
    birthCnt = 0;
    parAmount = 4;
    tornadoStartTime = -1000;
    time = 0;
    status = -1;
    
}

//--------------------------------------------------------------
void rainParticleSystemStele_2::updateParticleSystem() {
    
    double deltaT = ofGetLastFrameTime();
    time += deltaT;
    
    //----------------------------------------------------------//Ertsellen bzw. Lˆschen von Partikeln
    if ((birthCnt >= 0) && (status == -1)) {        //Ertsellen von Partiklen f¸r Regen
        createParticlesForRain();
    }
    //----------------------------------------------------------//Updaten der Partikel (Bewegung)
    
    
    for (int p = 0; p < particles.size(); p++) {
        particles.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(sceneSizeX, sceneSizeX), 0),
                                        false, false, false, 0, sceneSizeX, sceneSizeY);                        //Partikel werden an beliebige Stelle gezogen
    }
    
}

//--------------------------------------------------------------
void rainParticleSystemStele_2::createParticlesForRain()
{
    for (int i = 0; i < parAmount; i++) {
        particles.push_back(new particle);
        int rgen = ofRandom(((sceneSizeX/2)+10), sceneSizeX);
        particles.back()->setup(ofVec2f(rgen, sceneSizeY), 20);
    }
    birthCnt = 0;
}

//--------------------------------------------------------------
void rainParticleSystemStele_2::drawRainParticleSystem() {
    
    for (int i = 0; i < particles.size(); i++) {
        particles.at(i)->draw();
        
    }
}




