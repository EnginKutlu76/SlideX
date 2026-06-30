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
#include "gSound.h"
#include "gDatabase.h"


class gApp : public gBaseApp {
public:
	gApp();
	gApp(int argc, char **argv);
	~gApp();

	void setup();
	void update();

	gFont gametitlefont, titlefont, textfont, secondtextfont, thirdtextfont;

	std::string titlekey = "Slide X", languagekey = "language", showfpskey = "showfps",
	soundvolumekey = "soundvolume", musicvolumekey = "musicvolume", soundkey = "sound", musickey = "music",
	startkey = "start", optionskey = "options", creditskey = "credits", returnkey = "return",
	generalkey = "general", videokey = "video", audiokey = "audio", controlskey = "controls", applykey = "apply", resetkey = "reset", contactkey = "contact",
	generallabelkey = ".";

	void saveAudioSettings(int sound, int music);
	void saveHighScore(int highscore);

	void loadAudioSettings();
	void loadHighScore();

	void applyAudioSettings();

	void playMenuMusic();
	void stopMenuMusic();
	void toggleMusic();
	void setMusicEnabled(bool enabled);
	bool getMusicEnabled() const { return musicenabled; }

	int getSound();
	int getMusic();
	int getHighScore();
//	int getExperience();

private:
	bool musicenabled = true;
	void loadAssets();
	gDatabase optionsdb;
	int sound, music, highscore;
};

#endif /* GAPP_H_ */
