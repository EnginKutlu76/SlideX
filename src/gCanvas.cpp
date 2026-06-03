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
#include <cmath>
gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	std::vector<std::string> texturepaths;
	texturepaths.push_back("space/right.jpg");
	texturepaths.push_back("space/left.jpg");
	texturepaths.push_back("space/top.jpg");
	texturepaths.push_back("space/bottom.jpg");
	texturepaths.push_back("space/right.jpg");
	texturepaths.push_back("space/back.jpg");
	sky.loadTextures(texturepaths);
	sky.pan(PI / 3);

	tex.loadTexture("ss.jpg");
	mat.setDiffuseMap(&tex);
	player.setMaterial(&mat);
	jumpsound.loadSound("effectsound/jumping.wav");
	bestscore.loadSound("effectsound/bestscore.wav");
	countdown.loadSound("effectsound/countdown.wav");
	death.loadSound("effectsound/death.wav");
	doublejump.loadSound("effectsound/doublejump.wav");
	downfall.loadSound("effectsound/downfall.wav");
	leftright.loadSound("effectsound/leftright.wav");
	menubuttons.loadSound("effectsound/menubuttons.wav");
	passobstacle.loadSound("effectsound/passobstacle.wav");
	scoresound.loadSound("effectsound/score.wav");
	optionsound.loadSound("effectsound/optionbuttons.wav");

	gamestate = GAMESTATE_PLAY;
	keystate = KEY_NONE;
	light.setAmbientColor(255, 255, 255);
	light.setDiffuseColor(110, 110, 101);
	light.setSpecularColor(10, 10, 10);
	light.setPosition(0.0f, 50.0f, 50.0f);
	linestate = LINE_MID;
	linelocation = 0;
	color = glm::vec3(255, 0, 0);
	targetColor = glm::vec3(255, 0, 0);
	colorphase = 0.0f;
	fpsSetup();
	guiSetup();
	obstacleSetup();
	scoreSetup();
	planeSetup();
	controlSetup();
	timingSetup();
	camSetup();
	musictickSetup();
	fxtickSetup();
}

void gCanvas::update() {
	sky.setPosition(
		0,
		0,
		player.getPosZ() + 20.0f
	);

	if(root->getSound() == 1) {
		jumpsound.setVolume(0.5f);
		bestscore.setVolume(0.5f);
		countdown.setVolume(0.5f);
		death.setVolume(0.5f);
		doublejump.setVolume(0.2f);
		downfall.setVolume(0.5f);
		leftright.setVolume(0.2f);
		menubuttons.setVolume(0.5f);
		passobstacle.setVolume(0.5f);
		scoresound.setVolume(0.5f);
		optionsound.setVolume(0.5f);
	}

	if(root->getSound() == 0) {
		jumpsound.setVolume(0.0f);
		bestscore.setVolume(0.0f);
		countdown.setVolume(0.0f);
		death.setVolume(0.0f);
		doublejump.setVolume(0.0f);
		downfall.setVolume(0.0f);
		leftright.setVolume(0.0f);
		menubuttons.setVolume(0.0f);
		passobstacle.setVolume(0.0f);
		scoresound.setVolume(0.0f);
		optionsound.setVolume(0.0f);
	}

	timingUpdate();

	if(gamestate != GAMESTATE_PLAY) {
		return;
	}

	if(gamestate == GAMESTATE_PAUSE) {
		return;
	}

	light.setPosition(0.0f, 80.0f, player.getPosZ() + 20.0f);

	float dz = lastplayerz - player.getPosZ();

	if(dz > 0)
		scoreFloat += dz * 0.1f;

	if(score > highscore) {
	    highscore = score;
	    root->saveHighScore(highscore);
	}
	score = (int)scoreFloat;
	lastplayerz = player.getPosZ();

	controlUpdate();
	obstacleUpdate();
	collision();
	planeUpdate();
	camUpdate();
	colorphase += root->getAppManager()->getElapsedTime() * 0.05f;

	targetColor = glm::vec3(
	    127.5f + 127.5f * std::sin(colorphase),
	    127.5f + 127.5f * std::sin(colorphase + 2.0943951f),
	    127.5f + 127.5f * std::sin(colorphase + 4.1887902f)
	);

	color = glm::mix(color, targetColor, 0.02f);
}

