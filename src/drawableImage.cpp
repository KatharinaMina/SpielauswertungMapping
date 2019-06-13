#include "drawableImage.h"
#include "images.h"

//--------------------------------------------------------------
drawableImage::drawableImage(string imageName, float sceneSizeX, float sceneSizeY) {
	redImageColor = 121;		//Farbe f�r Symbol
	greenImageColor = 205;
	blueImageColor = 205;

	pastMiddle = true;
	fileImageHex.loadImage("Hexagon.png");
	imageToDraw.loadImage(imageName);
	fileImageHex = changeImageColor(fileImageHex, redImageColor, greenImageColor, blueImageColor);
	imageToDraw = changeImageColor(imageToDraw, redImageColor, greenImageColor, blueImageColor);
	xToMoveInCloud = ofRandom(1, 4);
	yToMoveIntoCloud = 0;
	ticksToMovePictureToRight = 150;
	counterToMovePictureToRight = 0;
	newMaxHeight = sceneSizeY - imageToDraw.getHeight() - 3;
	imageHeight = imageToDraw.getHeight();
	maxYpositionForPicture = setMaxHeightPosition(sceneSizeY);
}

//--------------------------------------------------------------
drawableImage::~drawableImage() {

}


//--------------------------------------------------------------
void drawableImage::updateImage(float sceneSizeX, float sceneSizeY) {

	if (cloudAttractorIsSet) {
		doMovementOfImageAtCloud(maxYpositionForPicture, sceneSizeX, sceneSizeY);
	}

	else if (symbolAttractorIsSet) {
		drawImage(sceneSizeX, sceneSizeY);
	}

}

//--------------------------------------------------------------
void drawableImage::drawImage(float sceneSizeX, float sceneSizeY)
{
	yToMoveIntoCloud = 0;
	xToMoveInCloud = 0;
	counterToMovePictureToRight = 0;

	imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));		//unten Symbol
	fileImageHex.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));		//unten Hexagon
}

//--------------------------------------------------------------
void drawableImage::doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY)
{
	if (yToMoveIntoCloud <= maxYpositionForPicture) {		//y-Bewegung zur Cloud 
		yToMoveIntoCloud += 3;
	}
	else if (counterToMovePictureToRight < ticksToMovePictureToRight) {
		counterToMovePictureToRight++;
	}
	else {													//x-Bewegung in Cloud 
		if (pastMiddle) {									//von der Mitte nach rechts: mittelpkt + x und x  wird immer hochgez�hlt bis zur Scenesize   
			xToMoveInCloud += 3;

		}
		else {												//von links in die Mitte: mittelpkt - x  jetzt wird x wieder zu null
			xToMoveInCloud -= 3;
		}
	}

	if (pastMiddle && xToMoveInCloud >= sceneSizeX / 2 + imageToDraw.getWidth()) {		//links von Mitte
		pastMiddle = false;
	}

	if (!pastMiddle && xToMoveInCloud <= 0) {											//rechts von Mitte
		pastMiddle = true;
	}

	imageToDraw.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));		//zeichnen des Symbols an neuer Position (f�r Bewegung des Symbols)
	fileImageHex.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));		//zeichnen des Hexagons an neuer Position (f�r Bewegung des Hexagons)

}



int drawableImage::setMaxHeightPosition(float sceneSizeY)			// Array f�r maximale Y-Werte, damit H�he der Hexagons zueinnadner passt und bei Wabenstruktur ineinander einhaken k�nnen
{
	for (float i = 0; i <= 4; i++) {								//setzten der gew�nschten Werte
		newMaxHeight -= imageHeight / 2;
		maxHeightPositions.push_back(newMaxHeight);
	}
	int rgen = ofRandom(0, 4);										
	return (int)maxHeightPositions.at(rgen);						//random Arrayposition zur Auswahl von einer random y-Position
}

//--------------------------------------------------------------
bool drawableImage::imageIsOnTop(float sceneSizeY) {			//schauen ob Symbol und Partikel in Cloud angelangt sind 

	return yToMoveIntoCloud >= maxYpositionForPicture;
}

//--------------------------------------------------------------
ofImage drawableImage::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//Verarbeiten der Farbinformation der einzelnen Bildpixel 
	int threshold = 1;

	int picWidth = imageToDraw.getWidth();
	int picHeight = imageToDraw.getHeight();


	for (int x = 0; x < picWidth; x++) {													//durchlaufen aller Pixel und setzten der neuen rgb-Werte
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

	ofSetColor(255, 255, 255);																//setzten der allg. Farbe wieder auf wei�, um keine Beeintr�chtigung bei neuer Farbsetztung zu erhalten

	imageToDraw.update();

	return imageToDraw;
}

//--------------------------------------------------------------
int drawableImage::getHeight() {
	return imageToDraw.getHeight();
}

//--------------------------------------------------------------
int drawableImage::getWidth() {
	return imageToDraw.getWidth();
}

//--------------------------------------------------------------
int drawableImage::getMaxHeight() {
	return maxYpositionForPicture;
}

//--------------------------------------------------------------
float drawableImage::getImagePosX(float sceneSizeX) {
	if (pastMiddle)
		return (sceneSizeX / 2 - imageToDraw.getWidth() / 2) + xToMoveInCloud;
	else
		return (sceneSizeX / 2 - imageToDraw.getWidth() / 2) - xToMoveInCloud;
}

//--------------------------------------------------------------
float drawableImage::getImagePosY(float sceneSizeY) {
	return (sceneSizeY - imageToDraw.getHeight() - 5) - yToMoveIntoCloud;
}