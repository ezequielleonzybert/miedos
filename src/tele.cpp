#pragma once
#include "tele.h"

void tele::setup(float x, float y, float z, float size, float rotSpeed, bool on, int soundI) {
	position.set(x, y, z);
	this->size = size;
	this->rotAng = rotAng;
	this->rotSpeed = rotSpeed;
	this->turnOn = on;

	for (int i = 0; i < 6; i++) {
		random[i] = rand() % 12;
	}
	if (soundI != -1) {
		sound.load("audio" + to_string(soundI) + ".mp3");
		sound.setLoop(true);
		sound.setPaused(true);
		sound.play();
	}
}

void tele::update(ofCamera & cam, ofVec2f mouse, int & clickCount, int & onCount) {

	float margin = 50000 / distance; // TVs position point margin for clicking it
	ofVec3f posInScreen = cam.worldToScreen(position);

	if ((mouse.x > posInScreen.x - margin && mouse.x < posInScreen.x + margin &&
		mouse.y > posInScreen.y - margin && mouse.y < posInScreen.y + margin) &&
		distance < 1000)
	{
		color = 255;
		if (clickCount == 1) {
				turnOn = !turnOn;
				if (turnOn) {
					onCount++;
					sound.setPaused(false);
				}
				else { 
					onCount--; 
					sound.setPaused(true);
				}
		}
	}
	else { color = 200; }

	// Limited distance between TVs and player (for sound fade effect)

	ofVec3f camPos = cam.getPosition();
	distance = ofClamp(
		sqrt((camPos.x - position.x)*(camPos.x - position.x) +
		(camPos.y - position.y)*(camPos.y - position.y) +
			(camPos.z - position.z)*(camPos.z - position.z)), 0, 2000);

	sound.setVolume(ofMap(distance, 0, 2000, 1, 0));

	rotAng += rotSpeed;
}

void tele::draw(ofVideoPlayer *v) {

	// Draw TV Box structure

	ofSetColor(color);

	ofPushMatrix();

	ofTranslate(position.x, position.y, position.z);

	ofRotateYDeg(rotAng*rotSpeed);
	ofRotateZDeg(rotAng*rotSpeed / 2);

	ofDrawBox(0, size / 2.4, size / 2.4, size, size / 6, size / 6);
	ofDrawBox(0, -size / 2.4, size / 2.4, size, size / 6, size / 6);
	ofDrawBox(0, size / 2.4, -size / 2.4, size, size / 6, size / 6);
	ofDrawBox(0, -size / 2.4, -size / 2.4, size, size / 6, size / 6);

	ofRotateZDeg(90);

	ofDrawBox(0, size / 2.4, size / 2.4, size / 1.5, size / 6, size / 6);
	ofDrawBox(0, -size / 2.4, size / 2.4, size / 1.5, size / 6, size / 6);
	ofDrawBox(0, size / 2.4, -size / 2.4, size / 1.5, size / 6, size / 6);
	ofDrawBox(0, -size / 2.4, -size / 2.4, size / 1.5, size / 6, size / 6);

	ofRotateZDeg(-90);
	ofRotateYDeg(90);

	ofDrawBox(0, size / 2.4, size / 2.4, size / 1.5, size / 6, size / 6);
	ofDrawBox(0, size / 2.4, -size / 2.4, size / 1.5, size / 6, size / 6);
	ofDrawBox(0, -size / 2.4, size / 2.4, size / 1.5, size / 6, size / 6);
	ofDrawBox(0, -size / 2.4, -size / 2.4, size / 1.5, size / 6, size / 6);

	// Draw videos and sound
	if (turnOn) {
		float vSize = size / 1.5;
		float vDist = size / 2.2;

		ofDisableLighting();

		ofTranslate(0, 0, vDist);
		v[random[0]].draw(-vSize / 2, -vSize / 2, vSize, vSize);

		ofTranslate(0, 0, -2 * vDist);
		ofRotateYDeg(180);
		v[random[1]].draw(-vSize / 2, -vSize / 2, vSize, vSize);

		ofTranslate(vDist, 0, -vDist);
		ofRotateYDeg(90);
		v[random[2]].draw(-vSize / 2, -vSize / 2, vSize, vSize);

		ofTranslate(0, 0, -2 * vDist);
		ofRotateYDeg(180);
		v[random[3]].draw(-vSize / 2, -vSize / 2, vSize, vSize);

		ofTranslate(0, vDist, -vDist);
		ofRotateXDeg(90);
		v[random[4]].draw(-vSize / 2, -vSize / 2, vSize, vSize);

		ofTranslate(0, 0, 2 * vDist);
		ofRotateXDeg(180);
		v[random[5]].draw(-vSize / 2, -vSize / 2, vSize, vSize);

		ofEnableLighting();

		sound.setPaused(false);
	}
	else sound.setPaused(true);

	ofPopMatrix();
}

//-----------------GETTERS-------------------

ofVec3f tele::getPos() {
	return position;
}

bool tele::getTurnOn() {
	return turnOn;
}

int tele::getColor() {
	return color;
}

//------------------SETTERS-------------------

void tele::setTurnOn(bool turnOn, int & onCount) {
	this->turnOn = turnOn;
	if (turnOn) onCount++;
	else onCount--;
}

void tele::setColor(int color) {
	this->color = color;
}