#pragma once
#include "ofMain.h"

class tele {

public:

	void setup(float x, float y, float z, float size, float rotSpeed, bool on, int soundI);
	void update(ofCamera & cam, ofVec2f mouse, int & clickCount, int & onCount);

	void draw(ofVideoPlayer *v);

	void setTurnOn(bool turnOn, int & onCount);
	void setColor(int color);

	ofVec3f getPos();
	int getColor();
	bool getTurnOn();

	bool flagRel = true;
	bool flagDrag = false;
	int random[6];

private:

	bool turnOn = NULL;
	int color = NULL;
	ofVec3f position;
	float size;
	float rotAng;
	float rotSpeed;
	float distance;
	ofSoundPlayer sound;
	ofCamera cam;

};

