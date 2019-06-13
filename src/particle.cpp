#include "particle.h"

particle::particle() {

}

//--------------------------------------------------------------
particle::~particle() {

}

//--------------------------------------------------------------
void particle::setup(ofVec2f pos, float maxAge) {
	//mode = newMode;
	this->pos = pos;										//pointer auf Position ofVec2f position
	vel.set(ofRandom(-20.0, 20.0), ofRandom(-90, -100));	//Die Bewegungsrichtung

	age = 0.0;												//Alter ist am Anfang 0
	maxLife = ofRandom(maxAge - 5, maxAge);					//Wie lange der Partikel maximal leben soll
	size = ofRandom(4.0, 0.01);
	mass = ofRandom(100, 250);								//verändert die Partikelgeschwindigkeit
	color.set(5, 241, 219);
	valueToMoveToTop = 0;									//Counter der bewirkt, dass sich Partikel mit Attraktor nach oben bewegen
	valueToMoveToRight = 0;									//Counter der bewirkt, dass sich Partikel mit Attraktor nach rechts bewegen
	ticksToMoveParticlesToRight = 70;						//Framerate für Bewegungsgeschwindigkeit
	counterToMoveParticlesToRight = 0;						//Counter für Pause oben
	particleLeftScene = false;								//Partikel sind rechts außerhalb der ScenesizeX

	//tex.load("img/overlay.png");							//siehe Tobis Code Textur
}

