#include "imageParticleSystem.h"


ImageParticleSystem::ImageParticleSystem(int sceneSizeX, int sceneSizeY, ofImage fileImageHex, string imageName) {
	this->imageToDraw = new DrawableImage(imageName, sceneSizeX, sceneSizeY);
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
void ImageParticleSystem::updateParticleSystem() {

	double deltaT = ofGetLastFrameTime();
	time += deltaT;

	if ((cloudAttractorIsSet == false) && (particles.size() < picPix / 7) && (this->imageToDraw->imageIsOnTop(sceneSizeY) == false)) {		//Creating particles for symbol on bottom 
		createParticlesForHexagonInSymbol();
	}
	else if ((cloudAttractorIsSet == false) && (particles.size() < picPix / 7) && (this->imageToDraw->imageIsOnTop(sceneSizeY))) {			//Creating particles for symbol in cloud 
		createParticlesForHexagonInCloud();
	}
	else if ((cloudAttractorIsSet == false) && (particles.size() > picPix / 7)) {															//Deleting unused particles for hexagon on bottom

		deleteParticlesForHexagon();
	}
	else if ((cloudAttractorIsSet == true) && (particles.size() > picPix / 7)) {															//Deleting unused particles for rocketeffect 

		//deleteParticlesForRocketEffect();
	}

	//Movement
	for (int p = 0; p < particles.size(); p++) {
		if (p * 7 < attractors.size()) {
			if (cloudAttractorIsSet == true) {																											//Movement at rocketeffect
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, this->imageToDraw->imageIsOnTop(sceneSizeY), true, imageHeight, imageWidth, sceneSizeX, sceneSizeY);
			}
			else if (symbolAttractorIsSet == true)																										//Movement at Symbol at the bottom
			{
				particles.at(p)->updateParticle(deltaT, attractors[p * 7],
					cloudAttractorIsSet, this->imageToDraw->imageIsOnTop(sceneSizeY), true, imageHeight, imageWidth, sceneSizeX, sceneSizeY);

				if (this->imageToDraw->imageIsOnTop(sceneSizeY))																						//Deleting the particle after they left scene at right
				{
					deleteParticleAfterLeavingOntheRightAndCreateThemOnTheLeft(p);
				}
			}
		}
	}

	if (counterToMoveImageToTop < ticksToMoveImageToTop) {			//Delay (every Frame) before the symbol and particle pass to the rocket effect
		counterToMoveImageToTop++;

	}
	else if (counterToMoveImageToTop == ticksToMoveImageToTop) {	//Symbol and particles do over in rocketeffect
		changeAttractorImage(fileImageCloud);
		setCloudAttractorIsSet(true);
	}

	if (this->imageToDraw->imageIsOnTop(sceneSizeY)) {				//Symbol and particles reached max. y-position and attractor gets changed from rocketeffect to hexagon
		setAttractorsFromHexagonFromPicture();
		cloudAttractorIsSet = false;
	}

}

//----------------------------------------------------------
void ImageParticleSystem::createParticlesForHexagonInSymbol()
{
	int newPix = (picPix / 7) - particles.size();
	for (int i = 1; i <= newPix; i++) {											//Go through pixel  i = 1 (there is no pixel 0)
		particles.push_back(new Particle);

		int x = sceneSizeX / 2;
		int y = sceneSizeY;

		particles.back()->setup(ofVec2f(x, y), 20);
	}
}

//----------------------------------------------------------
void ImageParticleSystem::createParticlesForHexagonInCloud()
{
	int newPix = (picPix / 7) - particles.size();
	for (int i = 1; i <= newPix; i++) {											//Go through pixel  i = 1 (there is no pixel 0)
		particles.push_back(new Particle);

		int x = sceneSizeX / 2;
		int y = imageToDraw->getImagePosY(sceneSizeY) + imageHeight;

		particles.back()->setup(ofVec2f(x, y), 20);
	}
}

//----------------------------------------------------------
void ImageParticleSystem::deleteParticlesForRocketEffect()
{
	int newPix = (particles.size() - (picPix / 7));
	for (int i = 0; i < newPix; i++) {
		delete particles.at(0);													//Deleting particle object
		particles.erase(particles.begin());										//Deleting pointer to particle
	}
}

//----------------------------------------------------------
void ImageParticleSystem::deleteParticlesForHexagon()
{
	int newPix = (particles.size() - (picPix / 7));

	for (int i = 0; i < newPix; i++) {
		delete particles.at(0);													//Deleting particle object
		particles.erase(particles.begin());										//Deleting pointer to particle
	}
}

//----------------------------------------------------------
void ImageParticleSystem::deleteParticleAfterLeavingOntheRightAndCreateThemOnTheLeft(int p)
{
	bool particleToDelete = particles.at(p)->deleteAfterLeavingSceneX();

	if (particleToDelete) {

		delete particles.at(0);													//Deleting particle object
		particles.erase(particles.begin());										//Deleting pointer to particle

		//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
		particles.push_back(new Particle);

		int x = -50;
		int y = imageToDraw->getHeight();

		particles.back()->setup(ofVec2f(x, y), 20);

	}
}

//----------------------------------------------------------
void ImageParticleSystem::changeAttractorImage(ofImage newAttractorImage) {		//Attractor is changed between hexagon and cloud 
	attractors = pixelInVector(newAttractorImage);
}

//----------------------------------------------------------
void ImageParticleSystem::setAttractorsFromHexagonFromPicture() {				//Hexagon is attracot (pixel from hexagon get converted in attractors)
	int picWidth = fileImageHex.getWidth();
	int picHeight = fileImageHex.getHeight();
	ofPixels pix;
	pix = fileImageHex.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {									//i specifys that every fourth color information of the pixel is handled (rgba)
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + imageToDraw->getImagePosX(sceneSizeX), y + imageToDraw->getImagePosY(sceneSizeY));		//Gets position of image and so that the attractor follows movement
			pxPos.push_back(vec);

			picPix++;
		}
	}
	attractors = pxPos;
}

//----------------------------------------------------------
vector<ofVec2f> ImageParticleSystem::pixelInVector(ofImage a) {			//Read in all the coloured pixels of image and vonvert them in vectors
	int picWidth = a.getWidth();
	int picHeight = a.getHeight();
	ofPixels pix;
	pix = a.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {							//i specifys that every fourth color information of the pixel is handled (rgba)
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + ((sceneSizeX / 2) - picWidth / 2), y - ((sceneSizeY)-picHeight - 7));
			pxPos.push_back(vec);

			picPix++;
		}
	}
	return pxPos;
}

//----------------------------------------------------------
void ImageParticleSystem::drawImageParticleSystem() {			//Drawing of symbols and particles

	imageToDraw->updateImage(sceneSizeX, sceneSizeY);

	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->draw();
	}
}

//----------------------------------------------------------
void ImageParticleSystem::setSymbolAttractorIsSet(bool value) {

	imageToDraw->symbolAttractorIsSet = value;
	symbolAttractorIsSet = value;
}

//----------------------------------------------------------
void ImageParticleSystem::setCloudAttractorIsSet(bool value) {

	imageToDraw->cloudAttractorIsSet = value;
	cloudAttractorIsSet = value;
}


