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

Options::Options(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

Options::~Options() {
}

void Options::setup() {
	buttonsound.loadSound("effectsound/menubuttons.wav");
	optionsound.loadSound("effectsound/optionbuttons.wav");

	backgroundSetup();
	containerSetup();
	tabSetup();
	contactSetup();
	creditsSetup();
	titleSetup();
}

void Options::update() {
	if(root->getSound() == 1) {
		buttonsound.setVolume(0.5f);
		optionsound.setVolume(0.5f);
	}
	if(root->getSound() == 0) {
		buttonsound.setVolume(0.0f);
		optionsound.setVolume(0.0f);
	}
}

void Options::draw() {
	backgroundDraw();
	setColor(containercolor);
	audioSettingsDraw();
	setColor(255, 255, 255);
	tabDraw();
	titleDraw();
	if(showcontactpanel) {
		contactDraw();
	}

	if(showcreditspanel) {
		creditsDraw();
	}
	setColor(255, 255, 255);
	root->titlefont.drawText(sectiontitle, (getScreenWidth() - root->titlefont.getStringWidth(sectiontitle)) / 2, (root->titlefont.getStringHeight(sectiontitle)) / 2);
	setColor(normalcolor);
}

void Options::backgroundSetup() {
	background.loadImage("Interface/Card X1/Card X2.png");
	bgw = background.getWidth();
	bgh = background.getHeight() * 0.80;
	bgx = (getWidth() - bgw) / 2;
	bgy = (getHeight() - bgh) / 2;
}

void Options::backgroundDraw() {
	background.draw(bgx, bgy, bgw, bgh);
}

void Options::creditsSetup() {
	creditspanel.loadImage("Interface/Card X2/Card X3.png");
	crexit.loadImage("Interface/Icons/03.png");
	line1 = "Developed By";
	line2 = "Engin Kutlu";
	line3 = "Game Studio: Tengri Games";
	line4 = "Programming & Design: Engin Kutlu";
	line5 = "Special Thanks: glistEngine, GameLab Istanbul";
	line6 = "Assets & Fonts Licensed (dafont)";
	line7 = "(c) 2026";

	centerx = getScreenWidth() / 2;
	linegap = 30;

	starty = getHeight() / 2 - 3 * linegap;
	tabtitle = "CREDITS";
	titley = getHeight() * 15 / 100;

	crpanelw = creditspanel.getWidth() * 2.4f;
	crpanelh = creditspanel.getHeight() * 2.4f;
	crpanelx = (getWidth() - crpanelw) / 2;
	crpanely = (getHeight() - crpanelh) / 3;
	crexitw = crexit.getWidth() * 0.10;
	crexith = crexit.getHeight() * 0.10;
	crexitx = (crpanelx + crpanelw) - crexitw;
	crexity = crpanely;

	crexitbutton.set(crexitx, crexity, crexitx + crexitw, crexity + crexith);
	crexitbuttonstate = BUTTON_NONE;
}

void Options::creditsDraw() {
	creditspanel.draw(crpanelx, crpanely, crpanelw, crpanelh);
	setColor(255, 255, 255);
	if(crexitbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(crexitbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	crexit.draw(crexitx, crexity, crexitw, crexith);
	setColor(255, 255, 255);

	int y = starty;
	std::vector<std::string> lines = {
		line1, line2, line3, line4, line5, line6, line7
	};

	for(int i = 0; i < lines.size(); i++) {
		int w = root->secondtextfont.getStringWidth(lines[i]);
		root->secondtextfont.drawText(lines[i], centerx - w / 2, y);
		y += linegap;
	}

	int titlew = root->textfont.getStringWidth(tabtitle);
	root->titlefont.drawText(tabtitle, centerx - titlew / 1.25, titley);
}

void Options::contactSetup() {
	contactlines.clear();
	contactpanel.loadImage("Interface/Card X2/Card X3.png");
	coexit.loadImage("Interface/Icons/03.png");
	contactlines.push_back("E-Mail: contact@yourmail.com");
	contactlines.push_back("X: x.com/youraccount");
	contactlines.push_back("Instagram: instagram.com/youraccount");
	contactlines.push_back("Website: yourwebsite.com");
	contactlines.push_back("itch.io: yourname.itch.io");

	contactlineh = root->secondtextfont.getStringHeight("y");

	copanelw = contactpanel.getWidth() * 2.4f;
	copanelh = contactpanel.getHeight() * 2.4f;
	copanelx = (getWidth() - copanelw) / 2;
	copanely = (getHeight() - copanelh) / 3;
	coexitw = coexit.getWidth() * 0.10;
	coexith = coexit.getHeight() * 0.10;
	coexitx = (copanelx + copanelw) - coexitw;
	coexity = copanely;

	contactw = root->secondtextfont.getStringWidth(contacttext);
	contacth = root->secondtextfont.getStringHeight(contacttext);

	contactx = contactbuttonx + (buttonw - contactw) / 2;
	contacty = contactbuttony + (buttonh + contacth) / 2;

	contactx = containerx + containerw * 0.01f;
	contacty = containery + containerh * 0.18f;

	coexitbutton.set(coexitx, coexity, coexitx + coexitw, coexity + coexith);
	coexitbuttonstate = BUTTON_NONE;
}

void Options::contactDraw() {
	float y = contacty;
	contactpanel.draw(copanelx, copanely, copanelw, copanelh);
	setColor(255, 255, 255);
	if(coexitbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(coexitbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	coexit.draw(coexitx, coexity, coexitw, coexith);
	setColor(255, 255, 255);

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
	backgroundSetup();
	containerSetup();
	tabSetup();
	contactSetup();
	creditsSetup();
	titleSetup();
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
	contactTabButtonSetup();
	creditsTabButtonSetup();
	returnSetup();
}

void Options::tabDraw() {
	setColor(normalcolor);
	contactTabButtonDraw();
	creditsTabButtonDraw();
	returnDraw();
}

void Options::tabButtonPressed(int x, int y) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}
	if(contactbutton.contains(x, y)) {
		contactbuttonstate = BUTTON_PRESSED;
	}
	if(creditsbutton.contains(x, y)) {
		creditsbuttonstate = BUTTON_PRESSED;
	}

	if(showcontactpanel && coexitbutton.contains(x, y)) {
		coexitbuttonstate = BUTTON_PRESSED;
	}
	if(showcreditspanel && crexitbutton.contains(x, y)) {
		crexitbuttonstate = BUTTON_PRESSED;
	}
}

void Options::tabButtonReleased(int x, int y) {
	if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		buttonsound.play();
		root->setCurrentCanvas(new MainMenuCanvas(root));
		return;
	}
	if(contactbutton.contains(x, y) && contactbuttonstate == BUTTON_PRESSED) {
		contactbuttonstate = BUTTON_PERFORMED;
		buttonsound.play();
		showcontactpanel = true;
		showcreditspanel = false;
		return;
	}
	if(creditsbutton.contains(x, y) && creditsbuttonstate == BUTTON_PRESSED) {
		creditsbuttonstate = BUTTON_PERFORMED;
		buttonsound.play();
		showcreditspanel = true;
		showcontactpanel = false;
		return;
	}
	if(showcreditspanel && crexitbutton.contains(x, y) && crexitbuttonstate == BUTTON_PRESSED) {
		gLogi("Options") << "Credits Kapatildi";
		crexitbuttonstate = BUTTON_PERFORMED;
		buttonsound.play();
		showcreditspanel = false;
		return;
	}
	if(showcontactpanel && coexitbutton.contains(x, y) && coexitbuttonstate == BUTTON_PRESSED) {
		gLogi("Options") << "Contact Kapatildi";
		coexitbuttonstate = BUTTON_PERFORMED;
		buttonsound.play();
		showcontactpanel = false;
		return;
	}

	returnbuttonstate  = BUTTON_CANCELED;
	contactbuttonstate = BUTTON_CANCELED;
	creditsbuttonstate = BUTTON_CANCELED;
	coexitbuttonstate  = BUTTON_CANCELED;
	crexitbuttonstate  = BUTTON_CANCELED;
}

void Options::tabButtonFocus(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		returnbuttonstate = returnhitbox.contains(x, y) ? BUTTON_FOCUS : BUTTON_NONE;
	}
	if(contactbuttonstate != BUTTON_PRESSED) {
		contactbuttonstate = contactbutton.contains(x, y) ? BUTTON_FOCUS : BUTTON_NONE;
	}
	if(creditsbuttonstate != BUTTON_PRESSED) {
		creditsbuttonstate = creditsbutton.contains(x, y) ? BUTTON_FOCUS : BUTTON_NONE;
	}

	if(showcontactpanel && coexitbuttonstate != BUTTON_PRESSED) {
		coexitbuttonstate = coexitbutton.contains(x, y) ? BUTTON_FOCUS : BUTTON_NONE;
	}
	if(showcreditspanel && crexitbuttonstate != BUTTON_PRESSED) {
		crexitbuttonstate = crexitbutton.contains(x, y) ? BUTTON_FOCUS : BUTTON_NONE;
	}
}

void Options::containerSetup() {
	returnimg.loadImage("Interface/Button 1/Button Active.png");
	applyimg.loadImage("Interface/Button 1/Button Active.png");
	resetimg.loadImage("Interface/Button 1/Button Active.png");

	int width = getWidth();
	int height = getHeight();

	float basecontainerw = 0.42f;
	float basecontainerh = 0.78f;

	containerw = getWidth() * basecontainerw;
	containerh = getHeight() * basecontainerh;

	containerx = (width - containerw) / 2;
	containery = (height - containerh) / 2;

	containercolor.set(255, 255, 255);
	audioSettingsSetup();
}

void Options::containerDraw() {
	setColor(255, 255, 255);
}

void Options::audioSettingsSetup() {
	musictickSetup();
	fxtickSetup();
}

void Options::audioSettingsDraw() {
	musictickDraw();
	fxtickDraw();
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
	    optionsound.play();
		applyAudioSettings();
		containerSetup();
		tabSetup();
	}
	else if(fxbuttonhitbox.contains(x, y) && fxtickstate == BUTTON_PRESSED) {
	    fxtickstate = BUTTON_PERFORMED;
	    isfxenabled = !isfxenabled;
	    optionsound.play();
	    applyAudioSettings();
		containerSetup();
		tabSetup();
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
	setColor(255, 255, 255);
}

void Options::contactTabButtonSetup() {
    contactbuttonactive.loadImage("Interface/Button 1/Button Active.png");
    contactbuttonhover.loadImage("Interface/Button 1/Button Hover.png");
    contactbuttonnormal.loadImage("Interface/Button 1/Button Normal.png");

    buttonw = contactbuttonactive.getWidth() * 1.30f;
    buttonh = contactbuttonactive.getHeight() * 1.30f;

    buttonspacing = 25;

    contactbuttonx = containerx + (containerw - buttonw) / 2;
    contactbuttony = containery + containerh * 0.58f;

    contacttext = "Contact";

    contactbutton.set(
        contactbuttonx,
        contactbuttony,
        contactbuttonx + buttonw,
        contactbuttony + buttonh
    );

    contactbuttonstate = BUTTON_NONE;
}

void Options::creditsTabButtonSetup() {
    creditsbuttonactive.loadImage("Interface/Button 1/Button Active.png");
    creditsbuttonhover.loadImage("Interface/Button 1/Button Hover.png");
    creditsbuttonnormal.loadImage("Interface/Button 1/Button Normal.png");

    creditsbuttonx = contactbuttonx;

    creditsbuttony =
        contactbuttony +
        buttonh +
        buttonspacing;

    creditstext = "Credits";

    creditsbutton.set(
        creditsbuttonx,
        creditsbuttony,
        creditsbuttonx + buttonw,
        creditsbuttony + buttonh
    );

    creditsbuttonstate = BUTTON_NONE;
}

void Options::contactTabButtonDraw() {
    if(contactbuttonstate == BUTTON_FOCUS)
        contactbuttonhover.draw(contactbuttonx, contactbuttony, buttonw, buttonh);
    else if(contactbuttonstate == BUTTON_PRESSED ||
            contactbuttonstate == BUTTON_PERFORMED)
        contactbuttonactive.draw(contactbuttonx, contactbuttony, buttonw, buttonh);
    else
        contactbuttonnormal.draw(contactbuttonx, contactbuttony, buttonw, buttonh);

    int textW = root->thirdtextfont.getStringWidth(contacttext);
    int textH = root->thirdtextfont.getStringHeight(contacttext);

    int textX = contactbuttonx + (buttonw - textW) / 2;
    int textY = contactbuttony + (buttonh + textH) / 2;

	setColor(255, 255, 255);
    root->thirdtextfont.drawText(contacttext, textX, textY);
}

void Options::creditsTabButtonDraw() {
    if(creditsbuttonstate == BUTTON_FOCUS)
        creditsbuttonhover.draw(creditsbuttonx, creditsbuttony, buttonw, buttonh);
    else if(creditsbuttonstate == BUTTON_PRESSED ||
            creditsbuttonstate == BUTTON_PERFORMED)
        creditsbuttonactive.draw(creditsbuttonx, creditsbuttony, buttonw, buttonh);
    else
        creditsbuttonnormal.draw(creditsbuttonx, creditsbuttony, buttonw, buttonh);

    int textW = root->thirdtextfont.getStringWidth(creditstext);
    int textH = root->thirdtextfont.getStringHeight(creditstext);

    int textX = creditsbuttonx + (buttonw - textW) / 2;
    int textY = creditsbuttony + (buttonh + textH) / 2;

	setColor(255, 255, 255);
    root->thirdtextfont.drawText(creditstext, textX, textY);
}

void Options::musictickSetup() {
	musictext = "Music";
	musicuncheck.loadImage("inactivecolor.png");
	musiccheck.loadImage("Interface/Icons/30.png");
	musictextw = root->secondtextfont.getStringWidth(musictext);
	musictexth = root->secondtextfont.getStringHeight(musictext);
	musictextx = containerx + (containerw * 0.20);
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
	fxuncheck.loadImage("inactivecolor.png");
	fxcheck.loadImage("Interface/Icons/30.png");
	fxtextw = root->secondtextfont.getStringWidth(fxtext);
	fxtexth = root->secondtextfont.getStringHeight(fxtext);
	fxtextx = containerx + (containerw * 0.20);
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
	root->secondtextfont.drawText(musictext, musictextx, musictexty);
	musicuncheck.draw(musicuncheckx, musicunchecky, musicuncheckw, musicuncheckh);
	if(ismusicenabled) {
		setColor(255, 255, 255);
		musiccheck.draw(musicuncheckx, musicunchecky, musiccheckw, musiccheckh);
	}
}

void Options::fxtickDraw() {
	root->secondtextfont.drawText(fxtext, fxtextx, fxtexty);
	fxuncheck.draw(fxuncheckx, fxunchecky, fxuncheckw, fxuncheckh);
	if(isfxenabled) {
		setColor(255, 255, 255);
		fxcheck.draw(fxuncheckx, fxunchecky, fxcheckw, fxcheckh);
	}
}

void Options::applyAudioSettings() {
	root->saveAudioSettings(isfxenabled, ismusicenabled);
}

void Options::titleSetup() {
	titlew = root->gametitlefont.getStringWidth(root->optionskey);
	titleh = root->gametitlefont.getStringHeight(root->optionskey);

	titlex = bgx + (bgw - titlew) / 2;
	titley = tabh + titleh;
}

void Options::titleDraw() {
	setColor(255, 255, 255);
	root->gametitlefont.drawText(root->optionskey, titlex, titley);
}

