/*
 * Help.h
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#ifndef SRC_HELP_H_
#define SRC_HELP_H_

#include <gBaseCanvas.h>
#include "gApp.h"

class Help: public gBaseCanvas {
public:

	Help(gApp* root);
	virtual ~Help();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();
private:
	gApp* root;

	static const int  BUTTON_NONE = 0, BUTTON_PRESSED = 1, BUTTON_CANCELED = -1, BUTTON_PERFORMED = 2, BUTTON_FOCUS = 3;
	static const int TAB_NONE = 0, TAB_GENERAL = 1, TAB_LEVEL = 2, TAB_ITEMS = 3, TAB_CONTROLS = 4;
	static const int languagenum = 3;
	static const int LANG_EN = 1, LANG_TR = 2;

	void tabSetup();

	void containerSetup();
	void gameSettingsSetup();
	void modeSettingsSetup();
	void itemsSettingsSetup();
	void controlsSettingsSetup();

	void tabDraw();

	void containerDraw();
	void gameSettingsDraw();
	void modeSettingsDraw();
	void itemsSettingsDraw();
	void controlsSettingsDraw();

	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

	void containerButtonPressed(int x, int y);
	void containerButtonReleased(int x, int y);
	void containerButtonFocus(int x, int y);

	void gameSettingsPressed(int x, int y);
	void gameSettingsReleased(int x, int y);
	void gameSettingsFocus(int x, int y);
	void modeSettingsPressed(int x, int y);
	void modeSettingsReleased(int x, int y);
	void modeSettingsFocus(int x, int y);
	void itemsSettingsPressed(int x, int y);
	void itemsSettingsReleased(int x, int y);
	void itemsSettingsFocus(int x, int y);
	void controlsSettingsPressed(int x, int y);
	void controlsSettingsReleased(int x, int y);
	void controlsSettingsFocus(int x, int y);
	void forwardButtonSetup();
	void forwardButtonDraw();
	void backButtonSetup();
	void backButtonDraw();

	std::string getTabTitle() const;

	//tabs
	gRect gametabbutton, modetabbutton, controlstabbutton;
	std::string  modetabtext, itemstabtext, controlstabtext;

	int tabfontx, tabfonty, tabfontw, tabfonth;
	int tabx, taby, tabw, tabh;
	gColor tabcolor, pressedcolor, focuscolor, normalcolor;

	int activetab;

	//container
	int containerx, containery, containerw, containerh;
	gColor containercolor;

	//game settings
	std::string gamelabeltext;
	int gamelabelx, gamelabely, gamelabelw, gamelabelh;
	int gamedisplayx, gamedisplayy, gamedisplayw, gamedisplayh;

    void returnSetup();
	void returnDraw();

	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;

	gImage logo[5];
	int logox[5], logoy[5], logow[5], logoh[5];

	std::vector<std::string> gamelabellines;

	//active color
	gImage activepart, inactivepart;
	int activex, activey, activew, activeh;
	int activeposx;

	std::string tabtitle;
	int tabtextx, tabtexty, tabtextw, tabtexth;

	//forwar&back buttons
	gRect forwardbutton, backbutton;
	int forwardbuttonx, forwardbuttony, forwardbuttonw, forwardbuttonh;
	int backbuttonx, backbuttony, backbuttonw, backbuttonh;
	gImage arrowleft, arrowright;
	int forwardstate, backstate;

};

#endif /* SRC_HELP_H_ */
