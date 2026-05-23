/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: Noyan Culum
*/


#include "gCanvas.h"
#include "MainMenuCanvas.h"
#include <ctime>
#include <vector>
#include <cstdlib>
gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	gamestate = GAMESTATE_PLAY;
	keystate = KEY_NONE;
	light.setDiffuseColor(255, 255, 245);
	light.setPosition(0.0f, 50.0f, 20.0f);
	linestate = LINE_MID;
	linelocation = 0;
	fpsSetup();
	guiSetup();
	obstacleSetup();
	scoreSetup();
	planeSetup();
	controlSetup();
	timingSetup();
	camSetup();
}

void gCanvas::update() {

	timingUpdate();

	if(gamestate == GAMESTATE_PAUSE) {
		return;
	}

	light.setPosition(player.getPosX(), player.getPosY() + 200, player.getPosZ() + 30);

	float dz = lastplayerz - player.getPosZ();

	if(dz > 0)
		scoreFloat += dz * 0.1f;

	score = (int)scoreFloat;
	lastplayerz = player.getPosZ();

	controlUpdate();
	obstacleUpdate();
	collision();
	planeUpdate();
	camUpdate();
}

void gCanvas::draw() {
	enabling();

	planeDraw();
	obstacleDraw();
	setColor(0, 255, 0);
	player.draw();
	setColor(255, 255, 255);
	disabling();
	setColor(255, 0, 0);
	scoreDraw();
	fpsDraw();
	setColor(255, 255, 255);
	if(isresuming) {
		setColor(0, 0, 255);

		root->secondtextfont.drawText(
			gToStr((int)ceil(resumetimer)),
			getWidth() / 2,
			getHeight() / 2
		);
	}

	setColor(255, 255, 255);

	guiDraw();
}

void gCanvas::collision() {
	int lane = 1;
	if(player.getPosX() < -1.5f) lane = 0;
	else if(player.getPosX() > 1.5f) lane = 2;

	int layer = 0;
	if(player.getPosY() > 5.0f) layer = 2;
	else if(player.getPosY() > 3.0f) layer = 1;

	for(int i = 0; i < rows.size(); i++) {
		float dz = abs(player.getPosZ() - rows[i].z);

		if(dz < 3.0f) {
			if(rows[i].cell[lane][layer]) {
				gamestate = GAMESTATE_PAUSE;
				return;
			}
		}
	}
}

void gCanvas::camSetup() {
	cam.boom(10.0f);
}

void gCanvas::camUpdate() {
	cam.setPosition(
		0,
		player.getPosY() + 8.0f,
		player.getPosZ() + 20.0f
	);

	cam.lookAt(glm::vec3(
		0,
		player.getPosY(),
		player.getPosZ()
	));
}

void gCanvas::timingSetup() {
	resumetimer = 0.0f;
	isresuming = false;
}

void gCanvas::timingUpdate() {
	if(isresuming) {

		resumetimer -= root->getAppManager()->getElapsedTime();

		if(resumetimer <= 0.0f) {
			isresuming = false;
			gamestate = GAMESTATE_PLAY;
		}

		return;
	}
}

void gCanvas::enabling() {
	setColor(255, 255, 255);
	cam.begin();
	enableDepthTest();
	light.enable();
}

void gCanvas::disabling() {
	light.disable();
	disableDepthTest();
	cam.end();
}

void gCanvas::controlSetup() {
	player.setScale(0.1f, 0.1f, 0.1f);
	player.setPosition(0, 2, 20);
	lastplayerz = player.getPosZ();
	speed = -0.40f;
	maxspeed = -3.0f;
	acceleration = -0.0002f;
	velocityy = 0.0f;
	gravity = -0.015f;
	isjumping = false;
	isgrounded = false;
}

void gCanvas::controlUpdate() {
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
}

void gCanvas::planeSetup() {
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
}

void gCanvas::planeDraw() {
	for(int i = 0; i < plane.size(); i++) {
		plane[i].draw();
	}
}

void gCanvas::planeUpdate() {
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
}

void gCanvas::scoreSetup() {
	score = 0;
	scorex = (getWidth() - root->textfont.getStringWidth(gToStr(score))) / 2;
	scorey = root->textfont.getStringHeight(gToStr(score));
	scoreFloat = 0.0f;
}

void gCanvas::scoreDraw() {
	root->secondtextfont.drawText(gToStr(score), scorex, scorey + 10);
}

