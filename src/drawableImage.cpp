#include "drawableImage.h"
#include <iostream>

//--------------------------------------------------------------
DrawableImage::DrawableImage(string imageName, float sceneSizeX, float sceneSizeY) {
	//Color for symbol
	redImageColor = 121;
	greenImageColor = 205;
	blueImageColor = 205;
	pastMiddle = true;
	pastYMax = false;
	fileImageHex.loadImage("Hexagon.png");
	imageToDraw.loadImage(imageName);
	fileImageHex = changeImageColor(fileImageHex, redImageColor, greenImageColor, blueImageColor);
	imageToDraw = changeImageColor(imageToDraw, redImageColor, greenImageColor, blueImageColor);
	xToMoveInCloud = ofRandom(0, 9);
	yToMoveInCloud = ofRandom(0, 9);
	yToMoveIntoCloud = 0;
	ticksToMovePictureToRight = 150;
	counterToMovePictureToRight = 0;
	newMaxHeight = sceneSizeY - imageToDraw.getHeight() - 3;
	maxYInWave = sceneSizeY - imageToDraw.getHeight() - 3;
	imageHeight = imageToDraw.getHeight();
	maxYpositionForPicture = setMaxHeightPosition(sceneSizeY);
	newCloudVelX = setSpeedAtCloud(sceneSizeX);
	newCloudVelY = setYAtCloud(sceneSizeY);
	frameTime = 0.03;
	pastMaxYInWave = false;
	test = false;
	std::cout << "setMaxHeight: " + maxYpositionForPicture << endl;

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
	yToMoveInCloud = 0;
	counterToMovePictureToRight = 0;

	imageToDraw.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));		//Symbol at bottom
	fileImageHex.draw((sceneSizeX / 2 - imageToDraw.getWidth() / 2), (sceneSizeY - imageToDraw.getHeight() - 5));		//Hexagon at bottom

}

//--------------------------------------------------------------
void DrawableImage::doMovementOfImageAtCloud(int maxYpositionForPicture, float sceneSizeX, float sceneSizeY)
{
	test = false;
	if (yToMoveIntoCloud <= maxYpositionForPicture ){//&& !test) {		//y-Movement into cloud
		if (ofGetLastFrameTime() > frameTime) {

			yToMoveIntoCloud += (0.005*sceneSizeY) * 2;		//y-Movement *2, if the frameTime is over 0.03

		}
		else {
			yToMoveIntoCloud += 0.005*sceneSizeY;
		}
	}

	else if (counterToMovePictureToRight < ticksToMovePictureToRight) {
		counterToMovePictureToRight++;
	}
	else {
		//x-Movement in cloud
		test = true;

		if (pastMaxYInWave) {
			yToMoveIntoCloud += newCloudVelY;				//y up
		}
		else {
			yToMoveIntoCloud -= newCloudVelY;				//y down
		}


		if (pastMiddle) {									//from the middle to right: midpoint + x and x  gets increased til its Scenesize   
			xToMoveInCloud += newCloudVelX;
		}
		else {												//From left to the middle: midpoint - x  decreased til x is 0 again
			xToMoveInCloud -= newCloudVelX;
		}
	}


	if (pastMaxYInWave && yToMoveIntoCloud >= maxYInWave ) {
		pastMaxYInWave = false;
	}

	if (!pastMaxYInWave && yToMoveIntoCloud <= maxYInWave / 4) {
		pastMaxYInWave = true;
	}

	if (!pastMaxYInWave && yToMoveIntoCloud <= maxYpositionForPicture + 1){//&& test) {
		pastMaxYInWave = true;
	}

	if (pastMiddle && xToMoveInCloud >= sceneSizeX / 2 + imageToDraw.getWidth()) {		//Left position from middle
		pastMiddle = false;
	}

	if (!pastMiddle && xToMoveInCloud <= 0) {											//Right position from middle
		pastMiddle = true;
	}

	if (yToMoveIntoCloud >= maxYpositionForPicture) {									//new Y Position 
		pastYMax = true;
	}


	imageToDraw.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));
	fileImageHex.draw(getImagePosX(sceneSizeX), getImagePosY(sceneSizeY));

}



int DrawableImage::setMaxHeightPosition(float sceneSizeY)			// Array for max y-values (so that height of the hexagons fits together and can hook into one another in honeycomb structure)
{
	newMaxHeight -= imageHeight / 2;
	for (float i = 0; i <= 4; i++) {								//alculate the max y-values
		newMaxHeight -= imageHeight / 2;
		maxHeightPositions.push_back(newMaxHeight);
	}
	int rgen = ofRandom(0, 3);
	return (int)maxHeightPositions.at(rgen);						//random array position to choose random y-position
}


int DrawableImage::setSpeedAtCloud(float sceneSizeX) {
	for (int i = 0; i <= 10; i++) {										//number of different velocities in x dircetion
		newXToMoveInCloud = ofRandom(0.0015*sceneSizeX, 0.004 * sceneSizeX);
		cloudVelX.push_back(newXToMoveInCloud);
	}
	int rgen = ofRandom(0, 9);
	return (float)cloudVelX.at(rgen);
}


int DrawableImage::setYAtCloud(float sceneSizeY) {
	for (int i = 0; i <= 10; i++) {									//number of different velocities in y dircetion
		newYToMoveInCloud = ofRandom(0.0012*sceneSizeY, 0.0015 * sceneSizeY);
		cloudVelY.push_back(newYToMoveInCloud);
	}
	int rgen = ofRandom(1, 9);
	return (float)cloudVelY.at(rgen);
}

//--------------------------------------------------------------
bool DrawableImage::imageIsOnTop(float sceneSizeY) {			//see if symbol and particles reached cloud

	return yToMoveIntoCloud >= maxYpositionForPicture;
}

//--------------------------------------------------------------
ofImage DrawableImage::changeImageColor(ofImage imageToDraw, int r, int g, int b) {			//Processing the color information of the individual image pixels
	int threshold = 1;

	int picWidth = imageToDraw.getWidth();
	int picHeight = imageToDraw.getHeight();


	for (int x = 0; x < picWidth; x++) {													//go through all pixel and set new rgb-values
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

	ofSetColor(255, 255, 255);																//set color to white again so the colors don't distort themself 

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