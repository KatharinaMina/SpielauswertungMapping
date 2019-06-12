#include "imageParticleSystem.h"


imageParticleSystem::imageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageHex, string imageName) {
	this->imageToDraw = new drawableImage(imageName, sceneSizeX, sceneSizeY);
	this->imageHeight = imageToDraw->getHeight();
	this->imageWidth = imageToDraw->getWidth();

	this->sceneSizeX = sceneSizeX;
	this->sceneSizeY = sceneSizeY;

	this->fileImageHex = fileImageHex;

	setAttractorsFromHexagonFromPicture();
	maxParticle = 50;

	setSymbolAttractorIsSet(true);
	setCloudAttractorIsSet(false);
	ticksToMoveImageToTop = 200;
	counterToMoveImageToTop = 0;
	fileImageCloud.loadImage("Hexagon.png");

	imageReachedTopAndAttractorIsChanged = false;
}

//----------------------------------------------------------
void imageParticleSystem::updateParticleSystem() {

	double deltaT = ofGetLastFrameTime();
	time += deltaT;

	if ((cloudAttractorIsSet == false) && (particles.size() < picPix / 7) && (this->imageToDraw->imageIsOnTop(sceneSizeY) == false)) {		//Ertsellen von Partiklen für Symbole unten
		createParticlesForHexagonInSymbol();
	}
	else if ((cloudAttractorIsSet == false) && (particles.size() < picPix / 7) && (this->imageToDraw->imageIsOnTop(sceneSizeY))) {			//Ertsellen von Partiklen für Symbole in der Cloud
		createParticlesForHexagonInCloud();
	}
	else if ((cloudAttractorIsSet == false) && (particles.size() > picPix / 7)) {															//Löschen von Überschüssigen Partikeln für Hexagon unten

		deleteParticlesForHexagon();
	}
	else if ((cloudAttractorIsSet == true) && (particles.size() > picPix / 7)) {															//Löschen von Überschüssigen Partikeln für Raketeneffekt 

		//deleteParticlesForRocketEffect();
	}

	//Bewegungen
	for (int p = 0; p < particles.size(); p++) {
		if (p * 7 < attractors.size()) {
			if (cloudAttractorIsSet == true) {																											//Bewegung bei Raketeneffekt
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, this->imageToDraw->imageIsOnTop(sceneSizeY), true, imageHeight, imageWidth, sceneSizeX, sceneSizeY);
			}
			else if (symbolAttractorIsSet == true)																										//Bewegung bei Symbol unten
			{
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, this->imageToDraw->imageIsOnTop(sceneSizeY), true, imageHeight, imageWidth, sceneSizeX, sceneSizeY);					
				
				if (this->imageToDraw->imageIsOnTop(sceneSizeY))																						//löschen der Partikel nachdem diese rechts aus der ScenesizeX ausgetreten sind
				{
					deleteParticleAfterLeavingOntheRightAndCreateThemOnTheLeft(p);
				}
			}
		}
	}

	if (counterToMoveImageToTop < ticksToMoveImageToTop) {			//Pause (da pro Frame aufgerufen) bevor Symbol und Partikel zum Raketeneffekt übergehen
		counterToMoveImageToTop++;
		
	}
	else if (counterToMoveImageToTop == ticksToMoveImageToTop) {	//Symbol und Partikel geht in Raketeneffekt über
		changeAttractorImage(fileImageCloud);
		setCloudAttractorIsSet(true);
	}

	if (this->imageToDraw->imageIsOnTop(sceneSizeY)) {				//Symbol und Partikel sind an maximaler y-Position angekommen und Hexagon wird als Attraktor gesetzt
		setAttractorsFromHexagonFromPicture();
		cloudAttractorIsSet = false;
	}

}

//----------------------------------------------------------
void imageParticleSystem::createParticlesForHexagonInSymbol()
{
	int newPix = (picPix / 7) - particles.size();
	for (int i = 1; i <= newPix; i++) {											//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
		particles.push_back(new particle);

		int x = sceneSizeX / 2;
		int y = sceneSizeY;

		particles.back()->setup(ofVec2f(x, y), 20);
	}
}