//--------------------------------------------------------------
void particle::updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool imageIsOnTop, bool tornadoIsFinished, int imageHeight, int imageWidth, float sceneSizeX, float sceneSizeY) {

	//Bewegung der Partikel in den unterschiedlichen Einstellungen

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
void particle::doMovementOfParticlesAtRain(bool tornadoIsFinished, double deltaT, float sceneSizeX)
{
	if (tornadoIsFinished == false) {				//Bewegung des Partikels von unten nach oben
		pos += vel * deltaT;
		age += deltaT;

		if (pos.x >= sceneSizeX) {
			pos.x = ofRandom (-1,-5); //Random, damit beim Beginn keine gerade Linie entsteht
		}
	}
}

//--------------------------------------------------------------
void particle::doMovementOfParticlesAtSymbols(double deltaT, ofVec2f &attractor)
{
	valueToMoveToTop = 0;
	valueToMoveToRight = 0;
	counterToMoveParticlesToRight = 0;

	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;				//Anziehungskraft						

	if (50 < force.length() < 150) {				//Bewegung der Partikel in einem Radius von 50 bis 150 um den Attraktor befinden
		force = 10 * force.getNormalized();			//Anziehungskraft des Attraktors auf die Partikel

		vel += force;								//Bewegung zum Attraktor
		vel = mass * vel.getNormalized();
	}
	else if (150 < force.length() < 500) {			//Bewegung der Partikel in einem Radius von 150 bis 500 um den Attraktor befinden
		force = 8 * force.getNormalized();

		vel += force;
		vel = mass * vel.getNormalized();
	}
	else {											//Bewegung der Partikel in einem Radius von mehr als 500 um den Attraktor befinden
		force = 2 * force.getNormalized();
		vel += force;
		vel = mass /1.2* vel.getNormalized();
	}
	pos += (vel / 1.5 * deltaT);					//Position = m/s * s [Partikel bleiben statisch]
}

//--------------------------------------------------------------
void particle::doMovementOfParticlesAtRocketEffect(float sceneSizeY, int imageHeight, int imageWidth, float sceneSizeX, ofVec2f &attractor, double deltaT)
{
	int y = ((sceneSizeY / 2) + imageHeight);												//Anfangshöhe für Attraktor
	int x = ofRandom(sceneSizeX / 2 - imageWidth / 2, sceneSizeX / 2 + imageWidth / 2);		//Breite des Attraktors

	if (y - valueToMoveToTop - imageHeight > 200) {						//erhöhen des Counters je nach Geschwindigkeit zur Bewegung nach oben 
		valueToMoveToTop += 3;											//Bewegung um 3 nach oben (pro Frame)
	}
	else if (y - valueToMoveToTop - imageHeight > 10) {					//erhöhen des Counters je nach Geschwindigkeit zur Bewegung nach oben
		valueToMoveToTop += 2;											//Bewegung um 2 nach oben (pro Frame)

	}

	else if (counterToMoveParticlesToRight < ticksToMoveParticlesToRight) {			//Pause oben 
		counterToMoveParticlesToRight++;											
	}
	else if (y - valueToMoveToTop - imageHeight <= 10) {		//erhöhen des Counters je nach Geschwindigkeit zur Bewegung nach rechts (Bewegung um 3 nach rechts (pro Frame))
		valueToMoveToRight += 3;
	}

	attractor.set(x + valueToMoveToRight, y - valueToMoveToTop);		//setzten des Attraktors bei Bewegung mit angepassten Koordinaten


	age += deltaT;
	vel *= 0.1;
	ofVec2f force = (attractor - pos);				//Anziehungskraft						

	if (30 < force.length() < 150) {				//Bewegung der Partikel in einem Radius von 30 bis 150 um den Attraktor befinden
		force = 17 * force.getNormalized();			//Anziehungskraft des Attraktors auf die Partikel

		vel += force;								//Bewegung zum Attraktor
		vel =( mass / 1.2) * vel.getNormalized();		//Anpassung des Raketeneffekts, damit die Partikel nicht schneller nach oben gehen als das Symbol
	}
	else if (150 < force.length() < 250) {			//Bewegung der Partikel in einem Radius von 150 bis 500 um den Attraktor befinden
		force = 14 * force.getNormalized();

		vel += force;
		vel = mass * 10 * vel.getNormalized();
	}
	else if (250 < force.length() < 500) {			//Bewegung der Partikel in einem Radius von 150 bis 500 um den Attraktor befinden
		force = 14 * force.getNormalized();

		vel += force;
		vel = mass * 4* vel.getNormalized();
	}
	else {											//Bewegung der Partikel in einem Radius mehr als 500 um den Attraktor befinden
		force = 20 * force.getNormalized();
		vel += force;
		vel = mass * vel.getNormalized();
	}
	pos += (vel / 1.7 * deltaT);					//Position = m/s * s [Partikel bleiben statisch] // Kraft der Anziehung wenn die Symbole nach rechts gehen
}

//--------------------------------------------------------------
void particle::doMovementOfHexagonOnTheTop(ofVec2f &attractor, float sceneSizeX, double deltaT)
{
	if (attractor.x + valueToMoveToRight >= sceneSizeX + 120) {
		particleLeftScene = true;
	}
	else {
		particleLeftScene = false;
	}
	age += deltaT;
	vel *= 0.1;
	ofVec2f force = attractor - pos;			//Anziehungskraft						

	if (50 < force.length() < 150) {			//Bewegung der Partikel in einem Radius von 50 bis 150 um den Attraktor befinden
		force = 60 * force.getNormalized();		//Anziehungskraft des Attraktors auf die Partikel

		vel += force;							//Bewegung zum Attraktor
		vel = mass * vel.getNormalized();
	}
	else {										//Bewegung der Partikel in einem Radius von mehr als 150 um den Attraktor befinden
		force = 100 * force.getNormalized();

		vel += force;
		vel = mass/2 * vel.getNormalized();
	}
	pos += (vel  * deltaT);				//Position = m/s * s [Partikel bleiben statisch] //vel/1.5 weg, damit die am Hexagon bleiben
}

//--------------------------------------------------------------
void particle::draw() {
	if (pos.x > 0 || pos.x < 300) {
		ofSetColor(this->color);				//setzten der Partikel auf Türkis
		 color.set(getAgeNorm() * 241,241/ getAgeNorm() ,219);		//Farbeffekt (Disco) 
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

//------------------------------------------------------------------
void particle::setMode(particleMode newMode) {
	mode = newMode;
}




