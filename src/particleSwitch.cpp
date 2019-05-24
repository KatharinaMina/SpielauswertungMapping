#include "particleSwitch.h"



particle02::particle02() {

}

//--------------------------------------------------------------

particle02::~particle02() {

}

//--------------------------------------------------------------

void particle02::setup(ofVec2f pos, ofVec2f pos2, float maxAge) {
	this->pos = pos;									//pointer auf Position ofVec2f position
    this->pos2 = pos2;
	vel.set(ofRandom(-20.0, 20.0), ofRandom(-90, -100));	//Die Bewegungsrichtung

	age = 0.0;											//Alter ist am Anfang 0
	maxLife = ofRandom(maxAge - 5, maxAge);				//Wie lange der Partikel maximal leben soll
	size = ofRandom(2, 3);								//Unterschiedliche Partikelgröße
	mass = ofRandom(100, 200);							//verändert die Partikelgeschwindigkeit
	color.set(5, 241, 219);
    color2.set(255,255,255);
    k = 0;
	l = 0;
	ticksToMoveParticlesToRight = 70;
	counterToMoveParticlesToRight = 0;
}

//--------------------------------------------------------------

void particle02::updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool tornadoIsFinished, int imageHeight, float sceneSizeX, float sceneSizeY) {
	//Fallender Partikel
    
    
	if (tornadoIsFinished == false) {
		pos += vel * deltaT;
        pos2 += vel * deltaT;
		age += deltaT;

		if (pos.x >= sceneSizeX) {
			pos.x = 0;
		}
        if (pos2.x >= sceneSizeX) {
            pos2.x = 0;
        }
	}

	//---------------------------------------------------------------
															//Bewegung bei Symbolen 
	if (cloudAttractorIsSet == true) {

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
		else if(counterToMoveParticlesToRight < ticksToMoveParticlesToRight){
			counterToMoveParticlesToRight++;
		}
		else if (y - k - imageHeight <= 10) {
			l += 3;
		}

		if (attractor.x + l >= sceneSizeX){
			particleLeftScene = true;
		}
		else {
			particleLeftScene = false;
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
       pos2 += (vel / 1.2 * deltaT);


	}

	if (tornadoIsFinished == true && cloudAttractorIsSet == false) {
		if (!cloudAttractorIsSet) {
			k = 0;
			l = 0;
			counterToMoveParticlesToRight = 0;
		}
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
		pos += (vel / 1.5 * deltaT);				//Position = m/s * s [Partikel bleiben statisch]
        pos2 += (vel / 1.5 * deltaT);
	}

}

//--------------------------------------------------------------

void particle02::draw() {
    if (pos.x > 0 || pos.x < 300){
        ofSetColor(this->color);
    } else{
        ofSetColor(255, 255, 255);
    }
    ofDrawCircle(pos, size);
	
    
}
void particle02::draw2(){
    ofSetColor(this->color2);
    ofDrawCircle(pos2, size);
}

//--------------------------------------------------------------

void particle02::startTornado() {
	int distance = pos.y - ofGetHeight() / 3.5 * 3;
    
	vel.y = -distance / 2;
}

//--------------------------------------------------------------

void particle02::startStage1() {
	vel.y = ofRandom(5, 15)*(-1);
}

//--------------------------------------------------------------

void particle02::updateStage1() {
	vel += ofVec2f(ofRandom(1.5, 2.5), ofRandom(0.3, 0.35)*(-1));
	color.set(5, 241, 219);
}

//--------------------------------------------------------------

float particle02::getAgeNorm() {
	return age / maxLife;
}

//--------------------------------------------------------------

float particle02::deleteAfterLeavingSceneY() {
	return pos.y < 0 || pos.y > ofGetHeight() || pos2.y < 0 || pos.y > ofGetHeight();

}

bool particle02::deleteAfterLeavingSceneX() {
	return particleLeftScene;
}



