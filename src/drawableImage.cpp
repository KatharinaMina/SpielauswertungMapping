#include "drawableImage.h"
#include "images.h"

//--------------------------------------------------------------
DrawableImage::DrawableImage(string imageName, float sceneSizeX, float sceneSizeY) {
	redImageColor = 121;		//Farbe für Symbol
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
DrawableImage::~DrawableImage() {

}


//--------------------------------------------------------------
void DrawableImage::updateImage(float sceneSizeX, float sceneSizeY) {

	if (cloudAttractorIsSet) {
		doMovementOfImageAtCloud(maxYpositionForPicture, sceneSizeX, sceneSizeY);
	}

	else if (symbolAttractorIsSet) {
		drawImage(sceneSizeX, sceneSizeY);
	}

}

//--------------------------------------------------------------
void DrawableImage::drawImage(float sceneSizeX, float sceneSizeY)
{
	yToMoveIntoCloud = 0;
	xToMoveInCloud = 0;
	counterToMovePictureToRight = 0;

	imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));		//unten Symbol
	fileImageHex.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));		//unten Hexagon
}

//--------------------------------------------------------------
void DrawableImage::doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY)
{
	if (yToMoveIntoCloud <= maxYpositionForPicture) {		//y-Bewegung zur Cloud 
		yToMoveIntoCloud += 3;
	}
	else if (counterToMovePictureToRight < ticksToMovePictureToRight) {
		counterToMovePictureToRight++;
	}
	else {													//x-Bewegung in Cloud 
		if (pastMiddle) {									//von der Mitte nach rechts: mittelpkt + x und x  wird immer hochgezählt bis zur Scenesize   
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

	imageToDraw.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));		//zeichnen des Symbols an neuer Position (für Bewegung des Symbols)
	fileImageHex.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));		//zeichnen des Hexagons an neuer Position (für Bewegung des Hexagons)

}



int DrawableImage::setMaxHeightPosition(float sceneSizeY)			// Array für maximale Y-Werte, damit Höhe der Hexagons zueinnadner passt und bei Wabenstruktur ineinander einhaken können
{
	for (float i = 0; i <= 4; i++) {								//setzten der gewünschten Werte
		newMaxHeight -= imageHeight / 2;
		maxHeightPositions.push_back(newMaxHeight);
	}
	int rgen = ofRandom(0, 4);										
	return (int)maxHeightPositions.at(rgen);						//random Arrayposition zur Auswahl von einer random y-Position
}

//--------------------------------------------------------------
bool DrawableImage::imageIsOnTop(float sceneSizeY) {			//schauen ob Symbol und Partikel in Cloud angelangt sind 

	return yToMoveIntoCloud >= maxYpositionForPicture;
}

//--------------------------------------------------------------
ofImage DrawableImage::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//Verarbeiten der Farbinformation der einzelnen Bildpixel 
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

	ofSetColor(255, 255, 255);																//setzten der allg. Farbe wieder auf weiß, um keine Beeinträchtigung bei neuer Farbsetztung zu erhalten

	imageToDraw.update();

	return imageToDraw;
}

//--------------------------------------------------------------
int DrawableImage::getHeight() {
	return imageToDraw.getHeight();
}

//--------------------------------------------------------------
int DrawableImage::getWidth() {
	return imageToDraw.getWidth();
}

//--------------------------------------------------------------
int DrawableImage::getMaxHeight() {
	return maxYpositionForPicture;
}

//--------------------------------------------------------------
float DrawableImage::getImagePosX(float sceneSizeX) {
	if (pastMiddle)
		return (sceneSizeX / 2 - imageToDraw.getWidth() / 2) + xToMoveInCloud;
	else
		return (sceneSizeX / 2 - imageToDraw.getWidth() / 2) - xToMoveInCloud;
}

//--------------------------------------------------------------
float DrawableImage::getImagePosY(float sceneSizeY) {
	return (sceneSizeY - imageToDraw.getHeight() - 5) - yToMoveIntoCloud;
}