#include "imageParticleSystem.h"


imageParticleSystem::imageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageHex, string imageName) {


	this->imageToDraw = new drawableImage(imageName);
	this->imageHeight = imageToDraw->getHeight();

	this->sceneSizeX = sceneSizeX;
	this->sceneSizeY = sceneSizeY;

	this->fileImageHex = fileImageHex;

	setAttractorsFromHexagonFromPicture();
	maxParticle = 50;

	setSymbolAttractorIsSet(true);
	setCloudAttractorIsSet(false);

	imageReachedTopAndAttractorIsChanged = false;
}

void imageParticleSystem::updateParticleSystem() {

	double deltaT = ofGetLastFrameTime();
	time += deltaT;


	if ((cloudAttractorIsSet == false) && (particles.size() < picPix / 7)) {			//Ertsellen von Partiklen f�r Symbole
		int newPix = (picPix / 7) - particles.size();
		for (int i = 1; i <= newPix; i++) {											//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
			particles.push_back(new particle);

			int x = ofRandom(0, sceneSizeX);
			int y = ofRandom(0, sceneSizeY);

			particles.back()->setup(ofVec2f(x, y), 20);
		}
	}
	else if ((cloudAttractorIsSet == false) && (particles.size() > picPix / 7)) {			//L�schen von �bersch�ssigen Partikeln f�r Symboleelse if(system.size() > picPix / 7) {			//L�schen von �bersch�ssigen Partikeln f�r Symbole

		int newPix = (particles.size() - (picPix / 7));

		for (int i = 0; i < newPix; i++) {
			delete particles.at(0);													// l�schen des Partikel Obj.
			particles.erase(particles.begin());										//l�schen der des Pointer auf Partikel
		}
	}
	else if ((cloudAttractorIsSet == true) && (particles.size() > picPix / 7)) {			//L�schen von �bersch�ssigen Partikeln f�r Symboleelse if(system.size() > picPix / 7) {			//L�schen von �bersch�ssigen Partikeln f�r Symbole

		int newPix = (particles.size() - (picPix / 7));
		for (int i = 0; i < newPix; i++) {
			delete particles.at(0);													// l�schen des Partikel Obj.
			particles.erase(particles.begin());										//l�schen der des Pointer auf Partikel
		}
	}

	//----------------------------------------------------------//Updaten der Partikel (Bewegung)

												//Bewegung bei Symbolen
	for (int p = 0; p < particles.size(); p++) {
		if (p * 7 < attractors.size()) {
			if (cloudAttractorIsSet == true) {
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, true, imageHeight, sceneSizeX, sceneSizeY);

			}
			else if (symbolAttractorIsSet == true)
			{
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, true, imageHeight, sceneSizeX, sceneSizeY);					//Partikel werden an Symbol gezogen
			}
		}
	}


	if (this->imageToDraw->imageIsOnTop(sceneSizeY)) {

		setAttractorsFromHexagonFromPicture();
		cloudAttractorIsSet = false;
	}
}

void imageParticleSystem::changeAttractorImage(ofImage newAttractorImage) {
	attractors = pixelInVector(newAttractorImage);
}

void imageParticleSystem::setAttractorsFromHexagonFromPicture() {
	int picWidth = fileImageHex.getWidth();
	int picHeight = fileImageHex.getHeight();
	ofPixels pix;
	pix = fileImageHex.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + imageToDraw->getImagePosX(sceneSizeX), y + imageToDraw->getImagePosY(sceneSizeY));
			pxPos.push_back(vec);

			picPix++;
		}
	}
	attractors = pxPos;
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
	}
}



