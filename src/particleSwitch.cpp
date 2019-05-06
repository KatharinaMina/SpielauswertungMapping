#include "particleSwitch.h"

particle02::particle02() {
    
}

//--------------------------------------------------------------

particle02::~particle02() {
    
}

//--------------------------------------------------------------

void particle02::setup(ofVec2f pos, float maxAge) {
    
	this->pos = pos;									//pointer auf Position ofVec2f position
	vel.set(ofRandom(-20.0, 20.0), ofRandom(90, 100));	//Die Bewegungsrichtung

	age = 0.0;											//Alter ist am Anfang 0
	maxLife = ofRandom(maxAge - 5, maxAge);				//Wie lange der Partikel maximal leben soll
	size = ofRandom(2, 3);							//Unterschiedliche Partikelgröße
	mass = ofRandom(100, 200);							//verändert die Partikelgeschwindigkeit
	color.set(5, 241, 219);
    
}

//--------------------------------------------------------------

void particle02::updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool tornadoIsFinished, float sceneSizeX, float sceneSizeY) {
	//Fallender Partikel
	if (tornadoIsFinished == false) {
		pos += vel * deltaT;
		age += deltaT;

		if (pos.x >= sceneSizeX) {
			pos.x = 0;
		}
	}

//---------------------------------------------------------------
														//Bewegung bei Symbolen
	if (tornadoIsFinished == true) {
		age += deltaT;
		vel *= 0.1;
		ofVec2f force = attractor - pos;				//Anziehungskraft				
		

		if (50 < force.length() < 150) {
			force = 300 * force.getNormalized();		//force.length = Abstand (Partikel - Attraktor)
													//Anziehungskraft des Attraktors auf die Partikel
				
			vel += force;							//Bewegung zum Attraktor
			vel = mass * vel.getNormalized();		//bleiben sonst nicht an Attraktor kleben auch Bewegungsgeschwindigkeit hin zum Attraktor
		}
		else if (force.length() < 50) {
			force = 10 * force.getNormalized();		//force.length = Abstand (Partikel - Attraktor)
													//Anziehungskraft des Attraktors auf die Partikel

			vel += force;							//Bewegung zum Attraktor
			vel = mass * vel.getNormalized();		//bleiben sonst nicht an Attraktor kleben auch Bewegungsgeschwindigkeit hin zum Attraktor
		}
		else {
			force = 10 * force.getNormalized();
			vel += force;
			vel = mass * vel.getNormalized();
		}
		pos += (vel / 2 * deltaT);					//Position = m/s * s [Partikel bleiben statisch]
	}

		if (cloudAttractorIsSet == true) {				//Bewegung bei Wolke
			int y = ofRandom(30, sceneSizeY/8);
			int x = ofRandom(0, sceneSizeX);

			attractor.set(x, y);						//Attraktor wird neu gesetzt 
			ofVec2f force2 = attractor - pos;

			velocity2 += force2 / 500;  
			velocity2 = (mass / 40)* velocity2.getNormalized(); //Bewegungsgeschwindigkeit hin zum Attraktor
			pos += (velocity2) * 2;						//Position = m/s Partikel bleiben nicht statisch am Attraktor kleben		
		}

	

}

//--------------------------------------------------------------

void particle02::draw() {
    ofSetColor(this->color);
    ofDrawCircle(pos , size);    
}

//--------------------------------------------------------------

void particle02::startTornado() {
    int distance = pos.y - ofGetHeight()/3.5*3;
    vel.y = -distance/2;
}

//--------------------------------------------------------------

void particle02::startStage1() {
    vel.y = ofRandom(5, 15)*(-1);
}

//--------------------------------------------------------------

void particle02::updateStage1() {
    vel += ofVec2f(ofRandom(1.5,2.5), ofRandom(0.3, 0.35)*(-1));
    color.set(5, 241, 219);
}

//--------------------------------------------------------------

float particle02::getAgeNorm() {
    return age/maxLife;
}

//--------------------------------------------------------------

float particle02::shallBeKilled() {
    return pos.y < 0 || pos.y > ofGetHeight();
    
}