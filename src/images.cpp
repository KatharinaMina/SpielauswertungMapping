#include "images.h"

bool pastMiddle = true;
int r = 121;
int g = 205;
int b = 205;


Images::Images() {

}

//--------------------------------------------------------------

Images::~Images() {

}

//--------------------------------------------------------------

void Images::setup() {

	fileImageHex.loadImage("Hexagon.png");
	fileImageUT.loadImage("PktUmweltTechnik.png");
	fileImageUW.loadImage("PktUmweltWissenschaft.png");
	fileImageAWU.loadImage("PktAlltagWissenschaftUmwelt.png");
	fileImageAUT.loadImage("PktAlltagUmweltTechnik.png");
	fileImageTU.loadImage("PktTechnikUmwelt.png");
	fileImageCloud.loadImage("Wolke.png");
	x = 0;
	y = 0;
	ticksToMovePictureToRight = 70;
	counterToMovePicctureToRight = 0;

}

//--------------------------------------------------------------

void Images::draw() {
	
}

//--------------------------------------------------------------

void Images::drawImageIntoScreen(float sceneSizeX, float sceneSizeY) {

}

//--------------------------------------------------------------

void Images::updateImage(float sceneSizeX, float sceneSizeY) {
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
void Images::doPlacementOfSymbolInGameEvaluation(float sceneSizeX, float sceneSizeY)
{
	y = 0;
	x = 0;
	counterToMovePicctureToRight = 0;
	imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));
}

//--------------------------------------------------------------
void Images::doMovementOfSymbolsOfCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY)
{
	if (y <= maxYpositionForPicture) {
		y += 0.005*sceneSizeY;
	}
	else if (counterToMovePicctureToRight < ticksToMovePictureToRight) {
		counterToMovePicctureToRight++;
	}
	else {
		if (pastMiddle) {		// midpoint + x and x: increase x til its scenesize
			x += 0.005*sceneSizeX;
			y += 0.005*sceneSizeY;
			
		}
		else {					// midpoint - x: decrease x til its 0 again
			x -= 0.005*sceneSizeX;
			y += 0.005*sceneSizeY;
			
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
ofImage Images::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//loading all the pixel from picture and convert them into vectors

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
void Images::keyReleased(int key) {

	switch (key) {
		//--------------------------------------------------//load all the images 
	case '1':												//image 1: UmweltTechnik
		imageToDraw = changeImageColor(fileImageUT, r, g, b);


		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	case '2':												//image 4: AlltagUmweltTechnik

		imageToDraw = changeImageColor(fileImageAUT, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	
	case '3':												//image 3: AlltagWissenschaftUmwelt

		imageToDraw = changeImageColor(fileImageAWU, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	
	case '4':												//image 2: UmweltWissenschaft

		imageToDraw = changeImageColor(fileImageUW, r, g, b);

		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	
	}

}

//--------------------------------------------------------------

float Images::getAgeNorm() {
	return age / maxLife;
}

//--------------------------------------------------------------

float Images::deleteAfterLeavingSceneY() {
	return pos.y < 0 || pos.y > ofGetHeight();

}
