#include "ofApp.h"
#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"

//--------------------------------------------------------------
void ofApp::setup() {

	currentImage = -1;
	ofDisableArbTex();
	ofBackground(0);

	//test image
	img.setUseTexture(false);
	if (!img.load("testcard.png"))
	{
		ofLogError("ofApp::setup") << "Could not load image!";
		return;
	}

	this->tex.enableMipmap();
	this->tex.loadData(img.getPixels());

	//scene properties
	sceneSize.set(1280, 800);
	area.set(0, 0, sceneSize.x, sceneSize.y);
	fbo.allocate(sceneSize.x, sceneSize.y, GL_RGBA);

	//clear fbo to make sure there's no scrap
	fbo.begin();
	ofClear(0);
	fbo.end();

	//load warp settings from file if present
//	this->warpController.loadSettings("settings.json");

	//if there is no file, generate warp
	if (this->warpController.getWarps().empty())
	{
		std::shared_ptr<ofxWarpBase> warp;

		warp = this->warpController.buildWarp<ofxWarpPerspective>();
		warp->setSize(sceneSize.x, sceneSize.y);
		warp->setEdges(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	editingWarp = false;

	//testing stuff
	ofSetCircleResolution(60);
	ofSetBackgroundColor(0, 0, 0);
	//ofSetFrameRate(60);



	fileImageHex.loadImage("Hexagon.png");
	fileImageCloud.loadImage("Wolke.png");

	rainIsActive = true;

	this->rainParticleSyst = new rainParticleSystem(sceneSize.x, sceneSize.y);

}

//--------------------------------------------------------------
void ofApp::update() {
	if (rainIsActive) {
		rainParticleSyst->updateParticleSystem();
	}
	else {
		for (int i = 0; i < imageParticleSystems.size(); i++) {
			imageParticleSystems.at(i)->updateParticleSystem();
		}
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	//save warp settings on exit
	this->warpController.saveSettings("settings.json");
}

//--------------------------------------------------------------
void ofApp::draw() {

	fbo.begin();
	ofClear(0, 0, 0);
	//draw stuff here

	//ofDrawRectangle(0, 0, 800, 800);
	//ofDrawCircle(sceneSize.x *.5, sceneSize.y * .5, 300);


	if (rainIsActive) {
		rainParticleSyst->drawRainParticleSystem();
	}
	else {
		for (int i = 0; i < imageParticleSystems.size(); i++) {
			imageParticleSystems.at(i)->drawImageParticleSystem();
		}
	}
	
	fbo.end();

	//do not draw past this point
	//draw warp
	warpController.getWarp(0)->begin();
	fbo.draw(0, 0);
    
	warpController.getWarp(0)->end();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	if (key == 'f')
	{
		ofToggleFullscreen();
	}

	if (key == 'e') {
		editingWarp = !editingWarp;
		warpController.getWarp(0)->setEditing(editingWarp);
	}

	switch (key) {
	case '4':
		imageParticleSystems.at(currentImage)->changeAttractorImage(fileImageCloud);
		rainIsActive = false;

		imageParticleSystems.at(currentImage)->setCloudAttractorIsSet(true);
		break;
	case '1':
		imageParticleSystems.push_back(new imageParticleSystem(sceneSize.x, sceneSize.y, fileImageHex, "PktUmweltTechnik.png"));
		rainIsActive = false;
		currentImage++;
		break;
	case '2':
		imageParticleSystems.push_back(new imageParticleSystem(sceneSize.x, sceneSize.y, fileImageHex, "PktAlltagTechnikUmwelt.png"));
		rainIsActive = false;
		currentImage++;
		break;

	case '3':
		imageParticleSystems.push_back(new imageParticleSystem(sceneSize.x, sceneSize.y, fileImageHex, "PktAlltagWissenschaftUmwelt.png"));
		rainIsActive = false;
		currentImage++;
		break;
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
