/*
 * Help.cpp
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#include "Help.h"
#include "gCanvas.h"
#include "MainMenuCanvas.h"

Help::Help(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

Help::~Help() {
}

void Help::setup() {
	tabSetup();
	containerSetup();
	forwardButtonSetup();
	backButtonSetup();
	modetabtext = "Modes";
	activetab = TAB_GENERAL;
}

void Help::update() {
}

void Help::draw() {
	root->drawMenuBackground(getWidth(), getHeight());
	tabDraw();
	containerDraw();
	forwardButtonDraw();
	backButtonDraw();
}

void Help::keyPressed(int key) {
	//	gLogi("HelpMenu") << "keyPressed:" << key;
}

void Help::keyReleased(int key) {
	//	gLogi("HelpMenu") << "keyReleased:" << key;
	if(key == G_KEY_ESC) {
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}
}

void Help::charPressed(unsigned int codepoint) {
	//	gLogi("Help") << "charPressed:" << gCodepointToStr(codepoint);
}

void Help::mouseMoved(int x, int y) {
	//	gLogi("Help") << "mouseMoved" << ", x:" << x << ", y:" << y;
	tabButtonFocus(x, y);
	containerButtonFocus(x, y);
}

void Help::mouseDragged(int x, int y, int button) {
	//	gLogi("Help") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void Help::mousePressed(int x, int y, int button) {
	//	gLogi("Help") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	tabButtonPressed(x, y);
	containerButtonPressed(x, y);
}

void Help::mouseReleased(int x, int y, int button) {
	//	gLogi("Help") << "mouseReleased" << ", button:" << button;
	tabButtonReleased(x, y);
	containerButtonReleased(x, y);
}

void Help::mouseScrolled(int x, int y) {
	//	gLogi("Help") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void Help::mouseEntered() {

}

void Help::mouseExited() {

}

void Help::windowResized(int w, int h) {

}

void Help::showNotify() {

}

void Help::hideNotify() {

}

void Help::tabSetup() {
	tabw = getWidth() / 2;
	tabh = getHeight() / 10;
	tabx = (getWidth() - tabw) / 2;
	taby = tabh;
	tabcolor.set(54, 126, 127);
	normalcolor.set(45, 50, 70);
	pressedcolor.set(65, 70, 90);
	focuscolor.set(55, 60, 80);
	returnSetup();

	activetab = TAB_GENERAL;
}

void Help::tabDraw() {
	setColor(tabcolor);
	gDrawRectangle(tabx, taby, tabw, tabh, true);
	setColor(normalcolor);
	tabtitle = getTabTitle();
	tabtextw = root->titlefont.getStringWidth(tabtitle);
	tabtexth = root->titlefont.getStringHeight(tabtitle);

	tabtextx = tabx + (tabw - tabtextw) / 2;
	tabtexty = taby + (tabh + tabtexth) / 2;

	setColor(0, 0, 0);
	root->titlefont.drawText(tabtitle, tabtextx, tabtexty);
	setColor(normalcolor);

	returnDraw();
}

void Help::tabButtonPressed(int x, int y) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}
	if(forwardbutton.contains(x, y)) {
		forwardstate = BUTTON_PRESSED;
	}
	if(backbutton.contains(x, y)) {
		backstate = BUTTON_PRESSED;
	}
}

void Help::tabButtonReleased(int x, int y) {
    if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		returny -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}

	else if(forwardbutton.contains(x, y) && forwardstate == BUTTON_PRESSED && activetab < TAB_CONTROLS) {
		forwardstate = BUTTON_PERFORMED;
		activetab += 1;
		activeposx += 40;
	}

	else if(backbutton.contains(x, y) && backstate == BUTTON_PRESSED && activetab > TAB_GENERAL) {
		backstate = BUTTON_PERFORMED;
		activetab -= 1;
		activeposx -= 40;
	}

	else {
		returnbuttonstate = BUTTON_CANCELED;
		forwardstate = BUTTON_CANCELED;
		backstate = BUTTON_CANCELED;
	}
}

void Help::tabButtonFocus(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}

	if(forwardstate != BUTTON_PRESSED) {
		if(forwardbutton.contains(x, y)) {
			forwardstate = BUTTON_FOCUS;
		}
		else {
			forwardstate = BUTTON_NONE;
		}
	}

	if(backstate != BUTTON_PRESSED) {
		if(backbutton.contains(x, y)) {
			backstate = BUTTON_FOCUS;
		}
		else {
			backstate = BUTTON_NONE;
		}
	}
}

void Help::containerSetup() {
	containerw = tabw;
	containerh = tabh * 7;
	containerx = tabx;
	containery = taby + tabh;
	containercolor.set(255, 255, 255);
	activepart.loadImage("activecolor.png");
	inactivepart.loadImage("inactivecolor.png");
	activew = activepart.getWidth();
	activeh = activepart.getHeight();
	activex = (containerx + containerw / 2) - 80;
	activey = (containery + containerw / 1.25) - activeh;
	activeposx = activex;
	gameSettingsSetup();
	modeSettingsSetup();
	itemsSettingsSetup();
	controlsSettingsSetup();
}

void Help::gameSettingsSetup() {
	gamelabeltext = root->localizeWord(root->generallabelkey);
    gamelabellines = root->titlefont.wrapSentenceByWidth(gamelabeltext, containerw * 0.8f);
    gamelabelh = root->titlefont.getStringHeight("y");
    gamelabelx = containerx + containerw / 10;
    gamelabely = containery + containerh / 15 + gamelabelh;
}

void Help::modeSettingsSetup() {

}

void Help::itemsSettingsSetup() {

}

void Help::controlsSettingsSetup() {
}


void Help::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);
	if(activetab == TAB_GENERAL) gameSettingsDraw();
	else if(activetab == TAB_LEVEL) modeSettingsDraw();
	else if(activetab == TAB_ITEMS) itemsSettingsDraw();
	else if(activetab == TAB_CONTROLS) controlsSettingsDraw();
	setColor(255, 255, 255);
	inactivepart.draw(activex, activey, activew, activeh);
	inactivepart.draw(activex + 40, activey, activew, activeh);
	inactivepart.draw(activex + 80, activey, activew, activeh);
	inactivepart.draw(activex + 120, activey, activew, activeh);
	activepart.draw(activeposx, activey, activew, activeh);
	setColor(255, 255, 255);
}

void Help::gameSettingsDraw() {
	setColor(0, 0, 0);

	float y = gamelabely;

	for (const auto& line : gamelabellines) {
	    root->titlefont.drawText(line, gamelabelx, y);
	    y += gamelabelh + 10.0f;
	}
}

void Help::modeSettingsDraw() {
	setColor(0, 0, 0);
}


void Help::itemsSettingsDraw() {
	setColor(255, 255, 255);

	for(int i = 0; i < 5; i++) {
		logo[0].draw(logox[0], logoy[0], logow[0], logoh[0]);
		logo[1].draw(logox[1], logoy[1], logow[1], logoh[1]);
		logo[2].draw(logox[2], logoy[2], logow[2], logoh[2]);
		logo[3].draw(logox[3], logoy[3], logow[3], logoh[3]);
		logo[4].draw(logox[4], logoy[4], logow[4], logoh[4]);
	}
}

void Help::controlsSettingsDraw() {
	setColor(0, 0, 0);
	setColor(normalcolor);

	setColor(0, 0, 0);
}

void Help::containerButtonPressed(int x, int y) {
	if(activetab == TAB_GENERAL) {
		gameSettingsPressed(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		modeSettingsPressed(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		itemsSettingsPressed(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsPressed(x, y);
	}
}

void Help::containerButtonReleased(int x, int y) {
	if(activetab == TAB_GENERAL) {
		gameSettingsReleased(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		modeSettingsReleased(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		itemsSettingsReleased(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsReleased(x, y);
	}
}

void Help::containerButtonFocus(int x, int y) {
	if(activetab == TAB_GENERAL) {
		gameSettingsFocus(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		modeSettingsFocus(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		itemsSettingsFocus(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsFocus(x, y);
	}
}

void Help::gameSettingsPressed(int x, int y) {

}

void Help::gameSettingsReleased(int x, int y) {

}

void Help::gameSettingsFocus(int x, int y) {

}

void Help::modeSettingsPressed(int x, int y) {

}

void Help::modeSettingsReleased(int x, int y) {

}

void Help::modeSettingsFocus(int x, int y) {

}

void Help::itemsSettingsPressed(int x, int y) {

}

void Help::itemsSettingsReleased(int x, int y) {

}

void Help::itemsSettingsFocus(int x, int y) {

}

void Help::controlsSettingsPressed(int x, int y) {

}

void Help::controlsSettingsReleased(int x, int y) {

}

void Help::controlsSettingsFocus(int x, int y) {

}

void Help::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
	returnh = root->titlefont.getStringHeight(returntext);
	returnw = root->titlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}

void Help::returnDraw() {
	setColor(255, 255, 255);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->titlefont.drawText(returntext, returnx, returny);
	setColor(0, 0, 0);
}

void Help::forwardButtonSetup() {
//	generaltabbuttonstate = BUTTON_NONE;
	arrowright.loadImage("ArrowsRight2.png");
	forwardbuttonw = arrowright.getWidth();
	forwardbuttonh = arrowright.getHeight();
	forwardbuttonx = (containerx - forwardbuttonw) + containerw + forwardbuttonw;
	forwardbuttony =  containery + (containerh - forwardbuttonh) / 2;
	forwardstate = BUTTON_NONE;
	forwardbutton.set(forwardbuttonx, forwardbuttony, forwardbuttonx + forwardbuttonw, forwardbuttony + forwardbuttonh);
}

void Help::forwardButtonDraw() {
	if(forwardstate == BUTTON_FOCUS) setColor(focuscolor);
	if(forwardstate == BUTTON_PRESSED || forwardstate == BUTTON_PERFORMED || activetab == TAB_ITEMS) setColor(pressedcolor);
	setColor(0, 0, 0);
	gDrawRectangle(forwardbuttonx, forwardbuttony, forwardbuttonw, forwardbuttonh, true);
	setColor(255, 255, 255);
	arrowright.draw(forwardbuttonx, forwardbuttony, forwardbuttonw, forwardbuttonh);
	setColor(normalcolor);
}

void Help::backButtonSetup() {
	arrowleft.loadImage("ArrowsLeft2.png");
	backbuttonw = arrowleft.getWidth();
	backbuttonh = arrowleft.getHeight();
	backbuttonx = containerx - backbuttonw;
	backbuttony = containery + (containerh - backbuttonh) / 2;
	backstate = BUTTON_NONE;
	backbutton.set(backbuttonx, backbuttony, backbuttonx + backbuttonw, backbuttony + backbuttonh);
}

void Help::backButtonDraw() {
	if(backstate == BUTTON_FOCUS) setColor(focuscolor);
	if(backstate == BUTTON_PRESSED || backstate == BUTTON_PERFORMED) setColor(pressedcolor);
	setColor(0, 0, 0);
	gDrawRectangle(backbuttonx, backbuttony, backbuttonw, backbuttonh, true);
	setColor(255, 255, 255);
	arrowleft.draw(backbuttonx, backbuttony, backbuttonw, backbuttonh);
	setColor(normalcolor);
}

std::string Help::getTabTitle() const {
	if(activetab == TAB_GENERAL) return "GAME";
	if(activetab == TAB_LEVEL) return "MODES";
	if(activetab == TAB_ITEMS) return "ITEMS";
	if(activetab == TAB_CONTROLS) return "CONTROLS";
	return "";
}

