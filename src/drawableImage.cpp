#include "drawableImage.h"



int r = 121;		//Farbe für Symbol
int g = 205;
int b = 205;

bool pastMiddle = true;



drawableImage::drawableImage(string imageName) {

	fileImageHex.loadImage("Hexagon.png");
	imageToDraw.loadImage(imageName);
	fileImageHex = changeImageColor(fileImageHex, r, g, b);
	imageToDraw = changeImageColor(imageToDraw, r, g, b);
	x = 0;
	y = 0;
	ticksToMovePictureToRight = 70;
	counterToMovePicctureToRight = 0;
}

//--------------------------------------------------------------

drawableImage::~drawableImage() {

}


//--------------------------------------------------------------

void drawableImage::updateImage(float sceneSizeX, float sceneSizeY) {
	
	int maxYpositionForPicture = sceneSizeY - imageToDraw.getHeight() - 3;


	if (cloudAttractorIsSet) {
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
			fileImageHex.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) + x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
		}
		else {
			imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) - x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
			fileImageHex.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2) - x, (sceneSizeY - imageToDraw.getHeight() - 5) - y);
		}


	}

	else if (symbolAttractorIsSet) {
		y = 0;
		x = 0;
		counterToMovePicctureToRight = 0;
		imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));
	}

}

int drawableImage::getHeight() {
	return imageToDraw.getHeight();
}

//--------------------------------------------------------------
ofImage drawableImage::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//Einlesen der farbigen Pixel eines Bildes und Umwandeln in Vektoren

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