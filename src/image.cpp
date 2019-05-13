#include "image.h"



int r = 121;		//Farbe für Symbol
int g = 205;
int b = 205;

image::image() {

}

//--------------------------------------------------------------

image::~image() {

}

//--------------------------------------------------------------

void image::setup(ofVec2f pos, float maxAge) {
	this->pos = pos;									//pointer auf Position ofVec2f position
	vel.set(ofRandom(-20.0, 20.0), ofRandom(90, 100));	//Die Bewegungsrichtung
	color.set(5, 241, 219);

	fileImage1.loadImage("Hexagon.png");
	fileImage2.loadImage("FINAL_Logo.png");
	fileImage3.loadImage("Danke_4070_2.png");
	fileImage4.loadImage("UmweltTechnik.png");
	fileImage5.loadImage("UmweltWissenschaft.png");
	fileImage6.loadImage("AlltagWissenschaftUmwelt.png");
	fileImage7.loadImage("AlltagTechnikUmwelt.png");
	fileImage8.loadImage("UmweltWissenschaft.png");
}

//--------------------------------------------------------------

void image::updateImage() {

}

//--------------------------------------------------------------

void image::draw() {
	ofSetColor(this->color);
}

//--------------------------------------------------------------

void image::drawImageIntoScreen(sceneSizeX, sceneSizeY) {
	if (symbolAttractorIsSet) {
		imageToDraw.draw((sceneSizeX / 4 - imageToDraw.getHeight() / 2), (sceneSizeY / 2 - imageToDraw.getHeight() / 2));
	}
	
}


//--------------------------------------------------------------
ofImage image::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//Einlesen der farbigen Pixel eines Bildes und Umwandeln in Vektoren

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


void image::keyReleased(int key) {

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
	case '5':												//Bild 3: AlltagTechnikUmwelt
	
		imageToDraw = changeImageColor(fileImage6, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	}
}

//--------------------------------------------------------------

float image::getAgeNorm() {
	return age / maxLife;
}

//--------------------------------------------------------------

float image::shallBeKilled() {
	return pos.y < 0 || pos.y > ofGetHeight();

}