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

	gFont gametitlefont, titlefont, textfont, secondtextfont;

	std::string titlekey = "Slide X", languagekey = "language", showfpskey = "showfps",
	soundvolumekey = "soundvolume", musicvolumekey = "musicvolume", soundkey = "sound", musickey = "music",
	startkey = "start", optionskey = "options", creditskey = "credits", returnkey = "return",
	generalkey = "general", videokey = "video", audiokey = "audio", controlskey = "controls", applykey = "apply", resetkey = "reset", contactkey = "contact",
	generallabelkey = ".";
	void drawMenuBackground(int w, int h);
	std::string localizeWord(std::string word);

	void saveGameSettings(int language, int vsync, int showfps);
	void saveGraphicsSettings(int windowmode);
	void saveAudioSettings(int soundvolume, int musicvolume, int sound, int music);

	void loadGameSettings();
	void loadGraphicsSettings();
	void loadAudioSettings();

	void applyGameSettings();
	void applyControlsSettings();
	void applyGraphicsSettings();
	void applyAudioSettings();

	void resetGameSettings();
	void resetControlsSettings();
	void resetGraphicsSettings();
	void resetAudioSettings();

	void playMenuMusic();
	void stopMenuMusic();
	void toggleMusic();
	void setMusicEnabled(bool enabled);
	bool getMusicEnabled() const { return musicenabled; }

	int getLanguage();
	int getShowFps();
	int getVsync();
	int getWindowMode();
	int getSoundVolume();
	int getMusicVolume();
	int getSound();
	int getMusic();
//	int getExperience();

private:
	bool musicenabled = true;
	void loadAssets();
	gLocalization localization;
	gImage* background;
	gDatabase optionsdb;
	int language, sensitivity, showfps, vsync, windowmode, soundvolume, musicvolume, sound, music;
};

#endif /* GAPP_H_ */
