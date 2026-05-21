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
	gamestate = GAMESTATE_PLAY;
	resumepanelshown = false;
	resumepanel.loadImage("dialogue_pause.png");
	rpw = resumepanel.getWidth();
	rph = resumepanel.getHeight();
	rpx = (getWidth() - rpw) / 2.0f;
	rpy = (getHeight() - rph) / 2.0f;

	score = 0;
	scorex = (getWidth() - root->textfont.getStringWidth(gToStr(score))) / 2;
	scorey = root->textfont.getStringHeight(gToStr(score));

	speed = -0.40f;
	maxspeed = -3.0f;
	acceleration = -0.0002f;

	for(int i = 0; i < 8; i++) {
		plane.push_back(plane1);
	}

	for(int i = 0; i < plane.size(); i++) {

		plane[i].setScale(5, 1, 40);

		plane[i].setPosition(
			0,
			0,
			i * -81
		);
	}

	lastplanez = plane.back().getPosZ();

	player.setPosition(0, 2, 20);

	cam.boom(10.0f);

	keystate = KEY_NONE;

	velocityy = 0.0f;

	gravity = -0.015f;

	isgrounded = false;

	light.setDiffuseColor(255, 255, 245);

	light.setPosition(0.0f, 50.0f, 20.0f);

	linestate = LINE_MID;
	linelocation = 0;
	isjumping = false;
	fpsSetup();
	lastPlayerZ = player.getPosZ();
	scoreFloat = 0.0f;
}

void gCanvas::update() {

	moveCharacter();

	velocityy += gravity;
	if(speed > maxspeed) speed += acceleration;

	player.setPosition(
		linelocation,
		player.getPosY() + velocityy,
		player.getPosZ() + speed
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

		player.tilt(6.0f);

		jumprotation += 6.0f;

		if(jumprotation >= 90.0f) {
			isjumping = false;
		}
	}

	for(int i = 0; i < plane.size(); i++) {

		if(plane[i].getPosZ() > player.getPosZ() + 40) {

			lastplanez -= 81;

			plane[i].setPosition(
				plane[i].getPosX(),
				plane[i].getPosY(),
				lastplanez
			);
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

	light.setPosition(player.getPosX(), player.getPosY() + 200, player.getPosZ() + 30);

	float dz = lastPlayerZ - player.getPosZ();

	if (dz > 0)
	    scoreFloat += dz * 0.1f;

	lastPlayerZ = player.getPosZ();

	score = (int)scoreFloat;
}

void gCanvas::draw() {

	setColor(255, 255, 255);

	cam.begin();

	enableDepthTest();

	light.enable();

	for(int i = 0; i < plane.size(); i++) {
		plane[i].draw();
	}

	drawGui();
//	if(resumepanelshown) return;

	setColor(255, 0, 0);

	player.draw();

	light.disable();

	disableDepthTest();
	cam.end();

	fpsDraw();
	root->secondtextfont.drawText(gToStr(score), scorex, scorey + 10);
}

void gCanvas::moveCharacter() {
	if(keystate == KEY_ESC) {
		gamestate = GAMESTATE_PAUSE;
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
		if(linestate == LINE_MID) {
			linestate = LINE_RIGHT;
			linelocation = 3;
			gLogi("line") << "you in line right";
		} else if (linestate == LINE_LEFT) {
			linestate = LINE_MID;
			linelocation = 0;
			gLogi("line") << "you in line mid";
		} else { gLogi("line") << "you already in line right"; }
		break;
	case G_KEY_A:
		pressedkey = KEY_A;
		if(linestate == LINE_MID) {
			linestate = LINE_LEFT;
			linelocation = -3;
			gLogi("line") << "you in line left";
		} else if (linestate == LINE_RIGHT) {
			linestate = LINE_MID;
			linelocation = 0;
			gLogi("line") << "you in line mid";
		} else { gLogi("line") << "you already in line left"; }
		break;
	case G_KEY_ESC:
		pressedkey = KEY_ESC;
		break;
	}
	keystate |= pressedkey;
}

void gCanvas::fpsSetup() {
	fpscounterx = scorex + 20.0f;
	fpscountery = scorey + 30.0f;
}

void gCanvas::fpsDraw() {
	//if(root->getShowFps() == 1) {
	char fpsBuffer[32];
	sprintf(fpsBuffer, "%d FPS", root->getFramerate());
	root->secondtextfont.drawText(fpsBuffer, fpscounterx, fpscountery);

}
void gCanvas::drawGui() {

	if(gamestate == GAMESTATE_PAUSE) {
		resumepanelshown = true;
		resumepanel.draw(rpx, rpy);
		setColor(0, 0, 0, 228);
		root->textfont.drawText("SCORE", scorepanelx + 4, scorepanely + 4);
		root->textfont.drawText(gToStr(score), scorepanelx + 6, scorepanely + 6);
		setColor(212, 212, 212);
		setColor(255, 255, 255);
//		continuebutton.draw(leftbx, leftby);
//		mainmbutton.draw(rightbx, rightby);
	}

/*	if(gamestate == GAMESTATE_PLAY) {
		dialogueshown = false;
	}

	if(!dialogueshown) return;
	if(gamestate == GAMESTATE_GAMEOVER) {
		gui_gameoverdialogue.draw(dialoguex, dialoguey);
		setColor(0, 0, 0, 228);
		scoretitlefont.drawText("SCORE", scoretitlex + 4, scoretitley + 4);
		scorefont.drawText(gToStr(score), scorex + 6, scorey + 6);
		setColor(212, 212, 212);
		scoretitlefont.drawText("SCORE", scoretitlex, scoretitley);
		scorefont.drawText(gToStr(score), scorex, scorey);
		setColor(255, 255, 255);
		replaybutton.draw(leftbx, leftby);
		mainmbutton.draw(rightbx, rightby);
	}*/
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
		case G_KEY_ESC:
			pressedkey = KEY_ESC;
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

