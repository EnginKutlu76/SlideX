/*
 * Options.cpp
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#include <Options.h>
#include "gCanvas.h"
#include "MainMenuCanvas.h"

Options::Options(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

Options::~Options() {
}

void Options::setup() {
	containerSetup();
	tabSetup();
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
	setColor(255, 255, 255);
	root->titlefont.drawText(sectiontitle, titlex, titley);
	setColor(normalcolor);
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
	returnSetup();
}

void Options::tabDraw() {
	setColor(normalcolor);
	applyTabButtonDraw();
	resetTabButtonDraw();
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
}

void Options::tabButtonReleased(int x, int y) {
	if(applytabbutton.contains(x, y) && applytabbuttonstate == BUTTON_PRESSED) {
		applytabbuttonstate = BUTTON_PERFORMED;
		applyGameSettings();
		applyGraphicsSettings();
		applyAudioSettings();
	}

	else if(resettabbutton.contains(x, y) && resettabbuttonstate == BUTTON_PRESSED) {
		resettabbuttonstate = BUTTON_PERFORMED;
		resetGameSettings();
		resetGraphicsSettings();
		resetAudioSettings();
	}

	else if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		root->setCurrentCanvas(new MainMenuCanvas(root));
	}

	else {
		applytabbuttonstate = BUTTON_CANCELED;
		resettabbuttonstate = BUTTON_CANCELED;
		returnbuttonstate= BUTTON_CANCELED;
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
}

void Options::containerSetup() {
	int width = getWidth();
	int height = getHeight();

	containerw = width * 0.42;
	containerh = height * 0.78;
	containerx = (width - containerw) / 2;
	containery = (height - containerh) / 2;

	containercolor.set(255, 255, 255);
	gameSettingsSetup();
}

void Options::gameSettingsSetup() {
	languageSetup();
	fpsSetup();
	vsyncSetup();
	windowmodeSetup();
	musicSetup();
	fxSetup();
	musictickSetup();
	fxtickSetup();
}

void Options::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);
	gameSettingsDraw();
	setColor(255, 255, 255);
}

void Options::gameSettingsDraw() {
	languageDraw();
	fpsDraw();
	vsyncDraw();
	windowmodeDraw();
	musicDraw();
	fxDraw();
	musictickDraw();
	fxtickDraw();
}

void Options::graphicsSettingsDraw() {
}

void Options::audioSettingsDraw() {
}

void Options::containerButtonPressed(int x, int y) {
	gameSettingsPressed(x, y);
	graphicsSettingsPressed(x, y);
	audioSettingsPressed(x, y);
}

void Options::containerButtonReleased(int x, int y) {
	gameSettingsReleased(x, y);
	graphicsSettingsReleased(x, y);
	audioSettingsReleased(x, y);
}

void Options::containerButtonFocus(int x, int y) {
	gameSettingsFocus(x, y);
	graphicsSettingsFocus(x, y);
	audioSettingsFocus(x, y);
}

void Options::gameSettingsPressed(int x, int y) {
	if(langbackbuttonhitbox.contains(x, y)) {
		langbackstate = BUTTON_PRESSED;
	}

	if(langforwardbuttonhitbox.contains(x, y)) {
		langfwstate = BUTTON_PRESSED;
	}

	if(fpsbuttonhitbox.contains(x, y)) {
		fpstickstate = BUTTON_PRESSED;
	}

	if(vsyncbuttonhitbox.contains(x, y)) {
		vsynctickstate = BUTTON_PRESSED;
	}
}

void Options::gameSettingsReleased(int x, int y) {
	if(langbackbuttonhitbox.contains(x, y) && langbackstate == BUTTON_PRESSED) {
		langbackstate = BUTTON_PERFORMED;
		selectedlanguage--;
		if(selectedlanguage < 0) selectedlanguage = languagenum - 1;
	}

	else if(langforwardbuttonhitbox.contains(x, y) && langfwstate == BUTTON_PRESSED) {
		langfwstate = BUTTON_PERFORMED;
		selectedlanguage++;
		if(selectedlanguage >= languagenum) selectedlanguage = 0;
	}

	else if(fpsbuttonhitbox.contains(x, y) && fpstickstate == BUTTON_PRESSED) {
	    fpstickstate = BUTTON_PERFORMED;
	    isfpsenabled = !isfpsenabled;
	}

	else if(vsyncbuttonhitbox.contains(x, y) && vsynctickstate == BUTTON_PRESSED) {
		vsynctickstate = BUTTON_PERFORMED;
	    isvsyncenabled = !isvsyncenabled;
	}

	else {
		langbackstate = BUTTON_CANCELED;
		langfwstate = BUTTON_CANCELED;
		fpstickstate = BUTTON_CANCELED;
		vsynctickstate = BUTTON_CANCELED;
	}

}

void Options::gameSettingsFocus(int x, int y) {
	if(langbackstate != BUTTON_PRESSED) {
		if(langbackbuttonhitbox.contains(x, y)) {
			langbackstate = BUTTON_FOCUS;
		}

		else {
			langbackstate = BUTTON_NONE;
		}
	}

	if(langfwstate != BUTTON_PRESSED) {
		if(langforwardbuttonhitbox.contains(x, y)) {
			langfwstate = BUTTON_FOCUS;
		}

		else {
			langfwstate = BUTTON_NONE;
		}
	}

	if(fpstickstate != BUTTON_PRESSED) {
		if(fpsbuttonhitbox.contains(x, y)) {
			fpstickstate = BUTTON_FOCUS;
		}

		else {
			fpstickstate = BUTTON_NONE;
		}
	}

	if(vsynctickstate != BUTTON_PRESSED) {
		if(vsyncbuttonhitbox.contains(x, y)) {
			vsynctickstate = BUTTON_FOCUS;
		}

		else {
			vsynctickstate = BUTTON_NONE;
		}
	}
}


void Options::graphicsSettingsPressed(int x, int y) {
	if(winbackbuttonhitbox.contains(x, y)) {
		winbackstate = BUTTON_PRESSED;
	}

	if(winforwardbuttonhitbox.contains(x, y)) {
		winfwstate = BUTTON_PRESSED;
	}
}

void Options::graphicsSettingsReleased(int x, int y) {
	if(winbackbuttonhitbox.contains(x, y) && winbackstate == BUTTON_PRESSED) {
		winbackstate = BUTTON_PERFORMED;
		selectedwindowmode--;
		if(selectedwindowmode < 0) selectedwindowmode = windowmodenum - 1;
	}

	else if(winforwardbuttonhitbox.contains(x, y) && winfwstate == BUTTON_PRESSED) {
		winfwstate = BUTTON_PERFORMED;
		selectedwindowmode++;
		if(selectedwindowmode >= windowmodenum) selectedwindowmode = 0;
	}
	else {
		winbackstate = BUTTON_CANCELED;
		winfwstate = BUTTON_CANCELED;
	}

}

void Options::graphicsSettingsFocus(int x, int y) {
	if(winbackstate != BUTTON_PRESSED) {
		if(winbackbuttonhitbox.contains(x, y)) {
			winbackstate = BUTTON_FOCUS;
		}

		else {
			winbackstate = BUTTON_NONE;
		}
	}

	if(winfwstate != BUTTON_PRESSED) {
		if(winforwardbuttonhitbox.contains(x, y)) {
			winfwstate = BUTTON_FOCUS;
		}

		else {
			winfwstate = BUTTON_NONE;
		}
	}
}

void Options::audioSettingsPressed(int x, int y) {
	if(musicbackstate != BUTTON_PRESSED) {
		if(musicbackbuttonhitbox.contains(x, y)) {
			musicbackstate = BUTTON_PRESSED;
		}
		else {
			musicbackstate = BUTTON_NONE;
		}
	}

	if(musicfwstate != BUTTON_PRESSED) {
		if(musicforwardbuttonhitbox.contains(x, y)) {
			musicfwstate = BUTTON_PRESSED;
		}
		else {
			musicfwstate = BUTTON_NONE;
		}
	}

	if(fxbackstate != BUTTON_PRESSED) {
		if(fxbackbuttonhitbox.contains(x, y)) {
			fxbackstate = BUTTON_PRESSED;
		}
		else {
			fxbackstate = BUTTON_NONE;
		}
	}

	if(fxfwstate != BUTTON_PRESSED) {
		if(fxforwardbuttonhitbox.contains(x, y)) {
			fxfwstate = BUTTON_PRESSED;
		}
		else {
			fxfwstate = BUTTON_NONE;
		}
	}

	if(musicbuttonhitbox.contains(x, y)) {
		musictickstate = BUTTON_PRESSED;
	}

	if(fxbuttonhitbox.contains(x, y)) {
		fxtickstate = BUTTON_PRESSED;
	}
}

void Options::audioSettingsReleased(int x, int y) {
	if(musicbackbuttonhitbox.contains(x, y) && musicbackstate == BUTTON_PRESSED) {
		musicbackstate = BUTTON_PERFORMED;
		if(musicvalue >= 5) musicvalue -= 5;
		musicnumtext = gToStr(musicvalue);
	}
	else if(musicforwardbuttonhitbox.contains(x, y) && musicfwstate == BUTTON_PRESSED) {
		musicfwstate = BUTTON_PERFORMED;
		if(musicvalue < 100) musicvalue += 5;
		musicnumtext = gToStr(musicvalue);
	}
	else if(fxbackbuttonhitbox.contains(x, y) && fxbackstate == BUTTON_PRESSED) {
		fxbackstate = BUTTON_PERFORMED;
		if(effectvalue >= 5) effectvalue -= 5;
		fxnumtext = gToStr(effectvalue);
	}
	else if(fxforwardbuttonhitbox.contains(x, y) && fxfwstate == BUTTON_PRESSED) {
		fxfwstate = BUTTON_PERFORMED;
		if(effectvalue < 100) effectvalue += 5;
		fxnumtext = gToStr(effectvalue);
	}
	else if(musicbuttonhitbox.contains(x, y) && musictickstate == BUTTON_PRESSED) {
	    musictickstate = BUTTON_PERFORMED;
	    ismusicenabled = !ismusicenabled;
	}
	else if(fxbuttonhitbox.contains(x, y) && fxtickstate == BUTTON_PRESSED) {
	    fxtickstate = BUTTON_PERFORMED;
	    isfxenabled = !isfxenabled;
	}
	else {
		musicbackstate = BUTTON_CANCELED;
		musicfwstate = BUTTON_CANCELED;
		fxbackstate = BUTTON_CANCELED;
		fxfwstate = BUTTON_CANCELED;
		musictickstate = BUTTON_CANCELED;
		fxtickstate = BUTTON_CANCELED;
	}

}

void Options::audioSettingsFocus(int x, int y) {
	if(musicbackstate != BUTTON_PRESSED) {
		if(musicbackbuttonhitbox.contains(x, y)) {
			musicbackstate = BUTTON_FOCUS;
		}

		else {
			musicbackstate = BUTTON_NONE;
		}
	}

	if(musicfwstate != BUTTON_PRESSED) {
		if(musicforwardbuttonhitbox.contains(x, y)) {
			musicfwstate = BUTTON_FOCUS;
		}

		else {
			musicfwstate = BUTTON_NONE;
		}
	}
	if(fxbackstate != BUTTON_PRESSED) {
		if(fxbackbuttonhitbox.contains(x, y)) {
			fxbackstate = BUTTON_FOCUS;
		}

		else {
			fxbackstate = BUTTON_NONE;
		}
	}

	if(fxfwstate != BUTTON_PRESSED) {
		if(fxforwardbuttonhitbox.contains(x, y)) {
			fxfwstate = BUTTON_FOCUS;
		}

		else {
			fxfwstate = BUTTON_NONE;
		}
	}
}

void Options::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
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

void Options::applyTabButtonDraw() {
	if(applytabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(applytabbuttonstate == BUTTON_PRESSED || applytabbuttonstate == BUTTON_PERFORMED || activetab == TAB_APPLY) setColor(pressedcolor);
	gDrawRectangle(applytabbuttonx, applytabbuttony, applytabbuttonw, applytabbuttonh, true);
	tabfontw = root->secondtextfont.getStringWidth(applytabtext);
	tabfonth = root->secondtextfont.getStringHeight(applytabtext);
	tabfontx = applytabbuttonx + (applytabbuttonw - tabfontw) / 2;
	tabfonty = applytabbuttony + (applytabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->secondtextfont.drawText(applytabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void Options::resetTabButtonDraw() {
	if(resettabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(resettabbuttonstate == BUTTON_PRESSED || resettabbuttonstate == BUTTON_PERFORMED || activetab == TAB_RESET) setColor(pressedcolor);
	gDrawRectangle(resettabbuttonx, resettabbuttony, resettabbuttonw, resettabbuttonh, true);
	tabfontw = root->secondtextfont.getStringWidth(resettabtext);
	tabfonth = root->secondtextfont.getStringHeight(resettabtext);
	tabfontx = resettabbuttonx + (resettabbuttonw - tabfontw) / 2;
	tabfonty = resettabbuttony + (resettabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->secondtextfont.drawText(resettabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void Options::languageSetup() {
	languagelabeltext = "Language: ";
	languages[0] = "English";
	languages[1] = "Turkish";
	langbackbutton.loadImage("ArrowsLeft2.png");
	langforwardbutton.loadImage("ArrowsRight2.png");

	selectedlanguage = root->getLanguage();

	languagelabelh = root->secondtextfont.getStringHeight("y");
	languagelabelx = containerx + (containerw * 0.10);
	languagelabely = containery + (containerh * 0.12) + languagelabelh;

	languagesw = root->secondtextfont.getStringWidth(languages[selectedlanguage]);
	languagesh = root->secondtextfont.getStringHeight(languages[selectedlanguage]);
	languagesx = containerx + (containerw * 0.55);

	langbackbuttonw = langbackbutton.getWidth() * 0.4;
	langbackbuttonh = langbackbutton.getHeight() * 0.4;
	langbackbuttonx = languagesx - langbackbuttonw - 10;
	langbackbuttony = languagelabely - (languagesh / 2) - (langbackbuttonh / 2) + 3;
	langforwardbuttonx = languagesx + languagesw + 10;
	langbackbuttonhitbox.set(langbackbuttonx, langbackbuttony, langbackbuttonx + langbackbuttonw, langbackbuttony + langbackbuttonh);
	langforwardbuttonhitbox.set(langforwardbuttonx, langbackbuttony, langforwardbuttonx + langbackbuttonw, langbackbuttony + langbackbuttonh);
}

void Options::fpsSetup() {
	fpstext = "Show Fps";
	isfpsenabled = root->getShowFps();
	fpsuncheck.loadImage("inactivecolor.png");
	fpscheck.loadImage("check-markred.png");
	fpstextw = root->secondtextfont.getStringWidth(fpstext);
	fpstexth = root->secondtextfont.getStringHeight(fpstext);
	fpstextx = languagelabelx;
	fpstexty = languagelabely + (containerh / 10);
	fpsuncheckw = fpsuncheck.getWidth();
	fpsuncheckh = fpsuncheck.getHeight();
	fpsuncheckx = containerx + (containerw * 0.55);
	fpsunchecky = fpstexty - (fpstexth / 2) - (fpsuncheckh / 2) + 3;
	fpscheckw = fpscheck.getWidth() * 0.06;
	fpscheckh = fpscheck.getHeight() * 0.06;
	fpsbuttonhitbox.set(fpsuncheckx, fpsunchecky, fpsuncheckx + fpsuncheckw, fpsunchecky + fpsuncheckh);
}

void Options::vsyncSetup() {
	vsynctext = "VSync";
	vsyncuncheck.loadImage("inactivecolor.png");
	vsynccheck.loadImage("check-markred.png");
	vsynctextw = root->secondtextfont.getStringWidth(vsynctext);
	vsynctexth = root->secondtextfont.getStringHeight(vsynctext);
	vsynctextx = languagelabelx;
	vsynctexty = fpstexty + (containerh / 10);
	vsyncuncheckw = vsyncuncheck.getWidth();
	vsyncuncheckh = vsyncuncheck.getHeight();
	vsyncuncheckx = fpsuncheckx;
	vsyncunchecky = vsynctexty - (vsynctexth / 2) - (vsyncuncheckh / 2) + 3;
	vsynccheckw = vsynccheck.getWidth() * 0.06;
	vsynccheckh = vsynccheck.getHeight() * 0.06;
	vsyncbuttonhitbox.set(vsyncuncheckx, vsyncunchecky, vsyncuncheckx + vsyncuncheckw, vsyncunchecky + vsyncuncheckh);
	isvsyncenabled = root->getVsync();
}

void Options::languageDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(languagelabeltext, languagelabelx, languagelabely);
	root->secondtextfont.drawText(languages[selectedlanguage], languagesx, languagelabely);

	if(langbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(langbackstate == BUTTON_PRESSED || langbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	langbackbutton.draw(langbackbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh);

	if(langfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(langfwstate == BUTTON_PRESSED || langfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	langforwardbutton.draw(langforwardbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh);

	setColor(0, 0, 0);
}

void Options::fpsDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(fpstext, fpstextx, fpstexty);
	fpsuncheck.draw(fpsuncheckx, fpsunchecky);
	if(isfpsenabled) {
		setColor(255, 255, 255);
	    fpscheck.draw(fpsuncheckx, fpsunchecky, fpscheckw, fpscheckh);
	}
	setColor(0, 0, 0);
}

void Options::vsyncDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(vsynctext, vsynctextx, vsynctexty);
	vsyncuncheck.draw(vsyncuncheckx, vsyncunchecky);
	if(isvsyncenabled) {
		setColor(255, 255, 255);
		vsynccheck.draw(vsyncuncheckx, vsyncunchecky, vsynccheckw, vsynccheckh);
	}
	setColor(0, 0, 0);
}

void Options::windowmodeSetup() {
	windowmodelabeltext = "Window Mode: ";
	windowmodes[0] = "FullScreen";
	windowmodes[1] = "Borderless";
	windowmodes[2] = "Windowed";
	winbackbutton.loadImage("ArrowsLeft2.png");
	winforwardbutton.loadImage("ArrowsRight2.png");

	selectedwindowmode = root->getWindowMode();

	winlabelh = root->secondtextfont.getStringHeight("y");
	winlabelx = containerx + (containerw * 0.10);
	winlabely = vsynctexty + (containerh / 10);

	windowmodesw = root->secondtextfont.getStringWidth(windowmodes[selectedwindowmode]);
	windowmodesh = root->secondtextfont.getStringHeight(windowmodes[selectedwindowmode]);
	windowmodesx = containerx + (containerw * 0.55);

	winbackbuttonw = winbackbutton.getWidth() * 0.4;
	winbackbuttonh = winbackbutton.getHeight() * 0.4;
	winbackbuttonx = windowmodesx - winbackbuttonw - 10;
	winbackbuttony = winlabely - (windowmodesh / 2) - (winbackbuttonh / 2) + 3;
	winforwardbuttonx = windowmodesx + windowmodesw + 10;
	winbackbuttonhitbox.set(winbackbuttonx, winbackbuttony, winbackbuttonx + winbackbuttonw, winbackbuttony + winbackbuttonh);
	winforwardbuttonhitbox.set(winforwardbuttonx, winbackbuttony, winforwardbuttonx + winbackbuttonw, winbackbuttony + winbackbuttonh);
}

void Options::windowmodeDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(windowmodelabeltext, winlabelx, winlabely);
	root->secondtextfont.drawText(windowmodes[selectedwindowmode], windowmodesx, winlabely);
	winbackbutton.draw(winbackbuttonx, winbackbuttony, winbackbuttonw, winbackbuttonh);
	winforwardbutton.draw(winforwardbuttonx, winbackbuttony, winbackbuttonw, winbackbuttonh);
	setColor(0, 0, 0);
}

void Options::musicSetup() {
	musicbackbutton.loadImage("ArrowsLeft2.png");
	musicforwardbutton.loadImage("ArrowsRight2.png");

	musicvalue = root->getMusicVolume();

	musicnumtext = gToStr(musicvalue);
	musiclabeltext = "Music Value";
	musiclabelh = root->secondtextfont.getStringHeight("y");
	musiclabelx = containerx + (containerw * 0.10);
	musiclabely = winlabely + (containerh / 10);
	musicw = root->secondtextfont.getStringWidth(musicnumtext);
	musicx = containerx + (containerw * 0.55);
	musich = root->secondtextfont.getStringHeight(musicnumtext);
	musicbackbuttonw = musicbackbutton.getWidth() * 0.4;
	musicbackbuttonh = musicbackbutton.getHeight() * 0.4;
	musicbackbuttonx = musicx - musicbackbuttonw - 10;
	musicbackbuttony = musiclabely - (musich / 2) - (musicbackbuttonh / 2) +  3;
	musicforwardbuttonx = musicx + musicw + 10;
	musicbackbuttonhitbox.set(musicbackbuttonx, musicbackbuttony, musicbackbuttonx + musicbackbuttonw, musicbackbuttony + musicbackbuttonh);
	musicforwardbuttonhitbox.set(musicforwardbuttonx, musicbackbuttony, musicforwardbuttonx + musicbackbuttonw, musicbackbuttony + musicbackbuttonh);
}

void Options::fxSetup() {
	fxbackbutton.loadImage("ArrowsLeft2.png");
	fxforwardbutton.loadImage("ArrowsRight2.png");

	effectvalue = root->getSoundVolume();

	fxnumtext = gToStr(effectvalue);
	fxlabeltext = "Effect Value";
	fxlabelh = root->secondtextfont.getStringHeight("y");
	fxlabelx = containerx + (containerw * 0.10);
	fxlabely = musiclabely + (containerh / 10);
	fxw = root->secondtextfont.getStringWidth(fxnumtext);
	fxx = containerx + (containerw * 0.55);
	fxh = root->secondtextfont.getStringHeight(fxnumtext);
	fxbackbuttonw = fxbackbutton.getWidth() * 0.4;
	fxbackbuttonh = fxbackbutton.getHeight() * 0.4;
	fxbackbuttonx = fxx - fxbackbuttonw - 10;
	fxbackbuttony = fxlabely - (fxh / 2) - (fxbackbuttonh / 2) +  3;
	fxforwardbuttonx = fxx + fxw + 10;
	fxbackbuttonhitbox.set(fxbackbuttonx, fxbackbuttony, fxbackbuttonx + fxbackbuttonw, fxbackbuttony + fxbackbuttonh);
	fxforwardbuttonhitbox.set(fxforwardbuttonx, fxbackbuttony, fxforwardbuttonx + fxbackbuttonw, fxbackbuttony + fxbackbuttonh);
}

void Options::musicDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(musiclabeltext, musiclabelx, musiclabely);

	if(musicbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(musicbackstate == BUTTON_PRESSED || musicbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	musicbackbutton.draw(musicbackbuttonx, musicbackbuttony, musicbackbuttonw, musicbackbuttonh);

	setColor(0, 0, 0);
	if(musicfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(musicfwstate == BUTTON_PRESSED || musicfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	musicforwardbutton.draw(musicforwardbuttonx, musicbackbuttony, musicbackbuttonw, musicbackbuttonh);

	setColor(0, 0, 0);
	root->secondtextfont.drawText(musicnumtext, musicx, musiclabely);
}

void Options::fxDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(fxlabeltext, fxlabelx, fxlabely);

	if(fxbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(fxbackstate == BUTTON_PRESSED || fxbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	fxbackbutton.draw(fxbackbuttonx, fxbackbuttony, fxbackbuttonw, fxbackbuttonh);

	setColor(0, 0, 0);
	if(fxfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(fxfwstate == BUTTON_PRESSED || fxfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	fxforwardbutton.draw(fxforwardbuttonx, fxbackbuttony, fxbackbuttonw, fxbackbuttonh);

	setColor(0, 0, 0);
	root->secondtextfont.drawText(fxnumtext, fxx, fxlabely);
}

void Options::musictickSetup() {
	musictext = "Music";
	musicuncheck.loadImage("inactivecolor.png");
	musiccheck.loadImage("check-markred.png");
	musictextw = root->secondtextfont.getStringWidth(musictext);
	musictexth = root->secondtextfont.getStringHeight(musictext);
	musictextx = containerx + (containerw * 0.10);
	musictexty = fxlabely + (containerh / 10);
	musicuncheckw = musicuncheck.getWidth();
	musicuncheckh = musicuncheck.getHeight();
	musicuncheckx = containerx + (containerw * 0.55);
	musicunchecky = musictexty - (musictexth / 2) - (musicuncheckh / 2) + 3;
	musiccheckw = musiccheck.getWidth() * 0.06;
	musiccheckh = musiccheck.getHeight() * 0.06;
	musicbuttonhitbox.set(musicuncheckx, musicunchecky, musicuncheckx + musicuncheckw, musicunchecky + musicuncheckh);
	ismusicenabled = root->getMusicVolume();
}

void Options::fxtickSetup() {
	fxtext = "FX Sound";
	fxuncheck.loadImage("inactivecolor.png");
	fxcheck.loadImage("check-markred.png");
	fxtextw = root->secondtextfont.getStringWidth(fxtext);
	fxtexth = root->secondtextfont.getStringHeight(fxtext);
	fxtextx = containerx + (containerw * 0.10);
	fxtexty = musictexty + (containerh / 10);
	fxuncheckw = fxuncheck.getWidth();
	fxuncheckh = fxuncheck.getHeight();
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
	musicuncheck.draw(musicuncheckx, musicunchecky);
	if(ismusicenabled) {
		setColor(255, 255, 255);
		musiccheck.draw(musicuncheckx, musicunchecky, musiccheckw, musiccheckh);
	}
	setColor(0, 0, 0);
}

void Options::fxtickDraw() {
	setColor(0, 0, 0);
	root->secondtextfont.drawText(fxtext, fxtextx, fxtexty);
	fxuncheck.draw(fxuncheckx, fxunchecky);
	if(isfxenabled) {
		setColor(255, 255, 255);
		fxcheck.draw(fxuncheckx, fxunchecky, fxcheckw, fxcheckh);
	}
	setColor(0, 0, 0);
}

void Options::applyGameSettings() {
	root->saveGameSettings(selectedlanguage, isvsyncenabled, isfpsenabled);
	root->applyGameSettings();
	containerSetup();
	tabSetup();
}

void Options::resetGameSettings() {
	root->resetGameSettings();
	selectedlanguage = root->getLanguage();
	isfpsenabled = root->getShowFps();
	isvsyncenabled = root->getVsync();
	containerSetup();
	tabSetup();
}

void Options::applyGraphicsSettings() {
	root->saveGraphicsSettings(selectedwindowmode);
	root->applyGraphicsSettings();
	containerSetup();
	tabSetup();
}

void Options::resetGraphicsSettings() {
	root->resetGraphicsSettings();
	selectedwindowmode = root->getWindowMode();
	containerSetup();
	tabSetup();
}

void Options::applyAudioSettings() {
	root->saveAudioSettings(effectvalue, musicvalue, isfxenabled, ismusicenabled);
	root->applyAudioSettings();
	containerSetup();
	tabSetup();
}

void Options::resetAudioSettings() {
	root->resetAudioSettings();
	effectvalue = root->getSoundVolume();
	musicvalue = root->getMusicVolume();
	isfxenabled = root->getSound();
	ismusicenabled = root->getMusic();
	containerSetup();
	tabSetup();
}
