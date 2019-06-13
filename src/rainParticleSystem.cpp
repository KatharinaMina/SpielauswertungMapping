#include "rainParticleSystem.h"


RainParticleSystem::RainParticleSystem(float startSceneX, float sceneSizeX, float sceneSizeY) {

	this->startSceneX = startSceneX;
	this->sceneSizeX = sceneSizeX;
	this->sceneSizeY = sceneSizeY;

	maxParticle = 40;
	birthCnt = 0;
	parAmount = 2;
	tornadoStartTime = -1000;
	time = 0;
	status = -1;

}

//--------------------------------------------------------------
void RainParticleSystem::updateParticleSystem() {

	double deltaT = ofGetLastFrameTime();
	time += deltaT;

	//----------------------------------------------------------
	if ((birthCnt >= 0) && (status == -1)) {					//Ertsellen von Partiklen für Regenpartikelsystem
		createParticlesForRain();
	}
	//----------------------------------------------------------//Updaten der Partikel (Bewegung)


	for (int p = 0; p < particles.size(); p++) {				//´Bewegung der Partikel von unten nach oben
		particles.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(startSceneX, startSceneX + sceneSizeX), 0),
			false, false, false, 0, 0, startSceneX + sceneSizeX, sceneSizeY);						
	}

}

//--------------------------------------------------------------
void RainParticleSystem::createParticlesForRain()
{
	for (int i = 0; i < parAmount; i++) {

		particles.push_back(new Particle);
		int rgen = ofRandom(startSceneX, startSceneX + sceneSizeX);

		particles.back()->setup(ofVec2f(rgen, sceneSizeY), 20);
	}
	birthCnt = 0;
}

//--------------------------------------------------------------
void RainParticleSystem::drawRainParticleSystem() {

	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->draw();
	}
}



