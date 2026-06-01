/*
 * CreditsMenu.cpp
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#include "CreditsMenu.h"
#include "MainMenuCanvas.h"
#include "gFont.h"

CreditsMenu::CreditsMenu(gApp* root): gBaseCanvas(root) {
	this->root = root;
}

CreditsMenu::~CreditsMenu() {
}

void CreditsMenu::setup() {
	backgroundimg.loadImage("UIasset/PNG/MainPanel03.png");
	bgw = backgroundimg.getWidth();
	bgh = backgroundimg.getHeight();
	bgx = 0;
	bgy = 0;
	setupTexts();
	setupButton();

	normalcolor.set(255,255,255);
	focuscolor.set(200,200,200);
	pressedcolor.set(180,180,180);
}

void CreditsMenu::update() {
}

void CreditsMenu::draw() {
	backgroundimg.draw(0, 0);
	drawTexts();
	drawButton();
}

void CreditsMenu::setupTexts() {
	line1 = "Developed By";
	line2 = "Engin Kutlu";
	line3 = "Game Studio: Tengri Games";
	line4 = "Programming & Design: Engin Kutlu";
	line5 = "Special Thanks: glistEngine, GameLab Istanbul";
	line6 = "Assets & Fonts Licensed (dafont)";
	line7 = "(c) 2026";

	centerx = getWidth() / 2;
	linegap = 30;

	starty = getHeight() / 2 - 3 * linegap;
	title = "CREDITS";
	titley = getHeight() * 15 / 100;
}

void CreditsMenu::drawTexts() {
	int y = starty;

	std::vector<std::string> lines = {
		line1, line2, line3, line4, line5, line6, line7
	};

	for(int i = 0; i < lines.size(); i++) {
		int w = root->secondtextfont.getStringWidth(lines[i]);
		root->secondtextfont.drawText(lines[i], centerx - w / 2, y);
		y += linegap;
	}

	int titlew = root->textfont.getStringWidth(title);
	root->titlefont.drawText(title, centerx - titlew / 1.25, titley);
}

void CreditsMenu::setupButton() {
	returntext = root->returnkey;

	returnw = root->textfont.getStringWidth(returntext);
	returnh = root->textfont.getStringHeight(returntext);

	returnx = getWidth() * 5 / 100;
	returny = getHeight() * 95 / 100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnstate = 0;
}

void CreditsMenu::drawButton() {
	if(returnstate == 1) setColor(focuscolor);
	else if(returnstate == 2) setColor(pressedcolor);
	else setColor(normalcolor);

	root->titlefont.drawText(returntext, returnx, returny);
	setColor(255,255,255);
}

void CreditsMenu::updateButtonState(int x, int y) {
	if(returnstate != 2) {
		if(returnhitbox.contains(x,y)) returnstate = 1;
		else returnstate = 0;
	}
}

void CreditsMenu::checkButtonPressed(int x, int y) {
	if(returnhitbox.contains(x,y)) {
		returnstate = 2;
		returny += 2;
	}
}

void CreditsMenu::checkButtonReleased(int x, int y) {
	if(returnhitbox.contains(x,y) && returnstate == 2) {
		returny -= 2;
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}
	returnstate = 0;
}

void CreditsMenu::mouseMoved(int x, int y) {
	updateButtonState(x,y);
}

void CreditsMenu::mousePressed(int x, int y, int button) {
	checkButtonPressed(x,y);
}

void CreditsMenu::mouseReleased(int x, int y, int button) {
	checkButtonReleased(x,y);
}
