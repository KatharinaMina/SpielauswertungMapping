#include "images.h"



int r = 121;		//Farbe für Symbol
int g = 205;
int b = 205;


images::images() {

}

//--------------------------------------------------------------

images::~images() {

}

//--------------------------------------------------------------

void images::setup() {
	//this->pos = pos;									//pointer auf Position ofVec2f position
	//vel.set(ofRandom(-20.0, 20.0), ofRandom(90, 100));	//Die Bewegungsrichtung
	//color.set(5, 241, 219);

	fileImage1.loadImage("Hexagon.png");
	fileImage2.loadImage("FINAL_Logo.png");
	fileImage3.loadImage("Danke_4070_2.png");
	fileImage4.loadImage("PktUmweltTechnik.png");
	fileImage5.loadImage("PktUmweltWissenschaft.png");
	fileImage6.loadImage("PktAlltagWissenschaftUmwelt.png");
	fileImage7.loadImage("PktAlltagTechnikUmwelt.png");
	fileImage8.loadImage("PktUmweltWissenschaft.png");
	fileImage9.loadImage("Wolke.png");

}

//--------------------------------------------------------------

void images::updateImage(float sceneSizeX, float sceneSizeY) {
	ima = changeImageColor(fileImage1, r, g, b);


	if (cloudAttractorIsSet) {
		if (y <= sceneSizeY / 2 - imageToDraw.getHeight() / 2) {

			//attractorToDraw.draw((sceneSizeX / 2 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2) - y);
			imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2) - y);

			ima.draw((sceneSizeX / 2 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2) - y);

			ofSetColor(0, 0, 0);
			ofDrawRectangle(sceneSizeX / 2 - 100, sceneSizeY / 3, 200, 200);
			ofSetColor(255, 255, 255);
			y += 3;
		}
		imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2) - y);
		ima.draw((sceneSizeX / 2 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2) - y);
	}
	else if (symbolAttractorIsSet) {
		y = 0;
		imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2));
	}
	else if (tornadoIsFinished == false) {
		y = 0;
	}

}

//--------------------------------------------------------------

void images::draw() {

}

//--------------------------------------------------------------

void images::drawImageIntoScreen(float sceneSizeX, float sceneSizeY) {

}


//--------------------------------------------------------------
ofImage images::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//Einlesen der farbigen Pixel eines Bildes und Umwandeln in Vektoren

	int threshold = 1;

	int picWidth = imageToDraw.getWidth();
	int picHeight = imageToDraw.getHeight();


	for (int x = 0; x < picWidth; x++) {
		for (int y = 0; y < picHeight; y++)
		{
			int index = (x + y * picWidth) * 4;

			if (imageToDraw.getPixelsRef()[index + 3] >= threshold) {
				imageToDraw.getPixelsRef()[index] = r;
				imageToDraw.getPixelsRef()[index + 1] = g;
				imageToDraw.getPixelsRef()[index + 2] = b;
			}
		}
	}

	ofSetColor(255, 255, 255);

	imageToDraw.update();

	return imageToDraw;
}


void images::keyReleased(int key) {

	switch (key) {
		//--------------------------------------------------// ab hier laden der unterschiedlichen Bilder
	case '1':												//Bild 1: UmweltTechnik
		imageToDraw = changeImageColor(fileImage4, r, g, b);


		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '2':												//Bild 2: UmweltWissenschaft

		imageToDraw = changeImageColor(fileImage5, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '3':												//Bild 3: AlltagTechnikUmwelt

		imageToDraw = changeImageColor(fileImage6, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '4':
		//attractorToDraw = changeImageColor(fileImage9, r, g, b);
		cloudAttractorIsSet = true;
		tornadoIsFinished = true;
		break;
	}

}

//--------------------------------------------------------------

float images::getAgeNorm() {
	return age / maxLife;
}

//--------------------------------------------------------------

float images::shallBeKilled() {
	return pos.y < 0 || pos.y > ofGetHeight();

}