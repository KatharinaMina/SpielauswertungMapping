#include "particle.h"

Particle::Particle() {

}

//--------------------------------------------------------------
Particle::~Particle() {

}

//--------------------------------------------------------------
void Particle::setup(ofVec2f pos, float maxAge) {
	//mode = newMode;
	this->pos = pos;										//Pointer to Position ofVec2f position
	vel.set(ofRandom(-20.0, 20.0), ofRandom(-90, -100));	//Movement direction

	age = 0.0;												//Age in the beginning 0
	maxLife = ofRandom(maxAge - 5, maxAge);					//Max life of a particle
	size = ofRandom(4.0, 0.01);
	mass = ofRandom(100, 250);								//Changes the particle velocity
	color.set(5, 241, 219);
	valueToMoveToTop = 0;									//Counter which causes the particle and the attractor to move to top
	valueToMoveToRight = 0;									//Counter which causes the particle and the attractor to move to right
	ticksToMoveParticlesToRight = 70;						//Framerate for movement velocity
	counterToMoveParticlesToRight = 0;						//Counter for delay on top
	particleLeftScene = false;								//Particle are out of ScenesizeX on the right side
}

//--------------------------------------------------------------
void Particle::updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool imageIsOnTop, bool tornadoIsFinished, int imageHeight, int imageWidth, float sceneSizeX, float sceneSizeY) {

	//Movement of particle in the different settings

	doMovementOfParticlesAtRain(tornadoIsFinished, deltaT, sceneSizeX);

	if (cloudAttractorIsSet == true) {
		doMovementOfParticlesAtRocketEffect(sceneSizeY, imageHeight, imageWidth, sceneSizeX, attractor, deltaT);
	}

	if (tornadoIsFinished == true && cloudAttractorIsSet == false) {
		doMovementOfParticlesAtSymbols(deltaT, attractor);
	}

	if (imageIsOnTop == true) {
		doMovementOfHexagonOnTheTop(attractor, sceneSizeX, deltaT);
	}

}

//--------------------------------------------------------------
void Particle::doMovementOfParticlesAtRain(bool tornadoIsFinished, double deltaT, float sceneSizeX)
{
	if (tornadoIsFinished == false) {				//Movement of partile from bottom to top
		pos += vel * deltaT;
		age += deltaT;

		if (pos.x >= sceneSizeX) {
			pos.x = ofRandom (-1,-5);				
		}
	}
}

//--------------------------------------------------------------
void Particle::doMovementOfParticlesAtSymbols(double deltaT, ofVec2f &attractor)
{
	valueToMoveToTop = 0;
	valueToMoveToRight = 0;
	counterToMoveParticlesToRight = 0;

	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;				//Attraction						

	if (50 < force.length() < 150) {				//Movement of the particle which is located at a radius of 50 to 150 around the attractor
		force = 10 * force.getNormalized();			

		vel += force;								//Movement to attractor
		vel = mass * vel.getNormalized();
	}
	else if (150 < force.length() < 500) {			//Movement of the particle which is located at a radius of 150 to 500 around the attractor
		force = 8 * force.getNormalized();

		vel += force;
		vel = mass * vel.getNormalized();
	}
	else {											//Movement of the particle which is located at a radius more than 500 around the attractor
		force = 2 * force.getNormalized();
		vel += force;
		vel = mass /1.2* vel.getNormalized();
	}
	pos += (vel / 1.5 * deltaT);					//Position = m/s * s [particle placed static]
}

