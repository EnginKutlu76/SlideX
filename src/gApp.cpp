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

std::string gApp::localizeWord(std::string word) {
	return localization.localizeWord(word);
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
	background = new gImage();
	background->loadImage("arkaplan.jpg");

	// OPTIONS DB
	optionsdb.loadDatabase("options.db");
	optionsdb.execute("CREATE TABLE IF NOT EXISTS options (key TEXT PRIMARY KEY, value TEXT)");

	// DEFAULTS
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('language','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('showfps','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('vsync','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('windowmode','0')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('soundvolume','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('musicvolume','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('sound','1')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('music','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('highscore','0')");

	// LOCALIZATION DB
	gDatabase locdb;
	locdb.loadDatabase("localization.db");
	locdb.execute("CREATE TABLE IF NOT EXISTS WORDS (Key TEXT PRIMARY KEY, en TEXT, tr TEXT)");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('start','Start','Basla')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('options','Options','Ayarlar')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('contact','Contact','Iletisim')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('credits','Credits','Emegi Gecenler')");
	locdb.close();

	localization.loadDatabase("localization.db", "WORDS");

	loadGameSettings();
	loadGraphicsSettings();
	loadAudioSettings();
	loadHighScore();
}

void gApp::update() {
}

void gApp::saveGameSettings(int language, int vsync, int showfps) {
	this->language = language;
	this->showfps = showfps;
	this->vsync = vsync;

	optionsdb.execute("UPDATE options SET value=" + gToStr(language) + " WHERE key='language'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(showfps) + " WHERE key='showfps'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(vsync) + " WHERE key='vsync'");

}

void gApp::saveGraphicsSettings(int windowmode) {
	this->windowmode = windowmode;

	optionsdb.execute("UPDATE options SET value=" + gToStr(windowmode) + " WHERE key='windowmode'");
}

void gApp::saveAudioSettings(int soundvolume, int musicvolume, int sound, int music) {
	this->soundvolume = soundvolume;
	this->musicvolume = musicvolume;
	this->sound = sound;
	this->music = music;

	optionsdb.execute("UPDATE options SET value=" + gToStr(soundvolume) + " WHERE key='soundvolume'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(musicvolume) + " WHERE key='musicvolume'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(sound) + " WHERE key='sound'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(music) + " WHERE key='music'");
}

void gApp::saveHighScore(int highscore) {
	this->highscore = highscore;

	optionsdb.execute("UPDATE options SET value=" + gToStr(highscore) + " WHERE key='highscore'");
}

void gApp::loadGameSettings(){
	optionsdb.execute("SELECT value FROM options WHERE key='language'");
	language = safeGetInt(optionsdb.getSelectData());
	if(language < 0 || language >= localization.getAvailableLanguages().size()) language = 0;
	localization.setCurrentLanguage(language);

	optionsdb.execute("SELECT value FROM options WHERE key='showfps'");
	showfps = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='vsync'");
	vsync = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadGraphicsSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='windowmode'");
	windowmode = safeGetInt(optionsdb.getSelectData());
	if(windowmode == NULL) windowmode = 1;
}

void gApp::loadAudioSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='soundvolume'");
	soundvolume = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='musicvolume'");
	musicvolume = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='sound'");
	sound = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='music'");
	music = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadHighScore() {
	optionsdb.execute("SELECT value FROM options WHERE key='highscore'");
	highscore = safeGetInt(optionsdb.getSelectData());
}

void gApp::applyGameSettings() {
	localization.setCurrentLanguage(language);
}

void gApp::applyControlsSettings() {

}

void gApp::applyGraphicsSettings() {

}

void gApp::applyAudioSettings() {

}

void gApp::resetGameSettings() {

}

void gApp::resetControlsSettings() {

}

void gApp::resetGraphicsSettings() {

}

void gApp::resetAudioSettings() {

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

int gApp::getLanguage() {
	return language;
}

int gApp::getShowFps() {
	return showfps;
}

int gApp::getVsync() {
	return vsync;
}

int gApp::getWindowMode() {
	return windowmode;
}

int gApp::getSoundVolume() {
	return soundvolume;
}

int gApp::getMusicVolume() {
	return musicvolume;
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
