/*
 * Options.cpp
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#include <Options.h>
#include <algorithm>
#include "gCanvas.h"
#include "MainMenuCanvas.h"
#include "CreditsMenu.h"

Options::Options(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

Options::~Options() {
}

void Options::setup() {
	containerSetup();
	tabSetup();
	contactSetup();
	sectiontitle = "OPTIONS";
	titlex = (containerw + gametabbuttonw) / 2;
	titley = tabh;
}

void Options::update() {
}

void Options::draw() {
	root->drawMenuBackground(getWidth(), getHeight());
	containerDraw();
	tabDraw();
	if(showContactPanel) {
		contactDraw();
	}
	setColor(255, 255, 255);
	root->titlefont.drawText(sectiontitle, titlex, titley);
	setColor(normalcolor);
}

void Options::contactSetup() {
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

void Options::contactDraw() {
	setColor(0, 0, 0);

	float y = contacty;

	for(const auto& line : contactlines) {
		root->secondtextfont.drawText(line, contactx, y);
		y += contactlineh + 30.0f;
	}
}

void Options::updateScale() {
    uiscale = std::min(getWidth() / 1920.0f, getHeight() / 1080.0f);
}

void Options::keyPressed(int key) {
	//	gLogi("Options") << "keyPressed:" << key;
}

void Options::keyReleased(int key) {
	//	gLogi("Options") << "keyReleased:" << key;
	if(key == G_KEY_ESC) {
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}
}

void Options::charPressed(unsigned int codepoint) {
	//	gLogi("Options") << "charPressed:" << gCodepointToStr(codepoint);
}

void Options::mouseMoved(int x, int y) {
	//	gLogi("Options") << "mouseMoved" << ", x:" << x << ", y:" << y;
	tabButtonFocus(x, y);
	containerButtonFocus(x, y);
}

void Options::mouseDragged(int x, int y, int button) {
	//	gLogi("Options") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void Options::mousePressed(int x, int y, int button) {
	//	gLogi("Options") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	tabButtonPressed(x, y);
	containerButtonPressed(x, y);
}

void Options::mouseReleased(int x, int y, int button) {
	//	gLogi("Options") << "mouseReleased" << ", button:" << button;
	tabButtonReleased(x, y);
	containerButtonReleased(x, y);
}

void Options::mouseScrolled(int x, int y) {
	//	gLogi("Options") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void Options::mouseEntered() {

}

void Options::mouseExited() {

}

void Options::windowResized(int w, int h) {
    updateScale();
    containerSetup();
    tabSetup();
}

void Options::showNotify() {

}

void Options::hideNotify() {

}

void Options::tabSetup() {
	tabw = containerw;
	tabh = getHeight() / 14;
	tabx = containerx;
	taby = containery + containerh - (tabh * 2) - (getHeight() / 30);
	tabcolor.set(54, 126, 127);
	normalcolor.set(45, 50, 70);
	pressedcolor.set(65, 70, 90);
	focuscolor.set(55, 60, 80);
	applyTabButtonSetup();
	resetTabButtonSetup();
	contactTabButtonSetup();
	creditsTabButtonSetup();
	returnSetup();
}

void Options::tabDraw() {
	setColor(normalcolor);
	applyTabButtonDraw();
	resetTabButtonDraw();
	contactTabButtonDraw();
	creditsTabButtonDraw();
	returnDraw();
}

void Options::tabButtonPressed(int x, int y) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}

	if(applytabbutton.contains(x, y)) {
		applytabbuttonstate = BUTTON_PRESSED;
	}

	if(resettabbutton.contains(x, y)) {
		resettabbuttonstate = BUTTON_PRESSED;
	}

	if(contactbutton.contains(x, y)) {
		contactbuttonstate = BUTTON_PRESSED;
	}

	if(creditsbutton.contains(x, y)) {
		creditsbuttonstate = BUTTON_PRESSED;
	}
}

void Options::tabButtonReleased(int x, int y) {
	if(applytabbutton.contains(x, y) && applytabbuttonstate == BUTTON_PRESSED) {
		applytabbuttonstate = BUTTON_PERFORMED;
		applyAudioSettings();
		containerSetup();
		tabSetup();
	}

	else if(resettabbutton.contains(x, y) && resettabbuttonstate == BUTTON_PRESSED) {
		resettabbuttonstate = BUTTON_PERFORMED;
		resetAudioSettings();
	}

	else if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}

	else if(contactbutton.contains(x, y) && contactbuttonstate == BUTTON_PRESSED) {
		contactbuttonstate = BUTTON_PERFORMED;
		showContactPanel = true;
	}

	else if(creditsbutton.contains(x, y) && creditsbuttonstate == BUTTON_PRESSED) {
		creditsbuttonstate = BUTTON_PERFORMED;
		root->setCurrentCanvas(new CreditsMenu(root));
	}

	else {
		applytabbuttonstate = BUTTON_CANCELED;
		resettabbuttonstate = BUTTON_CANCELED;
		returnbuttonstate= BUTTON_CANCELED;
		contactbuttonstate = BUTTON_CANCELED;
		creditsbuttonstate= BUTTON_CANCELED;
	}
}

void Options::tabButtonFocus(int x, int y) {
	if(applytabbuttonstate != BUTTON_PRESSED) {
		if(applytabbutton.contains(x, y)) {
			applytabbuttonstate = BUTTON_FOCUS;
		}
		else {
			applytabbuttonstate = BUTTON_NONE;
		}
	}

	if(resettabbuttonstate != BUTTON_PRESSED) {
		if(resettabbutton.contains(x, y)) {
			resettabbuttonstate = BUTTON_FOCUS;
		}
		else {
			resettabbuttonstate = BUTTON_NONE;
		}
	}

	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}

	if(contactbuttonstate != BUTTON_PRESSED) {
		if(contactbutton.contains(x, y)) {
			contactbuttonstate = BUTTON_FOCUS;
		}
		else {
			contactbuttonstate = BUTTON_NONE;
		}
	}

	if(creditsbuttonstate != BUTTON_PRESSED) {
		if(creditsbutton.contains(x, y)) {
			creditsbuttonstate = BUTTON_FOCUS;
		}
		else {
			creditsbuttonstate = BUTTON_NONE;
		}
	}

}

void Options::containerSetup() {
	backgroundimg.loadImage("UIasset/PNG/SelectPanel01.png");
	returnimg.loadImage("UIasset/PNG/button12.png");
	applyimg.loadImage("UIasset/PNG/button14.png");
	resetimg.loadImage("UIasset/PNG/button13.png");

	contactimg.loadImage("UIasset/PNG/button14.png");
	creditsimg.loadImage("UIasset/PNG/button13.png");

	int width = getWidth();
	int height = getHeight();

	float basecontainerw = 0.42f;
	float basecontainerh = 0.78f;

	containerw = getWidth() * basecontainerw;
	containerh = getHeight() * basecontainerh;

	containerx = (width - containerw) / 2;
	containery = (height - containerh) / 2;

	containercolor.set(255, 255, 255);
	gameSettingsSetup();
}

void Options::gameSettingsSetup() {
	musictickSetup();
	fxtickSetup();
}

void Options::containerDraw() {
	setColor(containercolor);
	backgroundimg.draw(containerx, containery, containerw, containerh);
	gameSettingsDraw();
	setColor(255, 255, 255);
}

void Options::gameSettingsDraw() {
	musictickDraw();
	fxtickDraw();
}

void Options::graphicsSettingsDraw() {
}

void Options::audioSettingsDraw() {
}

void Options::containerButtonPressed(int x, int y) {
	audioSettingsPressed(x, y);
}

void Options::containerButtonReleased(int x, int y) {
	audioSettingsReleased(x, y);
}

void Options::containerButtonFocus(int x, int y) {
	audioSettingsFocus(x, y);
}

void Options::gameSettingsPressed(int x, int y) {
}

void Options::gameSettingsReleased(int x, int y) {
}

void Options::gameSettingsFocus(int x, int y) {
}


void Options::graphicsSettingsPressed(int x, int y) {
}

void Options::graphicsSettingsReleased(int x, int y) {
}

void Options::audioSettingsPressed(int x, int y) {
	if(musicbuttonhitbox.contains(x, y)) {
		musictickstate = BUTTON_PRESSED;
	}

	if(fxbuttonhitbox.contains(x, y)) {
		fxtickstate = BUTTON_PRESSED;
	}
}

void Options::audioSettingsReleased(int x, int y) {
	if(musicbuttonhitbox.contains(x, y) && musictickstate == BUTTON_PRESSED) {
	    musictickstate = BUTTON_PERFORMED;
	    ismusicenabled = !ismusicenabled;
	}
	else if(fxbuttonhitbox.contains(x, y) && fxtickstate == BUTTON_PRESSED) {
	    fxtickstate = BUTTON_PERFORMED;
	    isfxenabled = !isfxenabled;
	}
	else {
		musictickstate = BUTTON_CANCELED;
		fxtickstate = BUTTON_CANCELED;
	}

}

void Options::audioSettingsFocus(int x, int y) {
}

void Options::returnSetup() {
	returntext = root->returnkey;
	returnh = root->titlefont.getStringHeight(returntext);
	returnw = root->titlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}

void Options::returnDraw() {
	setColor(255, 255, 255);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	returnimg.draw(returnx, returny - 40, 200, 50);
	root->titlefont.drawText(returntext, returnx, returny);
	setColor(0, 0, 0);
}

void Options::applyTabButtonSetup() {
	applytabtext = "APPLY";
	applytabbuttonstate = BUTTON_NONE;
	applytabbuttonh = tabh;
	applytabbuttonw = (tabw - (tabw * 0.08)) / 2;
	applytabbuttonx = containerx;
	applytabbuttony = containery + containerh - applytabbuttonh - (containerh * 0.05) + 30;
	applytabbutton.set(applytabbuttonx, applytabbuttony, applytabbuttonx + applytabbuttonw, applytabbuttony + applytabbuttonh);
}

void Options::resetTabButtonSetup() {
	resettabtext = "RESET";
	resettabbuttonstate = BUTTON_NONE;
	resettabbuttonh = tabh;
	resettabbuttonw = (tabw - (tabw * 0.08)) / 2;
	resettabbuttonx = applytabbuttonx + applytabbuttonw + (tabw * 0.085);
	resettabbuttony = applytabbuttony;
	resettabbutton.set(resettabbuttonx, resettabbuttony, resettabbuttonx + resettabbuttonw, resettabbuttony + resettabbuttonh);
}

void Options::contactTabButtonSetup() {
	contacttext = "Contact";
	contactbuttonstate = BUTTON_NONE;
	contacttabbuttonh = tabh;
	contacttabbuttonw = (tabw - (tabw * 0.08)) / 2;
	contacttabbuttonx = containerx;
	contacttabbuttony = containery;
	contactbutton.set(contacttabbuttonx, contacttabbuttony, contacttabbuttonx + contacttabbuttonw, contacttabbuttony + contacttabbuttonh);
}

void Options::creditsTabButtonSetup() {
	creditstext = "Credits";
	creditsbuttonstate = BUTTON_NONE;
	creditstabbuttonh = tabh;
	creditstabbuttonw = (tabw - (tabw * 0.08)) / 2;
	creditstabbuttonx = contacttabbuttonx + contacttabbuttonw + (tabw * 0.085);
	creditstabbuttony = contacttabbuttony;
	creditsbutton.set(creditstabbuttonx, creditstabbuttony, creditstabbuttonx + creditstabbuttonw, creditstabbuttony + creditstabbuttonh);
}


void Options::applyTabButtonDraw() {
	if(applytabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(applytabbuttonstate == BUTTON_PRESSED || applytabbuttonstate == BUTTON_PERFORMED || activetab == TAB_APPLY) setColor(pressedcolor);
	applyimg.draw(applytabbuttonx, applytabbuttony, applytabbuttonw, applytabbuttonh);
	tabfontw = root->secondtextfont.getStringWidth(applytabtext);
	tabfonth = root->secondtextfont.getStringHeight(applytabtext);
	tabfontx = applytabbuttonx + (applytabbuttonw - tabfontw) / 2;
	tabfonty = applytabbuttony + (applytabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->thirdtextfont.drawText(applytabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void Options::resetTabButtonDraw() {
	if(resettabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(resettabbuttonstate == BUTTON_PRESSED || resettabbuttonstate == BUTTON_PERFORMED || activetab == TAB_RESET) setColor(pressedcolor);
	resetimg.draw(resettabbuttonx, resettabbuttony, resettabbuttonw, resettabbuttonh);
	tabfontw = root->secondtextfont.getStringWidth(resettabtext);
	tabfonth = root->secondtextfont.getStringHeight(resettabtext);
	tabfontx = resettabbuttonx + (resettabbuttonw - tabfontw) / 2;
	tabfonty = resettabbuttony + (resettabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->thirdtextfont.drawText(resettabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void Options::contactTabButtonDraw() {
	if(contactbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(contactbuttonstate == BUTTON_PRESSED || contactbuttonstate == BUTTON_PERFORMED || activetab == TAB_CONTACT) setColor(pressedcolor);
	contactimg.draw(contacttabbuttonx, contacttabbuttony, contacttabbuttonw, contacttabbuttonh);
	tabfontw = root->secondtextfont.getStringWidth(contacttext);
	tabfonth = root->secondtextfont.getStringHeight(contacttext);
	tabfontx = contacttabbuttonx + (contacttabbuttonw - tabfontw) / 2;
	tabfonty = contacttabbuttony + (contacttabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->thirdtextfont.drawText(contacttext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void Options::creditsTabButtonDraw() {
	if(creditsbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(creditsbuttonstate == BUTTON_PRESSED || creditsbuttonstate == BUTTON_PERFORMED || activetab == TAB_CREDITS) setColor(pressedcolor);
	creditsimg.draw(creditstabbuttonx, creditstabbuttony, creditstabbuttonw, creditstabbuttonh);
	tabfontw = root->secondtextfont.getStringWidth(creditstext);
	tabfonth = root->secondtextfont.getStringHeight(creditstext);
	tabfontx = creditstabbuttonx + (creditstabbuttonw - tabfontw) / 2;
	tabfonty = creditstabbuttony + (creditstabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->thirdtextfont.drawText(creditstext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void Options::musictickSetup() {
	musictext = "Music";
	musicuncheck.loadImage("UIasset/PNG/button02.png");
	musiccheck.loadImage("check-markred.png");
	musictextw = root->secondtextfont.getStringWidth(musictext);
	musictexth = root->secondtextfont.getStringHeight(musictext);
	musictextx = containerx + (containerw * 0.10);
	musictexty = containery + containerh * 0.25f;
	musicuncheckw = musicuncheck.getWidth() * 0.5;
	musicuncheckh = musicuncheck.getHeight() * 0.5;
	musicuncheckx = containerx + (containerw * 0.55);
	musicunchecky = musictexty - (musictexth / 2) - (musicuncheckh / 2) + 3;
	musiccheckw = musiccheck.getWidth() * 0.06;
	musiccheckh = musiccheck.getHeight() * 0.06;
	musicbuttonhitbox.set(musicuncheckx, musicunchecky, musicuncheckx + musicuncheckw, musicunchecky + musicuncheckh);
	ismusicenabled = root->getMusic();
}

void Options::fxtickSetup() {
	fxtext = "FX Sound";
	fxuncheck.loadImage("UIasset/PNG/button02.png");
	fxcheck.loadImage("check-markred.png");
	fxtextw = root->secondtextfont.getStringWidth(fxtext);
	fxtexth = root->secondtextfont.getStringHeight(fxtext);
	fxtextx = containerx + (containerw * 0.10);
	fxtexty = musictexty + (containerh / 10);
	fxuncheckw = fxuncheck.getWidth() * 0.5;
	fxuncheckh = fxuncheck.getHeight() * 0.5;
	fxuncheckx = containerx + (containerw * 0.55);
	fxunchecky = fxtexty - (fxtexth / 2) - (fxuncheckh / 2) + 3;
	fxcheckw = fxcheck.getWidth() * 0.06;
	fxcheckh = fxcheck.getHeight() * 0.06;
	fxbuttonhitbox.set(fxuncheckx, fxunchecky, fxuncheckx + fxuncheckw, fxunchecky + fxuncheckh);
	isfxenabled = root->getSound();
}

void Options::musictickDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(musictext, musictextx, musictexty);
	musicuncheck.draw(musicuncheckx, musicunchecky, musicuncheckw, musicuncheckh);
	if(ismusicenabled) {
		setColor(255, 255, 255);
		musiccheck.draw(musicuncheckx, musicunchecky, musiccheckw, musiccheckh);
	}
	setColor(0, 0, 0);
}

void Options::fxtickDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(fxtext, fxtextx, fxtexty);
	fxuncheck.draw(fxuncheckx, fxunchecky, fxuncheckw, fxuncheckh);
	if(isfxenabled) {
		setColor(255, 255, 255);
		fxcheck.draw(fxuncheckx, fxunchecky, fxcheckw, fxcheckh);
	}
	setColor(0, 0, 0);
}

void Options::applyAudioSettings() {
	root->saveAudioSettings(isfxenabled, ismusicenabled);
}

void Options::resetAudioSettings() {
	isfxenabled = root->getSound();
	ismusicenabled = root->getMusic();
	containerSetup();
	tabSetup();
}
