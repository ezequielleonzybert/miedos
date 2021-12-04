#pragma once

#include "ofMain.h"
#include "tele.h"

// Number of floating TVs
const int CANT = 10;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	ofLight light;

	ofVec3f position;
	ofVec2f rotation;
	ofVec2f prevRot;

	tele tv[CANT];
	tele tv2;

	ofCamera cam;
	ofVec2f mouse;

	bool click = NULL;
	int clickCount = NULL;
	float rotAng = NULL;

	int wsad[4];

	ofVideoPlayer video[12];

	int onCount = CANT;
	bool transition = false;

	ofImage shadow;
};