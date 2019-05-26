#include "imageParticleSystem.h"


imageParticleSystem::imageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageForAttractors, string imageName) {


	this->imageToDraw = new drawableImage(imageName);
	this->imageHeight = imageToDraw->getHeight();

	this->sceneSizeX = sceneSizeX;
	this->sceneSizeY = sceneSizeY;

	attractors = pixelInVector(fileImageForAttractors);
	maxParticle = 50;
	//birthCnt = 0;
	//parAmount = 4;
	//tornadoStartTime = -1000;
	//time = 0;
	//status = -1;

	setSymbolAttractorIsSet(true);
	setCloudAttractorIsSet(false);
}

void imageParticleSystem::updateParticleSystem() {

	double deltaT = ofGetLastFrameTime();
	time += deltaT;


	if ((cloudAttractorIsSet == false) && (particles.size() < picPix / 7)) {			//Ertsellen von Partiklen für Symbole
		int newPix = (picPix / 7) - particles.size();
		for (int i = 1; i <= newPix; i++) {											//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
			particles.push_back(new particle);

			int y = ofRandom(0, sceneSizeY);
			int x = ofRandom(0, sceneSizeX / 2);
			int y2 = ofRandom(0, sceneSizeY);
			int x2 = ofRandom(sceneSizeX / 2, sceneSizeX);

			particles.back()->setup(ofVec2f(x, y), ofVec2f(x2, y2), 20);
		}
	}
	else if ((cloudAttractorIsSet == false) && (particles.size() > picPix / 7)) {			//Löschen von Überschüssigen Partikeln für Symboleelse if(system.size() > picPix / 7) {			//Löschen von Überschüssigen Partikeln für Symbole

		int newPix = (particles.size() - (picPix / 7));

		for (int i = 0; i < newPix; i++) {
			delete particles.at(0);													// löschen des Partikel Obj.
			particles.erase(particles.begin());										//löschen der des Pointer auf Partikel
		}
	}
	else if ((cloudAttractorIsSet == true) && (particles.size() > picPix / 7)) {			//Löschen von Überschüssigen Partikeln für Symboleelse if(system.size() > picPix / 7) {			//Löschen von Überschüssigen Partikeln für Symbole

		int newPix = (particles.size() - (picPix / 4));
		for (int i = 0; i < newPix; i++) {
			delete particles.at(0);													// löschen des Partikel Obj.
			particles.erase(particles.begin());										//löschen der des Pointer auf Partikel
		}
	}

	//----------------------------------------------------------//Updaten der Partikel (Bewegung)

												//Bewegung bei Symbolen
	for (int p = 0; p < particles.size();) {
		if (p * 7 < attractors.size()) {
			if (cloudAttractorIsSet == true) {
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, true, imageHeight, sceneSizeX, sceneSizeY);

				bool particleToDelete = particles.at(p)->deleteAfterLeavingSceneX();
				if (particleToDelete) {
					delete particles.at(0);													// löschen des Partikel Obj.
					particles.erase(particles.begin());
				}
			}
			else if (symbolAttractorIsSet == true)
			{
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, true, imageHeight, sceneSizeX, sceneSizeY);					//Partikel werden an Symbol gezogen
			}
		}
		p++;
	}
}

void imageParticleSystem::changeAttractorImage(ofImage newAttractorImage) {
	attractors = pixelInVector(newAttractorImage);
}

vector<ofVec2f> imageParticleSystem::pixelInVector(ofImage a) {			//Einlesen der farbigen Pixel eines Bildes und Umwandeln in Vektoren
	int picWidth = a.getWidth();
	int picHeight = a.getHeight();
	ofPixels pix;
	pix = a.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + ((sceneSizeX / 2) - picWidth / 2), y + ((sceneSizeY) - picHeight - 5));
			pxPos.push_back(vec);

			picPix++;
		}
	}
	return pxPos;
}

void imageParticleSystem::setSymbolAttractorIsSet(bool value) {
	
	imageToDraw->symbolAttractorIsSet = value;
	symbolAttractorIsSet = value;
}

void imageParticleSystem::setCloudAttractorIsSet(bool value) {
	
	imageToDraw->cloudAttractorIsSet = value;
	cloudAttractorIsSet = value;
}

void imageParticleSystem::drawImageParticleSystem() {
		
	imageToDraw->updateImage(sceneSizeX, sceneSizeY);
		
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->draw();
		particles.at(i)->draw2();
	}
}



