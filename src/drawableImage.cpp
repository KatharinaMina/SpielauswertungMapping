#include "drawableImage.h"
#include "images.h"

//--------------------------------------------------------------
drawableImage::drawableImage(string imageName, float sceneSizeX, float sceneSizeY) {
	redImageColor = 121;		//Farbe für Symbol
	greenImageColor = 205;
	blueImageColor = 205;


	pastMiddle = true;
	fileImageHex.loadImage("Hexagon.png");
	imageToDraw.loadImage(imageName);
	fileImageHex = changeImageColor(fileImageHex, redImageColor, greenImageColor, blueImageColor);
	imageToDraw = changeImageColor(imageToDraw, redImageColor, greenImageColor, blueImageColor);
	x = ofRandom(1, 4);
	y = 0;
	ticksToMovePictureToRight = 70;
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
	y = 0;
	x = 0;
	counterToMovePictureToRight = 0;
	imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));
}

//--------------------------------------------------------------
void drawableImage::doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY)
{
	if (y <= maxYpositionForPicture) {
		y += 3;
	}
	else if (counterToMovePictureToRight < ticksToMovePictureToRight) {
		counterToMovePictureToRight++;
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


	imageToDraw.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));
	fileImageHex.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));
}

int drawableImage::setMaxHeightPosition(float sceneSizeY)
{
	for (float i = 0; i <= 4; i++) {
		newMaxHeight -= imageHeight / 2;
		maxHeightPositions.push_back(newMaxHeight);
	}
	int rgen = ofRandom(0, 4);
	return (int)maxHeightPositions.at(rgen);
}

//--------------------------------------------------------------
int drawableImage::getHeight() {
	return imageToDraw.getHeight();
}

int drawableImage::getMaxHeight() {
	return maxYpositionForPicture;
}

//--------------------------------------------------------------
bool drawableImage::imageIsOnTop(float sceneSizeY) {

	return y >= maxYpositionForPicture;
}

//--------------------------------------------------------------
float drawableImage::getImagePosX(float sceneSizeX) {
	if (pastMiddle)
		return (sceneSizeX / 2 - imageToDraw.getWidth() / 2) + x;
	else
		return (sceneSizeX / 2 - imageToDraw.getWidth() / 2) - x;
}

//--------------------------------------------------------------
float drawableImage::getImagePosY(float sceneSizeY) {
	return (sceneSizeY - imageToDraw.getHeight() - 5) - y;
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
