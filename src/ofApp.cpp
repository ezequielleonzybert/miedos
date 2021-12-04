#include "ofApp.h"

#define RADS PI/180

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFullscreen(false);
	ofSetFrameRate(60);
	ofSetWindowShape(1024, 768);
	ofEnableAntiAliasing();
	ofEnableDepthTest();
	ofSetColor(200);
	light.enable();

	position.set(0, 0, 0);
	rotation.set(0, 0);
	cam.setPosition(0, 0, 0);

	// Initialize TVs
	int x[CANT], z[CANT];
	bool flag = false;

	for (int i = 0; i < CANT; i++) { // Avoid same coordinates for different TVs
		do {
			x[i] = rand() % 2500 - 1250;
			z[i] = rand() % 2500 - 1250;
			flag = false;
			for (int j = 0; j < i; j++) {
				if ((x[i] > x[j] - 300 && x[i] < x[j] + 300) && // if TVs overlapping
					(z[i] > z[j] - 300 && z[i] < z[j] + 300)) {
					flag = true;
					break;
				}
			}
		} while (flag);
	}

	for (int i = 0; i < CANT; i++) {
		tv[i].setup(x[i], rand() % 300 + 200, z[i], rand() % 100 + 100, ofRandomf(), true, i % 9);
	}

	for (int i = 0; i < 12; i++) {
		video[i].load("video" + to_string(i) + ".mp4");
		video[i].play();
	}

	// Initialize TV 2nd scenario
	tv2.setup(0, -300, -3500, 256, 0, false, -1);
	shadow.load("shadow.png");
}

//--------------------------------------------------------------
void ofApp::update(){

	rotAng++;

	// Show fps on window bar
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	// Calculate player position and rotation
	position.z += -(wsad[0] + wsad[1]) * cos(rotation.x*RADS);
	position.x += (wsad[0] + wsad[1]) * sin(rotation.x*RADS); 

	float alpha = (180 - rotation.x)*RADS;
	position.z += -(wsad[2] + wsad[3]) * sin(alpha);
	position.x += (wsad[2] + wsad[3]) * cos(alpha);

	cam.setPosition(position.x, position.y, position.z);
	cam.setOrientation(ofVec3f(rotation.y, -rotation.x, 0));

	// Mouse pressed instances to avoid draging click
	if (click) {
		clickCount++;
	}
	else clickCount = 0;

	// Update TVs
	if(onCount){ // scenario 1

		for (int i = 0; i < CANT; i++) {
			tv[i].update(cam, mouse, clickCount, onCount);
		}

		for (int i = 0; i < 12; i++) {
			video[i].update();
		}

	}
	else{ // scenario 2
		if (!transition) {
			transition = true;
			position.x = -1800;
			position.z = 0;
			rotation.x = 27;
			rotation.y = 0;
		}
		tv2.update(cam, mouse, clickCount, onCount);
		shadow.update();
		if (tv2.getTurnOn()) {
			position.x = 0;
			position.z = 0;
			tv2.setTurnOn(false, onCount);
			for (int i = 0; i < CANT; i++) {
				tv[i].setTurnOn(true, onCount);
			}
			transition = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (onCount && !transition) { // Scenario 1

		ofDisableLighting();
		ofBackgroundGradient(ofMap(onCount, 0, CANT, 100, 30), ofMap(onCount, 0, CANT, 100, 0));
		ofEnableLighting();

		cam.begin();

		// Draw TVs
		for (int i = 0; i < CANT; i++) {
			tv[i].draw(video);
		}

		// Draw floor
		ofRotateYDeg(90);
		ofRotateZDeg(90);
		ofTranslate(-300, 0, 0);

		light.disable();
		ofSetColor(0, 0, 0, (onCount * 30) + 10);
		ofDrawGridPlane(300, 100);
		light.enable();
		
		cam.end();
	}
	else { // Scenario 2

		ofBackground(255);

		cam.begin();

		tv2.draw(video);

		ofTranslate(0, -300-128, -3500);
		ofRotateXDeg(90);
		shadow.draw(-shadow.getWidth()/2, -shadow.getHeight()/2, 0);

		cam.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case 'w':
		wsad[0] = 10;
		break;
	case 's':
		wsad[1] = -10;
		break;
	case 'a':
		wsad[2] = 10;
		break;
	case 'd':
		wsad[3] = -10;
		break;
	case 'W':
		wsad[0] = 10;
		break;
	case 'S':
		wsad[1] = -10;
		break;
	case 'A':
		wsad[2] = 10;
		break;
	case 'D':
		wsad[3] = -10;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
	case 'w':
		wsad[0] = 0;
		break;
	case 's':
		wsad[1] = 0;
		break;
	case 'a':
		wsad[2] = 0;
		break;
	case 'd':
		wsad[3] = 0;
		break;
	case 'W':
		wsad[0] = 0;
		break;
	case 'S':
		wsad[1] = 0;
		break;
	case 'A':
		wsad[2] = 0;
		break;
	case 'D':
		wsad[3] = 0;
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	mouse.x = x;
	mouse.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	rotation.x += -(x - prevRot.x)*0.1;
	rotation.y += (y - prevRot.y)*0.1;

	prevRot.x = x;
	prevRot.y = y;

	mouse.x = x;
	mouse.y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	prevRot.x = x;
	prevRot.y = y;
	click = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	click = false;
}