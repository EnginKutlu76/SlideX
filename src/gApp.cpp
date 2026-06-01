/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#include "gApp.h"
#include "MainMenuCanvas.h"
#include "gCanvas.h"
#include "gImage.h"

gApp::gApp() {
}

gApp::gApp(int argc, char **argv) : gBaseApp(argc, argv) {
}

gApp::~gApp() {
}

void gApp::setup() {
	loadAssets();
	MainMenuCanvas* cnv = new MainMenuCanvas(this);
	appmanager->setCurrentCanvas(cnv);
}

void gApp::drawMenuBackground(int w, int h) {
	background->draw(0, 0, w, h);
}

int safeGetInt(std::string data) {
	auto parts = gSplitString(data, "|");
	if(parts.size() > 1) return gToInt(parts[1]);
	return 0;
}

void gApp::loadAssets() {
	titlefont.loadFont("neon_zone/Neon Zone.ttf", 30);
	gametitlefont.loadFont("neon_zone/Neon Zone.ttf", 50);
	textfont.loadFont("neon_zone/Neon Zone.ttf", 18);
	secondtextfont.loadFont("StrongStitch-Regular.otf", 20);
	thirdtextfont.loadFont("neon_zone/Neon Zone.ttf", 25);
	background = new gImage();
	background->loadImage("UIasset/PNG/MainPanel01.png");

	// OPTIONS DB
	optionsdb.loadDatabase("options.db");
	optionsdb.execute("CREATE TABLE IF NOT EXISTS options (key TEXT PRIMARY KEY, value TEXT)");

	// DEFAULTS
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('sound','1')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('music','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('highscore','0')");

	loadAudioSettings();
	loadHighScore();
}

void gApp::update() {
}

void gApp::saveAudioSettings(int sound, int music) {
	this->sound = sound;
	this->music = music;

	optionsdb.execute("UPDATE options SET value=" + gToStr(sound) + " WHERE key='sound'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(music) + " WHERE key='music'");
}

void gApp::saveHighScore(int highscore) {
	this->highscore = highscore;

	optionsdb.execute("UPDATE options SET value=" + gToStr(highscore) + " WHERE key='highscore'");
}

void gApp::loadAudioSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='sound'");
	sound = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='music'");
	music = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadHighScore() {
	optionsdb.execute("SELECT value FROM options WHERE key='highscore'");
	highscore = safeGetInt(optionsdb.getSelectData());
}


void gApp::playMenuMusic()  {

}

void gApp::stopMenuMusic() {

}

void gApp::toggleMusic() {
    musicenabled = !musicenabled;
    if (musicenabled) playMenuMusic();
    else stopMenuMusic();
}

void gApp::setMusicEnabled(bool enabled) {
    musicenabled = enabled;
    if (enabled) playMenuMusic();
    else stopMenuMusic();
}

int gApp::getSound() {
	return sound;
}

int gApp::getMusic() {
	return music;
}

int gApp::getHighScore() {
	return highscore;
}
