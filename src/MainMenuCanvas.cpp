/*
 * MainMenuCanvas.cpp
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#include <MainMenuCanvas.h>
#include "gCanvas.h"
#include "CreditsMenu.h"
#include "Options.h"

MainMenuCanvas::MainMenuCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

MainMenuCanvas::~MainMenuCanvas() {
	// TODO Auto-generated destructor stub
}

void MainMenuCanvas::setup() {
	//background.loadImage("black.png");
	logoSetup();
	startSetup();
	optionSetup();
	colorSetup();
}

void MainMenuCanvas::update() {
}

void MainMenuCanvas::draw() {
	backgroundDraw();
	logoDraw();
	startDraw();
	optionDraw();
	//fadeEffectDraw();
}

void MainMenuCanvas::keyPressed(int key) {
}

void MainMenuCanvas::keyReleased(int key) {
	if(key == G_KEY_ESC) exit(0);
}

void MainMenuCanvas::charPressed(unsigned int codepoint) {
}

void MainMenuCanvas::mouseMoved(int x, int y) {
	//	gLogi("mainMenu") << "mouseMoved" << ", x:" << x << ", y:" << y;
	updateButtonState(x, y);
}

void MainMenuCanvas::mouseDragged(int x, int y, int button) {
	//	gLogi("mainMenu") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void MainMenuCanvas::mousePressed(int x, int y, int button) {
	//	gLogi("mainMenu") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	checkButtonPressed(x, y, button);
}

void MainMenuCanvas::mouseReleased(int x, int y, int button) {
	//	gLogi("mainMenu") << "mouseReleased" << ", button:" << button;
	checkButtonReleased(x, y, button);
}

void MainMenuCanvas::mouseScrolled(int x, int y) {
}

void MainMenuCanvas::mouseEntered() {
}

void MainMenuCanvas::mouseExited() {
}

void MainMenuCanvas::windowResized(int w, int h) {
}

void MainMenuCanvas::showNotify() {
}

void MainMenuCanvas::hideNotify() {
}

void MainMenuCanvas::backgroundDraw() {
	root->drawMenuBackground(getWidth(), getHeight());
	setColor(165, 55, 55);
	root->gametitlefont.drawText(root->titlekey, titlex, titley);
	setColor(255, 255, 255);
}

void MainMenuCanvas::logoSetup() {
	glistlogo.loadImage("glistengine_logo.png");

	int titlesizer = 10;
	int nitralogosizer = 8;
	int glistlogosizer = 3;
	int padding = 25;

	titlew = root->gametitlefont.getStringWidth(root->titlekey);
	titleh = root->gametitlefont.getStringHeight(root->titlekey);
	titlex = (getWidth() - titlew) / 2;
	titley = (getHeight() - titleh) / 5;

	glistlogow = glistlogo.getWidth() / glistlogosizer;
	glistlogoh = glistlogo.getHeight() / glistlogosizer;
	glistlogox = 1300;
	glistlogoy = 840;

}

void MainMenuCanvas::startSetup() {
	starttext = root->startkey;
	startw = root->titlefont.getStringWidth(starttext);
	starth = root->titlefont.getStringHeight(starttext);
	startx = titlex + (titlew - startw) / 2;
	starty = titley + startw;
	starthitbox.set(startx, starty - starth, startx + startw, starty);
	startstate = BUTTON_NONE;
}

void MainMenuCanvas::optionSetup() {
	optiontext = root->optionskey;
	optionw = root->titlefont.getStringWidth(optiontext);
	optionh = root->titlefont.getStringHeight(optiontext);
	optionx = startx + (startw - optionw) / 2;
	optiony = starty + (optionh + 60);
	optionhitbox.set(optionx, optiony - optionh, optionx + optionw, optiony);
	optionstate = BUTTON_NONE;
}

void MainMenuCanvas::colorSetup() {
	pressedcolor.set(190, 190, 190);
	normalcolor.set(255, 255, 255);
	focuscolor.set(200, 200, 200);
}

/*void mainMenu::backgroundDraw() {
	background.draw(getWidth(), getHeight());
	setColor(165, 55, 55);
	menutitlefont.drawText("TANKS", titlex, titley);
	setColor(255, 255, 255);
}*/

void MainMenuCanvas::logoDraw() {
	glistlogo.draw(glistlogox, glistlogoy, glistlogow, glistlogoh);
}

void MainMenuCanvas::startDraw() {
	//if (gamestate != gApp::GAME_PAUSE) return;
	if(startstate == BUTTON_FOCUS) setColor(focuscolor);
	if(startstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->titlefont.drawText(starttext, startx, starty);
	setColor(normalcolor);
}

void MainMenuCanvas::optionDraw() {
	if(optionstate == BUTTON_FOCUS) setColor(focuscolor);
	if(optionstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->titlefont.drawText(optiontext, optionx, optiony);
	setColor(normalcolor);
}

void MainMenuCanvas::fadeEffectDraw() {
	//if(fadeeffect->isDrawing()) fadeeffect->drawFadeEffect();
}

void MainMenuCanvas::updateButtonState(int x, int y) {
	if(startstate != BUTTON_PRESSED) {
		if(starthitbox.contains(x, y)) {
			startstate = BUTTON_FOCUS;
		}
		else {
			startstate = BUTTON_NONE;
		}
	}
	if(optionstate != BUTTON_PRESSED) {
		if(optionhitbox.contains(x, y)) {
			optionstate = BUTTON_FOCUS;
		}
		else {
			optionstate = BUTTON_NONE;
		}
	}
}

void MainMenuCanvas::checkButtonPressed(int x, int y, int button) {
	if(starthitbox.contains(x, y)) {
		startstate = BUTTON_PRESSED;
		starty += 2;
	}

	if(optionhitbox.contains(x, y)) {
		optionstate = BUTTON_PRESSED;
		optiony += 2;
	}
}

void MainMenuCanvas::checkButtonReleased(int x, int y, int button) {
	if(starthitbox.contains(x, y) && startstate == BUTTON_PRESSED) {
		startstate = BUTTON_PERFORMED;
		starty -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new gCanvas(root));
	}

	else if(optionhitbox.contains(x, y) && optionstate == BUTTON_PRESSED) {
		optionstate = BUTTON_PERFORMED;
		optiony -=2;
		root->setCurrentCanvas(new Options(root));
	}

	else {
		startstate = BUTTON_CANCELED;
		//optionstate = BUTTON_CANCELED;
	}
}
