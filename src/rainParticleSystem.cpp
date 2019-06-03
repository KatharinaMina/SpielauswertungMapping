#include "rainParticleSystem.h"


rainParticleSystem::rainParticleSystem(float startSceneX, float sceneSizeX, float sceneSizeY) {

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
void rainParticleSystem::updateParticleSystem() {

	double deltaT = ofGetLastFrameTime();
	time += deltaT;

	//----------------------------------------------------------//Ertsellen bzw. Löschen von Partikeln
	if ((birthCnt >= 0) && (status == -1)) {		//Ertsellen von Partiklen für Regen
		createParticlesForRain();
	}
	//----------------------------------------------------------//Updaten der Partikel (Bewegung)


	for (int p = 0; p < particles.size(); p++) {
		particles.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(startSceneX, startSceneX + sceneSizeX), 0),
			false, false, false, 0, startSceneX + sceneSizeX, sceneSizeY);						//Partikel werden an beliebige Stelle gezogen
	}

}

//--------------------------------------------------------------
void rainParticleSystem::createParticlesForRain()
{
	for (int i = 0; i < parAmount; i++) {
		particles.push_back(new particle);
		int rgen = ofRandom(startSceneX, startSceneX + sceneSizeX);
		particles.back()->setup(ofVec2f(rgen, sceneSizeY), 20);
	}
	birthCnt = 0;
}

//--------------------------------------------------------------
void rainParticleSystem::drawRainParticleSystem() {

	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->draw();
	}
}



