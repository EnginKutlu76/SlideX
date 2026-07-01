/*
 * Options.h
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#ifndef SRC_OPTIONS_H_
#define SRC_OPTIONS_H_

#include <gBaseCanvas.h>
#include "gApp.h"
#include "gImage.h"
#include "gSound.h"

class Options: public gBaseCanvas {
public:
	Options(gApp* root);
	virtual ~Options();

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

	float uiscale;
	void updateScale();

private:
	gApp* root;

	static const int  BUTTON_NONE = 0, BUTTON_PRESSED = 1, BUTTON_CANCELED = -1, BUTTON_PERFORMED = 2, BUTTON_FOCUS = 3;
	static const int TAB_NONE = 0, TAB_GAME = 1, TAB_CONTROLS = 2, TAB_GRAPHICS = 3, TAB_AUDIO = 4, TAB_APPLY = 5, TAB_CONTACT = 7, TAB_CREDITS = 8;
	static const int keynum = 7;

	//tab funcs
	void tabSetup();
	void tabDraw();
	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

	//container funcs
	void containerSetup();
	void containerDraw();
	void containerButtonPressed(int x, int y);
	void containerButtonReleased(int x, int y);
	void containerButtonFocus(int x, int y);

	//audio funcs
	void audioSettingsSetup();
	void musictickSetup();
	void fxtickSetup();
	void audioSettingsPressed(int x, int y);
	void audioSettingsReleased(int x, int y);
	void audioSettingsFocus(int x, int y);
	void audioSettingsDraw();
	void musictickDraw();
	void fxtickDraw();

	void applyAudioSettings();

	//return funcs
	void returnSetup();
	void returnDraw();

	//contact and credits button
	void contactTabButtonSetup();
	void creditsTabButtonSetup();
	void contactTabButtonDraw();
	void creditsTabButtonDraw();
	void repositionAll();
	//void loadAssets();

	void contactSetup();
	void contactDraw();

	void creditsSetup();
	void creditsDraw();

	void backgroundSetup();
	void backgroundDraw();

	void titleSetup();
	void titleDraw();

	//tabs
	gRect audiotabbutton, contactbutton, creditsbutton;
	std::string audiotabtext, contacttext, creditstext;
	int audiotabbuttonstate, contactbuttonstate, creditsbuttonstate;

	int gametabbuttonx, gametabbuttony, gametabbuttonw, gametabbuttonh;
	int graphicstabbuttonx, graphicstabbuttony, graphicstabbuttonw, graphicstabbuttonh;
	int audiotabbuttonx, audiotabbuttony, audiotabbuttonw, audiotabbuttonh;
	int tabfontx, tabfonty, tabfontw, tabfonth;
	int tabx, taby, tabw, tabh;

	gColor tabcolor, pressedcolor, focuscolor, normalcolor;

	int activetab;

	//container
	int containerx, containery, containerw, containerh;
	gColor containercolor;

	//audio settings
	gImage musicuncheck, musiccheck;
	gRect musicbuttonhitbox;
	std::string musictext;
	int musictextx, musictexty, musictextw, musictexth;
	int musicuncheckx, musicunchecky, musicuncheckw, musicuncheckh;
	int musiccheckw, musiccheckh;
	int musictickstate;
	bool ismusicenabled;

	gImage fxuncheck, fxcheck;
	gRect fxbuttonhitbox;
	std::string fxtext;
	int fxtextx, fxtexty, fxtextw, fxtexth;
	int fxuncheckx, fxunchecky, fxuncheckw, fxuncheckh;
	int fxcheckw, fxcheckh;
	int fxtickstate;
	bool isfxenabled;

	//return
	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;

	//titles
	std::string tabtitle;
	int tabtextx, tabtexty, tabtextw, tabtexth;
	std::string sectiontitle;
	int titlex, titley, titlew, titleh;

	int settingstartx, settingstarty;
	int settingrowh;
	int settingvaluex;
	int settingiconoffset;

	gImage backgroundimg;
	gImage returnimg;
	gImage applyimg;
	gImage resetimg;

	std::string line1, line2, line3, line4, line5, line6, line7;
	int centerx, starty, linegap;

	gSound buttonsound, optionsound;

	//bg
	gImage background;
	int bgx, bgy, bgw, bgh;

	int buttonw, buttonh;
	int buttonspacing;

	gImage contactbuttonactive, contactbuttonhover, contactbuttonnormal;
	int contactbuttonx, contactbuttony;
	gImage contactimg;
	gImage contactpanel;
	gImage coexit;
	gRect coexitbutton;
	int coexitbuttonstate;
	int copanelx, copanely, copanelw, copanelh;
	int coexitx, coexity, coexitw, coexith;
	std::vector<std::string> contactlines;
	float contactlineh;
	float contactx, contacty, contactw, contacth;
	bool showcontactpanel = false;

	gImage creditsbuttonactive, creditsbuttonhover, creditsbuttonnormal;
	int creditsbuttonx, creditsbuttony;
	gImage creditsimg;
	gImage creditspanel;
	gImage crexit;
	gRect crexitbutton;
	int crexitbuttonstate;
	int crpanelx, crpanely, crpanelw, crpanelh;
	int crexitx, crexity, crexitw, crexith;
	bool showcreditspanel = false;
};

#endif /* SRC_OPTIONS_H_ */