//--------------------------------------------------------------
void Particle::doMovementOfParticlesAtRocketEffect(float sceneSizeY, int imageHeight, int imageWidth, float sceneSizeX, ofVec2f &attractor, double deltaT)
{
	int y = ((sceneSizeY / 2) + imageHeight);												//Beginning height for attractor
	int x = ofRandom(sceneSizeX / 2 - imageWidth / 2, sceneSizeX / 2 + imageWidth / 2);		//Width for attractor

	if (y - valueToMoveToTop - imageHeight > 200) {						//Increase counter depending on velocity for movement to top
		valueToMoveToTop += 3;											//Movement by 3 to top (pro Frame)
	}
	else if (y - valueToMoveToTop - imageHeight > 10) {					//Increase counter depending on velocity for movement to top
		valueToMoveToTop += 2;											//Movement by 3 to top (pro Frame)

	}

	else if (counterToMoveParticlesToRight < ticksToMoveParticlesToRight) {			//Delay on top 
		counterToMoveParticlesToRight++;											
	}
	else if (y - valueToMoveToTop - imageHeight <= 10) {				//Increase counter depending on velocity for movement to right( Movement by 3 to right (pro Frame))
		valueToMoveToRight += 3;
	}

	attractor.set(x + valueToMoveToRight, y - valueToMoveToTop);		


	age += deltaT;
	vel *= 0.1;
	ofVec2f force = (attractor - pos);				//Attraction					

	if (30 < force.length() < 150) {				//Movement of the particle which is located at a radius of 30 to 150 around the attractor
		force = 17 * force.getNormalized();			

		vel += force;								//Movement to attractor
		vel =( mass / 1.2) * vel.getNormalized();	//Particle don't pass the symbol
	}
	else if (150 < force.length() < 250) {			//Movement of the particle which is located at a radius of 150 to 250 around the attractor
		force = 14 * force.getNormalized();

		vel += force;
		vel = mass * 10 * vel.getNormalized();
	}
	else if (250 < force.length() < 500) {			//Movement of the particle which is located at a radius of 250 to 500 around the attractor
		force = 14 * force.getNormalized();

		vel += force;
		vel = mass * 4* vel.getNormalized();
	}
	else {											//Movement of the particle which is located at a radius more than 500 around the attractor
		force = 20 * force.getNormalized();
		vel += force;
		vel = mass * vel.getNormalized();
	}
	pos += (vel / 1.7 * deltaT);					//Position = m/s * s [particle placed static]
}

//--------------------------------------------------------------
void Particle::doMovementOfHexagonOnTheTop(ofVec2f &attractor, float sceneSizeX, double deltaT)
{
	if (attractor.x + valueToMoveToRight >= sceneSizeX + 120) {
		particleLeftScene = true;
	}
	else {
		particleLeftScene = false;
	}
	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;			//Attraction						

	if (50 < force.length() < 150) {			//Movement of the particle which is located at a radius of 50 to 150 around the attractor
		force = 60 * force.getNormalized();		//Anziehungskraft des Attraktors auf die Partikel

		vel += force;							//Bewegung zum Attraktor
		vel = mass * vel.getNormalized();
	}
	else {										//Movement of the particle which is located at a radius of more than 150 around the attractor
		force = 100 * force.getNormalized();

		vel += force;
		vel = mass/2 * vel.getNormalized();
	}
	pos += (vel  * deltaT);						//Position = m/s * s [particle placed static] 
}

//--------------------------------------------------------------
void Particle::draw() {
	if (pos.x > 0 || pos.x < 300) {
		ofSetColor(this->color);				//To make particle turquoise
		 color.set(getAgeNorm() * 241,241/ getAgeNorm() ,219);		//Color (Disco) 
	}
	else {
		ofSetColor(255, 255, 255);

	}
	ofDrawCircle(pos, size);

}

//--------------------------------------------------------------
float Particle::getAgeNorm() {
	return age / maxLife;
}

//--------------------------------------------------------------
float Particle::deleteAfterLeavingSceneY() {
	return pos.y < 0 || pos.y > ofGetHeight();

}

//--------------------------------------------------------------
bool Particle::deleteAfterLeavingSceneX() {
	return particleLeftScene;
}

//------------------------------------------------------------------
void Particle::setMode(particleMode newMode) {
	mode = newMode;
}