void gCanvas::guiSetup() {
	resumepanel.loadImage("dialogue_pause.png");
	mainmbutton.loadImage("button_mainmenu.png");
	continuebutton.loadImage("button_continue.png");

	rpw = resumepanel.getWidth();
	rph = resumepanel.getHeight();
	rpx = (getWidth() - rpw) / 2.0f;
	rpy = (getHeight() - rph) / 2.0f;

	leftbw = continuebutton.getWidth();
	leftbh = continuebutton.getHeight();
	leftbx = rpx + 100;
	leftby = rpy + 300;

	rightbw = mainmbutton.getWidth();
	rightbh = mainmbutton.getHeight();
	rightbx = rpx + 300;
	rightby = rpy + 300;

}

void gCanvas::obstacleSetup() {
	rows.clear();

	rowSpacing = 18.0f;
	nextRowZ = -100.0f;

	for(int i = 0; i < 20; i++) {
		Row r;
		r.z = nextRowZ;
		nextRowZ -= rowSpacing;

		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				r.cell[x][y] = true;
			}
		}

		int holes = 1 + rand() % 2;

		for(int h = 0; h < holes; h++) {
			int x = rand() % 3;
			int y = rand() % 3;
			r.cell[x][y] = false;
		}

		rows.push_back(r);
	}
}
void gCanvas::obstacleUpdate() {
	for(int i = 0; i < rows.size(); i++) {
		if(rows[i].z > player.getPosZ() + 40.0f) {
			rows[i].z = nextRowZ;
			nextRowZ -= rowSpacing;

			for(int x = 0; x < 3; x++) {
				for(int y = 0; y < 3; y++) {
					rows[i].cell[x][y] = true;
				}
			}

			int holes = 1 + rand() % 2;

			for(int h = 0; h < holes; h++) {
				int x = rand() % 3;
				int y = rand() % 3;
				rows[i].cell[x][y] = false;
			}
		}
	}
}
void gCanvas::obstacleDraw() {
	setColor(255, 0, 0);

	for(int i = 0; i < rows.size(); i++) {
		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				if(!rows[i].cell[x][y]) continue;

				float worldX = (x - 1) * 3.0f;
				float worldY = 2.0f + (y * 2.0f);

				obstacle.setPosition(worldX, worldY, rows[i].z);
				obstacle.draw();
			}
		}
	}

	setColor(255, 255, 255);
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
		if(gamestate == GAMESTATE_PLAY) {
			gamestate = GAMESTATE_PAUSE;
		}
		else if(gamestate == GAMESTATE_PAUSE && !isresuming) {
			isresuming = true;
			resumetimer = 3.0f;
		}
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
void gCanvas::guiDraw() {
	if(gamestate != GAMESTATE_PAUSE) return;
	if(isresuming) return;

	setColor(0, 0, 0, 180);
	hitbox.set(0, 0, getWidth(), getHeight());

	setColor(255, 255, 255);

	resumepanel.draw(rpx, rpy);

	root->secondtextfont.drawText(
		"SCORE : " + gToStr(score),
		rpx + 80,
		rpy + 100
	);

	setColor(255, 255, 255);
	continuebutton.draw(leftbx, leftby);
	mainmbutton.draw(rightbx, rightby);
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
	if(gamestate == GAMESTATE_GAMEOVER) {
		if(x >= leftbx && x < leftbx + leftbw && y >= leftby && y < leftby + leftbh) {
			gCanvas* cnv = new gCanvas(root);
			root->setCurrentCanvas(cnv);
			return;
		}
	}
	if(gamestate == GAMESTATE_PAUSE) {
		if(x >= leftbx && x < leftbx + leftbw && y >= leftby && y < leftby + leftbh) {
//			gamestate = GAMESTATE_PLAY;
			isresuming = true;
			resumetimer = 3.0f;
		}
	}

	if(gamestate == GAMESTATE_GAMEOVER || /*gamestate == GAMESTATE_WIN ||*/ gamestate == GAMESTATE_PAUSE) {
		if(x >= rightbx && x < rightbx + rightbw && y >= rightby && y < rightby + rightbh) {
			MainMenuCanvas* cnv = new MainMenuCanvas(root);
			root->setCurrentCanvas(cnv);
			return;
		}
	}
	if(resumepanelshown) return;
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

