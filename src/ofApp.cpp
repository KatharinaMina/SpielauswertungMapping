#include "ofApp.h"
#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"

images imgs;
//--------------------------------------------------------------
void ofApp::setup() {

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
	maxParticle = 50;
	birthCnt = 0;
	parAmount = 4;
	tornadoStartTime = -1000;
	time = 0;
	status = -1;
	imgs.setup();


	fileImage1.loadImage("Hexagon.png");
	fileImage9.loadImage("Wolke.png");

}

//--------------------------------------------------------------
void ofApp::update() {

	std::cout << picPix << endl;
	double deltaT = ofGetLastFrameTime();
	time += deltaT;

	//----------------------------------------------------------//Ertsellen bzw. Löschen von Partikeln
	if ((birthCnt >= 0) && (status == -1) && (tornadoIsFinished == false)) {		//Ertsellen von Partiklen für Tornado
		for (int i = 0; i < parAmount; i++) {
			system.push_back(new particle02);
			system.back()->setup(ofVec2f(ofRandom(0, sceneSize.x), 0), 20);
		}
		birthCnt = 0;
	}
	else if ((tornadoIsFinished == true) && (system.size() < picPix / 7)) {			//Ertsellen von Partiklen für Symbole
		int newPix = (picPix / 7) - system.size();
		for (int i = 1; i <= newPix; i++) {											//Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
			system.push_back(new particle02);

			int y = ofRandom(0, sceneSize.y);
			int x = ofRandom(0, sceneSize.x);

			system.back()->setup(ofVec2f(x, y), 20);
		}
	}
	else if ((tornadoIsFinished == true) && (cloudAttractorIsSet == false) && (system.size() > picPix / 7)) {			//Löschen von Überschüssigen Partikeln für Symboleelse if(system.size() > picPix / 7) {			//Löschen von Überschüssigen Partikeln für Symbole

		int newPix = (system.size() - (picPix / 7));

		for (int i = 0; i < newPix; i++) {
			delete system.at(0);													// löschen des Partikel Obj.
			system.erase(system.begin());										//löschen der des Pointer auf Partikel
		}
	}
	else if ((tornadoIsFinished == true) && (cloudAttractorIsSet == true) && (system.size() > picPix / 7)) {			//Löschen von Überschüssigen Partikeln für Symboleelse if(system.size() > picPix / 7) {			//Löschen von Überschüssigen Partikeln für Symbole

		int newPix = (system.size() - (picPix / 4));

		for (int i = 0; i < newPix; i++) {
			delete system.at(0);													// löschen des Partikel Obj.
			system.erase(system.begin());										//löschen der des Pointer auf Partikel
		}
	}

	//----------------------------------------------------------//Updaten der Partikel (Bewegung)

	if (tornadoIsFinished == true) {												//Bewegung bei Symbolen
		for (int p = 0; p < system.size();) {
			if (p * 7 < attractors.size()) {
				if (cloudAttractorIsSet == true) {
					system.at(p)->updateParticle(deltaT, attractors[p * 7],
						cloudAttractorIsSet, tornadoIsFinished, sceneSize.x, sceneSize.y);
				}
				else if (symbolAttractorIsSet == false) {
					system.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(0, sceneSize.x), ofRandom(0, ofGetHeight())),
						cloudAttractorIsSet, tornadoIsFinished, sceneSize.x, sceneSize.y);					//Partikel werden an beliebige Stelle gezogen				
				}
				else if (symbolAttractorIsSet == true)
				{
					system.at(p)->updateParticle(deltaT, attractors[p * 7],
						cloudAttractorIsSet, tornadoIsFinished, sceneSize.x, sceneSize.y);					//Partikel werden an Symbol gezogen
				}
			}
			else {
				system.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(0, sceneSize.x), ofRandom(0, ofGetHeight())),
					cloudAttractorIsSet, tornadoIsFinished, sceneSize.x, sceneSize.y);						//Partikel werden an beliebige Stelle gezogen
			}
			p++;
		}
	}
	else {																			//Bewegung bei Tornado
		for (int p = 0; p < system.size(); p++) {
			particle02* partikel = system.at(p);

			partikel->updateParticle(deltaT, ofVec2f(ofRandom(0, sceneSize.x), ofRandom(0, ofGetHeight())), cloudAttractorIsSet, tornadoIsFinished, sceneSize.x, sceneSize.y);

			if (system.at(p)->shallBeKilled()) {									//Beim austreten rechts werden die Partikel gelöscht
				delete system.at(p);												//und links wieder erstellt
				system.erase(system.begin() + p);
				p--;
			}
		}
		updateTornado();

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

	//drawImage = fileImage1;
	
	imgs.updateImage(sceneSize.x, sceneSize.y);

	for (int i = 0; i < system.size(); i++) {
		system.at(i)->draw();
	}

	fbo.end();

	//do not draw past this point
	//draw warp
	warpController.getWarp(0)->begin();
	fbo.draw(0, 0);
	warpController.getWarp(0)->end();
}


//--------------------------------------------------------------

vector<ofVec2f> ofApp::pixelInVector(ofImage a) {			//Einlesen der farbigen Pixel eines Bildes und Umwandeln in Vektoren
	int picWidth = a.getWidth();
	int picHeight = a.getHeight();
	ofPixels pix;
	pix = a.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;

			vec.set(x + ((sceneSize.x / 2) - picWidth / 2.5), y + ((sceneSize.y / 2) - picHeight / 2));
			pxPos.push_back(vec);

			picPix++;
		}
	}
	return pxPos;
}

//--------------------------------------------------------------
void ofApp::startTornado() {
	status = 0;
	tornadoStartTime = time;
	for (int p = 0; p < system.size(); p++) {
		particle02* partikel = system.at(p);
		partikel->startTornado();
	}

}

//--------------------------------------------------------------
void ofApp::updateTornado() {
	switch (status) {
	case 0:															//Status 0: Partikel wandern zur Grenze
		if ((time - tornadoStartTime) > 1.9) {
			status = 1;
			for (int p = 0; p < system.size(); p++) {
				particle02* partikel = system.at(p);
				partikel->startStage1();
			}
		}
		break;
	case 1:															//Status 1: Tornado wandert nach Oben 
		if ((time - tornadoStartTime) > 20) {
			status = -1;											//Status -1: Es "schneit"
		}
		for (int p = 0; p < system.size(); p++) {
			particle02* partikel = system.at(p);
			partikel->updateStage1();
		}
		break;
	}
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
	case ' ':												//Löschen von Partikel
		for (int p = 0; p < system.size();) {
			//schauen ob maxAge erreicht
			delete system.at(p);						//Löschen des Partikel Obj.
			system.erase(system.begin() + p);			//Löschen des Pointer auf Partikel

			p++;
		}
		maxParticle = 0;									//damit keine neuen Partikel durch die update-Methode ersellt werden
		break;
	case '5':												//Tornado
		startTornado();
		tornadoIsFinished = false;
		break;
	case '4':
		attractors = pixelInVector(fileImage9);
		cloudAttractorIsSet = true;
		tornadoIsFinished = true;
		break;
	case '1':
	case '2':
	case '3':

		attractors = pixelInVector(fileImage1);
		symbolAttractorIsSet = true;
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;

		break;
	}
	imgs.keyReleased(key);
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
