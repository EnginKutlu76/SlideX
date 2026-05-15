/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#include "gApp.h"
#include "MainMenuCanvas.h"


gApp::gApp() {
}

gApp::gApp(int argc, char **argv) : gBaseApp(argc, argv) {
}

gApp::~gApp() {
}

void gApp::setup() {
	MainMenuCanvas* cnv = new MainMenuCanvas(this);
	appmanager->setCurrentCanvas(cnv);
	loadAssets();
}

void gApp::drawMenuBackground(int w, int h) {
	background->draw(0, 0, w, h);
}

std::string gApp::localizeWord(std::string word) {
	return localization.localizeWord(word);
}

void gApp::loadAssets() {
	titlefont.loadFont("neon_zone/Neon Zone.ttf", 30);
	gametitlefont.loadFont("neon_zone/Neon Zone.ttf", 50);
	textfont.loadFont("neon_zone/Neon Zone.ttf", 18);
	secondtextfont.loadFont("StrongStitch-Regular.otf", 20);
	background = new gImage();
	background->loadImage("arkaplan.jpg");

	// LOCALIZATION DB
	gDatabase locdb;
	locdb.loadDatabase("localization.db");
	locdb.execute("CREATE TABLE IF NOT EXISTS WORDS (Key TEXT PRIMARY KEY, en TEXT, tr TEXT)");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('start','Start','Basla')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('options','Options','Ayarlar')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('help','Help','Yardim')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('credits','Credits','Emegi Gecenler')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('exit','Exit','aaa')");
	locdb.close();

	localization.loadDatabase("localization.db", "WORDS");
}

void gApp::update() {
}
