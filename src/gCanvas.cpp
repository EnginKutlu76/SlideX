/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: Noyan Culum
*/


#include "gCanvas.h"


gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	plane.push_back(plane1);
	plane.push_back(plane1);
	plane[0].setScale(5, 1, 50);
	plane[1].setScale(5, 1, 520);

	plane[0].setPosition(
		cam.getPosX(),
		cam.getPosY(),
		cam.getPosZ() - 5
	);
	player.setPosition(0, 2, 40);
	cam.dolly(60.0f);
	cam.boom(10.0f);
	keystate = KEY_NONE;
	velocityy = 0.0f;
	gravity = -0.015f;
	isgrounded = false;

	light.setSpecularColor(8, 8, 8);
	light.setAmbientColor(40, 40, 40);
	light.setDiffuseColor(255, 255, 245);
	light.setPosition(0.0f, 50.0f, 20.0f);

	shadow.allocate(&light, &cam, 4096, 4096);

	shadow.setLightProjection(-20.0f, 20.0f, 20.0f, -20.0f, 0.01f, 60.0f);

	shadow.activate();

}

void gCanvas::update() {
	moveCharacter();
	velocityy += gravity;

	player.setPosition(
		player.getPosX(),
		player.getPosY() + velocityy,
		player.getPosZ() - 0.11f
	);

	if(player.getPosY() <= 2.0f) {
		player.setPosition(
			player.getPosX(),
			2.0f,
			player.getPosZ()
		);

		velocityy = 0.0f;
		isgrounded = true;
	}
	else {
		isgrounded = false;
	}

	if(isjumping) {
	    player.tilt(5.0f);

	    jumprotation += 5.0f;

	    if(jumprotation >= 90.0f) {
	        isjumping = false;
	    }
	}

	cam.setPosition(
		player.getPosX(),
		player.getPosY() + 8.0f,
		player.getPosZ() + 20.0f
	);

	cam.lookAt(glm::vec3(
		player.getPosX(),
		player.getPosY(),
		player.getPosZ()
	));
}

void gCanvas::draw() {
	setColor(255, 255, 255);
	shadow.enable();
	cam.begin();
	enableDepthTest();
	light.enable();
	plane[1].draw();
	setColor(255, 0, 0);
	player.draw();
	light.disable();
	disableDepthTest();
	cam.end();
	shadow.disable();
}

void gCanvas::moveCharacter() {

    if(keystate & KEY_A) {
    	player.pan(0.01f);
    }
    if(keystate & KEY_D) {
    	player.pan(-0.01f);
    }

 }

void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
	int pressedkey = KEY_NONE;
	switch(key) {
	case G_KEY_W:
		pressedkey = KEY_W;
		if(isgrounded) {
			velocityy = 0.35f;
			isjumping = true;
			jumprotation = 0.0f;
			isgrounded = false;
		}
		break;
	case G_KEY_S:
		pressedkey = KEY_S;
		break;
	case G_KEY_D:
		pressedkey = KEY_D;
		break;
	case G_KEY_A:
		pressedkey = KEY_A;
		break;
	}
	keystate |= pressedkey;
}

void gCanvas::keyReleased(int key) {
//	gLogi("gCanvas") << "keyReleased:" << key;
	int pressedkey = KEY_NONE;
	switch(key) {
		case G_KEY_W:
			pressedkey = KEY_W;
			break;
		case G_KEY_S:
			pressedkey = KEY_S;
			break;
		case G_KEY_D:
			pressedkey = KEY_D;
			break;
		case G_KEY_A:
			pressedkey = KEY_A;
			break;
		case G_KEY_E:
			pressedkey = KEY_E;
			break;
		case G_KEY_R:
			pressedkey = KEY_R;
			break;
		case G_KEY_Z:
			pressedkey = KEY_Z;
			break;
		case G_KEY_X:
			pressedkey = KEY_X;
			break;
		default:
			break;
	}
	keystate &= ~pressedkey;
}

void gCanvas::charPressed(unsigned int codepoint) {
//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
//	gLogi("gCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
//	gLogi("gCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseReleased" << ", button:" << button;
}

void gCanvas::mouseScrolled(int x, int y) {
//	gLogi("gCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseEntered() {

}

void gCanvas::mouseExited() {

}

void gCanvas::windowResized(int w, int h) {

}

void gCanvas::showNotify() {

}

void gCanvas::hideNotify() {

}

