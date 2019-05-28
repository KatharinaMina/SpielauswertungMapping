#include "particle.h"

particle::particle() {

}

//--------------------------------------------------------------
particle::~particle() {

}

//--------------------------------------------------------------
void particle::setup(ofVec2f pos, float maxAge) {
	this->pos = pos;									//pointer auf Position ofVec2f position
	vel.set(ofRandom(-20.0, 20.0), ofRandom(-90, -100));//Die Bewegungsrichtung

	age = 0.0;											//Alter ist am Anfang 0
	maxLife = ofRandom(maxAge - 5, maxAge);				//Wie lange der Partikel maximal leben soll
	size = ofRandom(2, 3);								//Unterschiedliche Partikelgr��e
	mass = ofRandom(100, 200);							//ver�ndert die Partikelgeschwindigkeit
	color.set(5, 241, 219);
	k = 0;
	l = 0;
	ticksToMoveParticlesToRight = 70;
	counterToMoveParticlesToRight = 0;
	particleLeftScene = false;
}

//--------------------------------------------------------------
void particle::updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool imageIsOnTop, bool tornadoIsFinished, int imageHeight, float sceneSizeX, float sceneSizeY) {

	doMovementOfParticlesAtRain(tornadoIsFinished, deltaT, sceneSizeX);

	if (cloudAttractorIsSet == true) {
		doMovementOfParticlesAtRocketEffect(sceneSizeY, imageHeight, sceneSizeX, attractor, deltaT);
	}

	if (tornadoIsFinished == true && cloudAttractorIsSet == false) {
		doMovementOfParticlesAtSymbols(deltaT, attractor);				//Position = m/s * s [Partikel bleiben statisch]
	}

	if (imageIsOnTop == true) {
		doMovementOfHexagonOnTheTop(attractor, sceneSizeX, deltaT);
	}

}

//--------------------------------------------------------------
void particle::doMovementOfParticlesAtRain(bool tornadoIsFinished, double deltaT, float sceneSizeX)
{
	if (tornadoIsFinished == false) {
		pos += vel * deltaT;
		age += deltaT;

		if (pos.x >= sceneSizeX) {
			pos.x = 0;
		}
	}
}

//--------------------------------------------------------------
void particle::doMovementOfParticlesAtSymbols(double deltaT, ofVec2f &attractor)
{
	k = 0;
	l = 0;
	counterToMoveParticlesToRight = 0;

	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;			//Anziehungskraft						

	if (50 < force.length() < 150) {
		force = 8 * force.getNormalized();		//Anziehungskraft des Attraktors auf die Partikel

		vel += force;							//Bewegung zum Attraktor
		vel = mass * vel.getNormalized();
	}
	else if (force.length() < 500) {
		force = 5 * force.getNormalized();

		vel += force;
		vel = mass * vel.getNormalized();
	}
	else {
		force = 1 * force.getNormalized();
		vel += force;
		vel = mass * vel.getNormalized();
	}
	pos += (vel / 1.5 * deltaT);
}

//--------------------------------------------------------------
void particle::doMovementOfParticlesAtRocketEffect(float sceneSizeY, int imageHeight, float sceneSizeX, ofVec2f &attractor, double deltaT)
{
	// setzen des Attraktors und der Bewegugsgeschwindigkeit
	int y = ((sceneSizeY / 2) + imageHeight);
	int x = ofRandom(sceneSizeX / 2 - imageHeight / 2, sceneSizeX / 2 + imageHeight / 2);

	ofVec2f force2 = attractor - pos;
	if (y - k - imageHeight > 250) {
		k += 2;
	}
	else if (y - k - imageHeight > 10) {
		k += 2;

	}
	else if (counterToMoveParticlesToRight < ticksToMoveParticlesToRight) {
		counterToMoveParticlesToRight++;
	}
	else if (y - k - imageHeight <= 10) {
		l += 3;
	}

	attractor.set(x + l, y - k);


	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;			//Anziehungskraft						

	if (50 < force.length() < 150) {
		force = 3 * force.getNormalized();		//Anziehungskraft des Attraktors auf die Partikel

		vel += force;							//Bewegung zum Attraktor
		vel = mass * vel.getNormalized();
	}
	else if (force.length() < 500) {
		force = 7 * force.getNormalized();

		vel += force;
		vel = mass * vel.getNormalized();
	}
	else {
		force = 1 * force.getNormalized();
		vel += force;
		vel = mass * vel.getNormalized();
	}
	pos += (vel / 1.2 * deltaT);					//Position = m/s * s [Partikel bleiben statisch]
}

//--------------------------------------------------------------
void particle::doMovementOfHexagonOnTheTop(ofVec2f &attractor, float sceneSizeX, double deltaT)
{
	if (attractor.x + l >= sceneSizeX + 120) {
		particleLeftScene = true;
	}
	else {
		particleLeftScene = false;
	}
	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;			//Anziehungskraft						

	if (50 < force.length() < 150) {
		force = 60 * force.getNormalized();		//Anziehungskraft des Attraktors auf die Partikel

		vel += force;							//Bewegung zum Attraktor
		vel = mass * vel.getNormalized();
	}
	else {
		force = 60 * force.getNormalized();

		vel += force;
		vel = mass * vel.getNormalized();
	}
	pos += (vel / 1.5 * deltaT);				//Position = m/s * s [Partikel bleiben statisch]
}

//--------------------------------------------------------------
void particle::draw() {
	if (pos.x > 0 || pos.x < 300) {
		ofSetColor(this->color);
	}
	else {
		ofSetColor(255, 255, 255);
	}
	ofDrawCircle(pos, size);

}

//--------------------------------------------------------------
float particle::getAgeNorm() {
	return age / maxLife;
}

//--------------------------------------------------------------
float particle::deleteAfterLeavingSceneY() {
	return pos.y < 0 || pos.y > ofGetHeight();

}

//--------------------------------------------------------------
bool particle::deleteAfterLeavingSceneX() {
	return particleLeftScene;
}



