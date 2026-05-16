/*
 * ContactCanvas.cpp
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#include "ContactCanvas.h"
#include "MainMenuCanvas.h"

ContactCanvas::ContactCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

ContactCanvas::~ContactCanvas() {
}

void ContactCanvas::setup() {
	tabSetup();
	containerSetup();
	contactSetup();
}

void ContactCanvas::update() {
}

void ContactCanvas::draw() {
	root->drawMenuBackground(getWidth(), getHeight());

	tabDraw();
	containerDraw();
}

void ContactCanvas::keyPressed(int key) {
}

void ContactCanvas::keyReleased(int key) {
	if(key == G_KEY_ESC) {
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}
}

void ContactCanvas::charPressed(unsigned int codepoint) {
}

void ContactCanvas::mouseMoved(int x, int y) {
	tabButtonFocus(x, y);
}

void ContactCanvas::mouseDragged(int x, int y, int button) {
}

void ContactCanvas::mousePressed(int x, int y, int button) {
	tabButtonPressed(x, y);
}

void ContactCanvas::mouseReleased(int x, int y, int button) {
	tabButtonReleased(x, y);
}

void ContactCanvas::mouseScrolled(int x, int y) {
}

void ContactCanvas::mouseEntered() {
}

void ContactCanvas::mouseExited() {
}

void ContactCanvas::windowResized(int w, int h) {
}

void ContactCanvas::showNotify() {
}

void ContactCanvas::hideNotify() {
}

void ContactCanvas::tabSetup() {
	tabw = getWidth() / 2;
	tabh = getHeight() / 10;

	tabx = (getWidth() - tabw) / 2;
	taby = tabh;

	tabcolor.set(54, 126, 127);

	normalcolor.set(45, 50, 70);
	pressedcolor.set(65, 70, 90);
	focuscolor.set(55, 60, 80);

	tabtitle = "CONTACT";

	returnSetup();
}

void ContactCanvas::tabDraw() {
	setColor(tabcolor);
	gDrawRectangle(tabx, taby, tabw, tabh, true);

	tabtextw = root->titlefont.getStringWidth(tabtitle);
	tabtexth = root->titlefont.getStringHeight(tabtitle);

	tabtextx = tabx + (tabw - tabtextw) / 2;
	tabtexty = taby + (tabh + tabtexth) / 2;

	setColor(0, 0, 0);
	root->titlefont.drawText(tabtitle, tabtextx, tabtexty);

	returnDraw();
}

void ContactCanvas::containerSetup() {
	containerw = tabw;
	containerh = tabh * 7;

	containerx = tabx;
	containery = taby + tabh;

	containercolor.set(255, 255, 255);
}

void ContactCanvas::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);

	contactDraw();
}

void ContactCanvas::contactSetup() {
	contactlines.clear();

	contactlines.push_back("E-Mail: contact@yourmail.com");
	contactlines.push_back("X: x.com/youraccount");
	contactlines.push_back("Instagram: instagram.com/youraccount");
	contactlines.push_back("Website: yourwebsite.com");
	contactlines.push_back("itch.io: yourname.itch.io");

	contactlineh = root->secondtextfont.getStringHeight("y");

	contactx = containerx + containerw * 0.08f;
	contacty = containery + containerh * 0.18f;
}

void ContactCanvas::contactDraw() {
	setColor(0, 0, 0);

	float y = contacty;

	for(const auto& line : contactlines) {
		root->secondtextfont.drawText(line, contactx, y);
		y += contactlineh + 30.0f;
	}
}

void ContactCanvas::returnSetup() {
	returntext = "Return";

	returnh = root->titlefont.getStringHeight(returntext);
	returnw = root->titlefont.getStringWidth(returntext);

	returnx = getWidth() * 0.05f;
	returny = getHeight() * 0.95f;

	returnhitbox.set(returnx,
					 returny - returnh,
					 returnx + returnw,
					 returny);

	returnbuttonstate = BUTTON_NONE;
}

void ContactCanvas::returnDraw() {
	setColor(255, 255, 255);

	if(returnbuttonstate == BUTTON_FOCUS) {
		setColor(focuscolor);
	}

	if(returnbuttonstate == BUTTON_PRESSED) {
		setColor(pressedcolor);
	}

	root->titlefont.drawText(returntext, returnx, returny);
}

void ContactCanvas::tabButtonPressed(int x, int y) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}
}

void ContactCanvas::tabButtonReleased(int x, int y) {
	if(returnhitbox.contains(x, y) &&
	   returnbuttonstate == BUTTON_PRESSED) {

		returnbuttonstate = BUTTON_PERFORMED;

		returny -= 2;

		root->setCurrentCanvas(new MainMenuCanvas(root));
	}
	else {
		returnbuttonstate = BUTTON_CANCELED;
	}
}

void ContactCanvas::tabButtonFocus(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}
}