//----------------------------------------------------------
void imageParticleSystem::createParticlesForHexagonInCloud()
{
	int newPix = (picPix / 7) - particles.size();
	for (int i = 1; i <= newPix; i++) {											//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
		particles.push_back(new particle);

		int x = sceneSizeX / 2;
		int y = imageToDraw->getImagePosY(sceneSizeY) + imageHeight;

		particles.back()->setup(ofVec2f(x, y), 20);
	}
}

//----------------------------------------------------------
void imageParticleSystem::deleteParticlesForRocketEffect()
{
	int newPix = (particles.size() - (picPix / 7));
	for (int i = 0; i < newPix; i++) {
		delete particles.at(0);													// löschen des Partikel Obj.
		particles.erase(particles.begin());										//löschen der des Pointer auf Partikel
	}
}

//----------------------------------------------------------
void imageParticleSystem::deleteParticlesForHexagon()
{
	int newPix = (particles.size() - (picPix / 7));

	for (int i = 0; i < newPix; i++) {
		delete particles.at(0);													//löschen des Partikel Obj.
		particles.erase(particles.begin());										//löschen der des Pointer auf Partikel
	}
}

//----------------------------------------------------------
void imageParticleSystem::deleteParticleAfterLeavingOntheRightAndCreateThemOnTheLeft(int p)
{
	bool particleToDelete = particles.at(p)->deleteAfterLeavingSceneX();

	if (particleToDelete) {

		delete particles.at(0);													//löschen des Partikel Obj.
		particles.erase(particles.begin());										//löschen der des Pointer auf Partikel

		//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
		particles.push_back(new particle);

		int x = -50;
		int y = imageToDraw->getHeight();

		particles.back()->setup(ofVec2f(x, y), 20);

	}
}

//----------------------------------------------------------
void imageParticleSystem::changeAttractorImage(ofImage newAttractorImage) {		//Attraktor wird von Cloud auf Hexagon gewechselt und umgekehrt
	attractors = pixelInVector(newAttractorImage);
}

//----------------------------------------------------------
void imageParticleSystem::setAttractorsFromHexagonFromPicture() {				//Hexagon wird als Attraktor gesetzt (Pixel von Hexagon werden in Attraktoren umgewandelt)
	int picWidth = fileImageHex.getWidth();
	int picHeight = fileImageHex.getHeight();
	ofPixels pix;
	pix = fileImageHex.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {									//i gibt an das wir jede vierte Information des Pixels verarbeiten (rgba)
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + imageToDraw->getImagePosX(sceneSizeX), y + imageToDraw->getImagePosY(sceneSizeY));		//holt sich Position des Symbols um Bewegung zu folgen
			pxPos.push_back(vec);

			picPix++;
		}
	}
	attractors = pxPos;
}

//----------------------------------------------------------
vector<ofVec2f> imageParticleSystem::pixelInVector(ofImage a) {			//Einlesen der farbigen Pixel eines Bildes und Umwandeln in Vektoren
	int picWidth = a.getWidth();
	int picHeight = a.getHeight();
	ofPixels pix;
	pix = a.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {							//i gibt an das wir jede vierte Information des Pixels verarbeiten (rgba)
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + ((sceneSizeX / 2) - picWidth / 2), y - ((sceneSizeY)-picHeight - 7));		//setzten der Position an ScenesizeY
			pxPos.push_back(vec);

			picPix++;
		}
	}
	return pxPos;
}

//----------------------------------------------------------
void imageParticleSystem::drawImageParticleSystem() {			//zeichnen der Bilder und der Partikel

	imageToDraw->updateImage(sceneSizeX, sceneSizeY);

	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->draw();
	}
}

//----------------------------------------------------------
void imageParticleSystem::setSymbolAttractorIsSet(bool value) {	

	imageToDraw->symbolAttractorIsSet = value;
	symbolAttractorIsSet = value;
}

//----------------------------------------------------------
void imageParticleSystem::setCloudAttractorIsSet(bool value) {

	imageToDraw->cloudAttractorIsSet = value;
	cloudAttractorIsSet = value;
}


