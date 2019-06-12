#include "images.h"

bool pastMiddle = true;
int r = 121;
int g = 205;
int b = 205;


images::images() {

}

//--------------------------------------------------------------

images::~images() {

}

//--------------------------------------------------------------

void images::setup() {

	fileImageHex.loadImage("Hexagon.png");
	fileImageUT.loadImage("PktUmweltTechnik.png");
	fileImageUW.loadImage("PktUmweltWissenschaft.png");
	fileImageAWU.loadImage("PktAlltagWissenschaftUmwelt.png");
	fileImageATU.loadImage("PktAlltagTechnikUmwelt.png");
	fileImageTU.loadImage("PktTechnikUmwelt.png");
	fileImageCloud.loadImage("Wolke.png");
	x = 0;
	y = 0;
	ticksToMovePictureToRight = 70;
	counterToMovePicctureToRight = 0;

}

//--------------------------------------------------------------

void images::draw() {

}

//--------------------------------------------------------------

void images::drawImageIntoScreen(float sceneSizeX, float sceneSizeY) {

}

//--------------------------------------------------------------

void images::updateImage(float sceneSizeX, float sceneSizeY) {
	ima = changeImageColor(fileImageHex, r, g, b);

	int maxYpositionForPicture = sceneSizeY - imageToDraw.getHeight() - 3;


	if (cloudAttractorIsSet) {
		doMovementOfSymbolsOfCloud(maxYpositionForPicture, sceneSizeX, sceneSizeY);
	}

	else if (symbolAttractorIsSet) {
		doPlacementOfSymbolInGameEvaluation(sceneSizeX, sceneSizeY);
	}
	else if (tornadoIsFinished == false) {
		y = 0;
		x = 0;
		counterToMovePicctureToRight = 0;
	}

}

//--------------------------------------------------------------
void images::doPlacementOfSymbolInGameEvaluation(float sceneSizeX, float sceneSizeY)
{
	y = 0;
	x = 0;
	counterToMovePicctureToRight = 0;
	imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));
}

//--------------------------------------------------------------
void images::doMovementOfSymbolsOfCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY)
{
	if (y <= maxYpositionForPicture) {
		y += 3;
	}
	else if (counterToMovePicctureToRight < ticksToMovePictureToRight) {
		counterToMovePicctureToRight++;
	}
	else {
		if (pastMiddle) {		// mittelpkt + x und x  wird immer hochgezählt bis zur Scenesize   
			x += 3;
			
		}
		else {					// mittelpkt - x  jetzt wird x wieder zu null
			x -= 3;
			
		}
	}

	if (pastMiddle && x >= sceneSizeX / 2 + imageToDraw.getWidth()) {
		pastMiddle = false;
	}

	if (!pastMiddle && x <= 0) {
		pastMiddle = true;
	}

	if (pastMiddle) {
		imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) + x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
		ima.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) + x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
	}
	else {
		imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) - x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
		ima.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) - x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
	}
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

//--------------------------------------------------------------
void images::keyReleased(int key) {

	switch (key) {
		//--------------------------------------------------// ab hier laden der unterschiedlichen Bilder
	case '1':												//Bild 1: UmweltTechnik
		imageToDraw = changeImageColor(fileImageUT, r, g, b);


		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '2':												//Bild 2: UmweltWissenschaft

		imageToDraw = changeImageColor(fileImageUW, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '3':												//Bild 3: AlltagTechnikUmwelt

		imageToDraw = changeImageColor(fileImageAWU, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '4':
		//attractorToDraw = changeImageColor(fileImageCloud, r, g, b);
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

float images::deleteAfterLeavingSceneY() {
	return pos.y < 0 || pos.y > ofGetHeight();

}