void gCanvas::draw() {
	enabling();

	planeDraw();
	obstacleDraw();
	setColor((int)color.r, (int)color.g, (int)color.b);
	sky.draw();
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

void gCanvas::applyAudioSettings() {
	root->saveAudioSettings(isfxenabled, ismusicenabled);
}

void gCanvas::musictickSetup() {
	musictext = "Music";
	musicuncheck.loadImage("UIasset/PNG/button02.png");
	musiccheck.loadImage("check-markred.png");
	musictextw = root->secondtextfont.getStringWidth(musictext);
	musictexth = root->secondtextfont.getStringHeight(musictext);
	musictextx = rpx + (resumepanel.getWidth() * 0.10);
	musictexty = rpy + resumepanel.getHeight() / 1.5;
	musicuncheckw = musicuncheck.getWidth() * 0.5;
	musicuncheckh = musicuncheck.getHeight() * 0.5;
	musicuncheckx = rpx + (musictextw * 2);
	musicunchecky = musictexty - (musictexth / 2) - (musicuncheckh / 2) + 3;
	musiccheckw = musiccheck.getWidth() * 0.06;
	musiccheckh = musiccheck.getHeight() * 0.06;
	musicbuttonhitbox.set(musicuncheckx, musicunchecky, musicuncheckx + musicuncheckw, musicunchecky + musicuncheckh);
	ismusicenabled = root->getMusic();
}

void gCanvas::fxtickSetup() {
	fxtext = "FX Sound";
	fxuncheck.loadImage("UIasset/PNG/button02.png");
	fxcheck.loadImage("check-markred.png");
	fxtextw = root->secondtextfont.getStringWidth(fxtext);
	fxtexth = root->secondtextfont.getStringHeight(fxtext);
	fxtextx = rpx + (resumepanel.getWidth() * 0.10);
	fxtexty = musictexty + (resumepanel.getHeight() / 8);
	fxuncheckw = fxuncheck.getWidth() * 0.5;
	fxuncheckh = fxuncheck.getHeight() * 0.5;
	fxuncheckx = rpx + (fxtextw * 1.5);
	fxunchecky = fxtexty - (fxtexth / 2) - (fxuncheckh / 2) + 3;
	fxcheckw = fxcheck.getWidth() * 0.06;
	fxcheckh = fxcheck.getHeight() * 0.06;
	fxbuttonhitbox.set(fxuncheckx, fxunchecky, fxuncheckx + fxuncheckw, fxunchecky + fxuncheckh);
	isfxenabled = root->getSound();
}

void gCanvas::musictickDraw() {
	root->secondtextfont.drawText(musictext, musictextx, musictexty);
	musicuncheck.draw(musicuncheckx, musicunchecky, musicuncheckw, musicuncheckh);
	if(ismusicenabled) {
		setColor(255, 255, 255);
		musiccheck.draw(musicuncheckx, musicunchecky, musiccheckw, musiccheckh);
	}
}

void gCanvas::fxtickDraw() {
	root->secondtextfont.drawText(fxtext, fxtextx, fxtexty);
	fxuncheck.draw(fxuncheckx, fxunchecky, fxuncheckw, fxuncheckh);
	if(isfxenabled) {
		setColor(255, 255, 255);
		fxcheck.draw(fxuncheckx, fxunchecky, fxcheckw, fxcheckh);
	}
}

void gCanvas::updatePlayState() {

}

void gCanvas::updatePauseState() {

}

void gCanvas::collision() {
	int lane = 1;
	if(player.getPosX() < -1.5f) lane = 0;
	else if(player.getPosX() > 1.5f) lane = 2;

	int layer = 0;
	if(player.getPosY() > 5.0f) layer = 2;
	else if(player.getPosY() > LANE_OFFSET) layer = 1;

	for(int i = 0; i < rows.size(); i++) {
		float dz = abs(player.getPosZ() - rows[i].z);

		if(dz < 3.0f) {
			if(rows[i].cell[lane][layer]) {
				gamestate = GAMESTATE_GAMEOVER;
				death.play();
				//death.stop();
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
		for(int i = 0; i < resumetimer; i++) {
			countdown.play();
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
//	player.setScale(0.1f, 0.1f, 0.1f);
	player.setPosition(0, 2, 20);
	lastplayerz = player.getPosZ();
	speed = -0.60f;
	maxspeed = -2.5f;
	acceleration = -0.0002f;
	velocityy = 0.0f;
	isjumping = false;
	isgrounded = false;
}

void gCanvas::controlUpdate() {
	if(isdownfall) {
	    velocityy += GRAVITY * 2.5f;
		downfall.play(); }
	else
	    velocityy += GRAVITY;
	if(speed > maxspeed) {
		speed += acceleration;
	}
	player.setPosition(
		linelocation,
		player.getPosY() + velocityy,
		player.getPosZ() + speed
	);

	if(player.getPosY() <= GROUND_Y) {

		player.setPosition(
			player.getPosX(),
			GROUND_Y,
			player.getPosZ()
		);
		velocityy = 0.0f;
		isgrounded = true;
		player.setScale(1.0f, 1.0f, 1.0f);
		isdownfall = false;
		downfallVelocity = 0.0f;
	}
	else {
		isgrounded = false;
	}

	static bool downfalltilted = false;

	if(isdownfall && !downfalltilted)
	{
		player.tilt(-45.0f);
		downfalltilted = true;
	}

	if(isgrounded && downfalltilted)
	{
		player.tilt(45.0f);
		downfalltilted = false;
	}

	if(isjumping) {
		jumpsound.play();
		player.tilt(6.0f);
		player.setScale(0.8f, 0.8f, 0.8f);
		jumprotation += 6.0f;

		if(jumprotation >= 90.0f) {
			jumpsound.stop();
			player.tilt(-jumprotation);
			jumprotation = 0.0f;
			isjumping = false;
		}
	}
}

void gCanvas::planeSetup() {
	planetex.loadTexture("aa.jpg");
	planemat.setDiffuseMap(&planetex);

	for(int i = 0; i < 8; i++) {
		plane.push_back(plane1);
	}

	for(int i = 0; i < plane.size(); i++) {

		plane[i].setScale(5, 1, 40);

		plane[i].setPosition(
			0,
			0,
			i * -80
		);
		plane[i].setMaterial(&planemat);
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

		if(plane[i].getPosZ() > player.getPosZ() + 60) {

			lastplanez -= 80;

			plane[i].setPosition(
				plane[i].getPosX(),
				plane[i].getPosY(),
				lastplanez
			);
		}
	}
}

void gCanvas::scoreSetup() {
	highscore = root->getHighScore();
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
	overpanel.loadImage("dialogue_gameover.png");
	mainmbutton.loadImage("button_mainmenu.png");
	continuebutton.loadImage("button_continue.png");
	restartbutton.loadImage("button_replay.png");

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

	nextRowZ = -100.0f;

	for(int i = 0; i < 20; i++) {
		Row r;
		r.z = nextRowZ;
		nextRowZ -= ROW_SPACING;

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
	obstacle.setMaterial(&mat);

	for(int i = 0; i < rows.size(); i++) {
		if(rows[i].z > player.getPosZ() + 40.0f) {
			rows[i].z = nextRowZ;
			nextRowZ -= ROW_SPACING;

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
	setColor((int)color.r, (int)color.g, (int)color.b);
	for(int i = 0; i < rows.size(); i++) {
		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				if(!rows[i].cell[x][y]) continue;

				float worldX = (x - 1) * LANE_OFFSET;
				float worldY = GROUND_Y + (y * GROUND_Y);

				obstacle.setScale(1.5f, 1.0f, 1.0f);
				obstacle.setPosition(worldX, worldY, rows[i].z);
				obstacle.draw();
			}
		}
	}

	setColor(255, 255, 255);
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
	if(gamestate != GAMESTATE_PAUSE && gamestate != GAMESTATE_GAMEOVER) return;
	if(isresuming) return;

	setColor(0, 0, 0, 180);
	hitbox.set(0, 0, getWidth(), getHeight());

	setColor(255, 255, 255);

	if(gamestate == GAMESTATE_PAUSE) {
		resumepanel.draw(rpx, rpy);

		continuebutton.draw(leftbx, leftby);
		musictickDraw();
		fxtickDraw();
	}
	else if(gamestate == GAMESTATE_GAMEOVER) {
		overpanel.draw(rpx, rpy);

		restartbutton.draw(leftbx, leftby);
	}

	root->secondtextfont.drawText(
		"SCORE : " + gToStr(score),
		rpx + 80,
		rpy + 100
	);

	root->secondtextfont.drawText(
		"BEST SCORE : " + gToStr(highscore),
		rpx + 80,
		rpy + 150
	);

	mainmbutton.draw(rightbx, rightby);

	setColor(255, 255, 255);
}

void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
	int pressedkey = KEY_NONE;
	switch(key) {
	case G_KEY_W:
		pressedkey = KEY_W;
		if(isgrounded) {
			secondjump = true;
			velocityy = 0.30f;
			isjumping = true;
			jumprotation = 0.0f;
			isgrounded = false;
		} else if(secondjump) {
			doublejump.play();
			velocityy = 0.30f;
			secondjump = false;
		}
		break;
	case G_KEY_S:
		pressedkey = KEY_S;
		pressedkey = KEY_S;

		if(!isgrounded)
		{
		    isdownfall = true;
		    downfallVelocity = -1.2f;
		}
		break;
	case G_KEY_D:
		pressedkey = KEY_D;
		if(linestate == LINE_MID) {
			linestate = LINE_RIGHT;
			leftright.play();
			linelocation = 3;
		} else if (linestate == LINE_LEFT) {
			linestate = LINE_MID;
			leftright.play();
			linelocation = 0;
		}
		break;

	case G_KEY_A:
		pressedkey = KEY_A;
		if(linestate == LINE_MID) {
			linestate = LINE_LEFT;
			leftright.play();
			linelocation = -3;
		} else if (linestate == LINE_RIGHT) {
			linestate = LINE_MID;
			leftright.play();
			linelocation = 0;
		}
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
	if(musicbuttonhitbox.contains(x, y)) {
		musictickstate = BUTTON_PRESSED;
	}

	if(fxbuttonhitbox.contains(x, y)) {
		fxtickstate = BUTTON_PRESSED;
	}
}

void gCanvas::mouseReleased(int x, int y, int button) {
	if(gamestate == GAMESTATE_GAMEOVER) {
		if(x >= leftbx && x < leftbx + leftbw && y >= leftby && y < leftby + leftbh) {
			menubuttons.play();
			gCanvas* cnv = new gCanvas(root);
			root->setCurrentCanvas(cnv);
			return;
		}
	}

	if(gamestate == GAMESTATE_PAUSE) {
		if(x >= leftbx && x < leftbx + leftbw && y >= leftby && y < leftby + leftbh) {
			menubuttons.play();
			isresuming = true;
			resumetimer = 3.0f;
		}
	}

	if(gamestate == GAMESTATE_GAMEOVER || gamestate == GAMESTATE_PAUSE) {
		if(x >= rightbx && x < rightbx + rightbw && y >= rightby && y < rightby + rightbh) {
			menubuttons.play();
			MainMenuCanvas* cnv = new MainMenuCanvas(root);
			root->setCurrentCanvas(cnv);
			return;
		}
	}

	if(musicbuttonhitbox.contains(x, y) && musictickstate == BUTTON_PRESSED) {
	    musictickstate = BUTTON_PERFORMED;
	    ismusicenabled = !ismusicenabled;
	    optionsound.play();
		applyAudioSettings();
		musictickSetup();
	}
	else if(fxbuttonhitbox.contains(x, y) && fxtickstate == BUTTON_PRESSED) {
	    fxtickstate = BUTTON_PERFORMED;
	    isfxenabled = !isfxenabled;
	    optionsound.play();
	    applyAudioSettings();
		fxtickSetup();
	}
	else {
		musictickstate = BUTTON_CANCELED;
		fxtickstate = BUTTON_CANCELED;
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
	rpw = resumepanel.getWidth();
	rph = resumepanel.getHeight();
	rpx = (w - rpw) / 2.0f;
	rpy = (h - rph) / 2.0f;

	leftbx = rpx + 100;
	leftby = rpy + 300;

	rightbx = rpx + 300;
	rightby = rpy + 300;

	scorex = (w - root->textfont.getStringWidth(gToStr(score))) / 2;
	scorey = root->textfont.getStringHeight(gToStr(score));

	fpscounterx = scorex + 20.0f;
	fpscountery = scorey + 30.0f;

	hitbox.set(0, 0, w, h);
}

void gCanvas::showNotify() {

}

void gCanvas::hideNotify() {

}

