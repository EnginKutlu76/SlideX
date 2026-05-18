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
//	light.setAmbientColor(96, 96, 96);
//	light.setSpecularColor(128, 128, 128);
//	light.setDiffuseColor(192, 192, 192);
//	light.setPosition(5.0f, 5.0f, 0.0f);
	plane.setScale(5, 1, 50);

	plane.setPosition(
		cam.getPosX(),
		cam.getPosY(),
		cam.getPosZ() - 5
	);
	player.setPosition(0, 2, 40);
//	diffusemap.loadTexture("crate_diffuse.png");
//	specularmap.loadTexture("crate_specular.png");
//	material.setDiffuseMap(&diffusemap);
//	material.setSpecularMap(&specularmap);
//	cube.setMaterial(&material);
	cam.dolly(60.0f);
	cam.boom(10.0f);
	keystate = KEY_NONE;
}

void gCanvas::update() {
	moveCharacter();
	gLogi("camX") << cam.getPosX();
	gLogi("camY") << cam.getPosY();
	gLogi("camZ") << cam.getPosZ();
}

void gCanvas::draw() {
	setColor(255, 255, 255);
	cam.begin();
	enableDepthTest();
	light.enable();
	plane.draw();
	setColor(255, 0, 0);
	player.draw();
	light.disable();
	disableDepthTest();
	cam.end();
}

void gCanvas::moveCharacter() {

    if(keystate & KEY_A) {
    	player.pan(0.01f);
    }
    if(keystate & KEY_D) {
    	player.pan(-0.01f);
    }

    if(keystate & KEY_W) {
    	player.dolly(-5.01f);
    }

    if(keystate & KEY_S) {
    	player.dolly(5.01f);
    }


    if(keystate & KEY_E) {
    	player.boom(2.01f);
    }

    if(keystate & KEY_R) {
    	player.boom(-2.01f);
    }

    if(keystate & KEY_Z) {
    	player.tilt(-0.01f);
    }

    if(keystate & KEY_X) {
    	player.tilt(0.01f);
    }

}

void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
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

