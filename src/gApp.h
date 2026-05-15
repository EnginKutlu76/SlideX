/*
 * gApp.h
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#ifndef GAPP_H_
#define GAPP_H_

#include "gBaseApp.h"
#include "gFont.h"
#include "gLocalization.h"

class gApp : public gBaseApp {
public:
	gApp();
	gApp(int argc, char **argv);
	~gApp();

	void setup();
	void update();
	std::string localizeWord(std::string word);

	gFont gametitlefont, titlefont, textfont, secondtextfont;

	std::string titlekey = "Slide X", languagekey = "language", showfpskey = "showfps",
	soundvolumekey = "soundvolume", musicvolumekey = "musicvolume", soundkey = "sound", musickey = "music",
	startkey = "start", optionskey = "options", creditskey = "credits", returnkey = "return",
	generalkey = "general", videokey = "video", audiokey = "audio", controlskey = "controls", applykey = "apply", resetkey = "reset", helpkey = "help",
	generallabelkey = ".";
	void drawMenuBackground(int w, int h);


private:
	void loadAssets();
	gLocalization localization;
	gImage* background;

};

#endif /* GAPP_H_ */
