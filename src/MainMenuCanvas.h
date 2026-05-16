/*
 * MainMenuCanvas.h
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#ifndef SRC_MAINMENUCANVAS_H_
#define SRC_MAINMENUCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gFont.h"
#include "gImage.h"
#include "gFont.h"

class MainMenuCanvas: public gBaseCanvas {
public:
	MainMenuCanvas(gApp* root);
	virtual ~MainMenuCanvas();
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

	void menuSetup();
	void menuDraw();
	void menuPressed(int x, int y);
	void menuReleased(int x, int y);
	void menuFocus(int x, int y);

	//std::unique_ptr<Fade> fadeeffect;

private:
	static const int  BUTTON_NONE = 0, BUTTON_PRESSED = 1, BUTTON_CANCELED = -1, BUTTON_PERFORMED = 2, BUTTON_FOCUS = 3;

	gApp* root;

	void logoSetup();
	void startSetup();
	void optionSetup();
	void contactSetup();
	void creditSetup();
	void colorSetup();

	void updateButtonState(int x, int y);
	void checkButtonPressed(int x, int y, int button);
	void checkButtonReleased(int x, int y, int button);

	void backgroundDraw();
	void logoDraw();
	void startDraw();
	void optionDraw();
	void creditDraw();
	void contactDraw();
	void fadeEffectDraw();

	gImage background;
	std::string starttext, optiontext, credittext, exittext, contacttext;
	gImage glistlogo;
	int glistlogox, glistlogoy, glistlogow, glistlogoh;
	int nitralogox, nitralogoy, nitralogow, nitralogoh;
	int startx, starty, startw, starth;
	int optionx, optiony, optionw, optionh;
	int contactx, contacty, contactw, contacth;
	int creditx, credity, creditw, credith;
	int titlex, titley, titlew, titleh;
	gRect starthitbox, optionhitbox, credithitbox, contacthitbox;
	int startstate, optionstate, creditstate, contactstate;
	gColor pressedcolor, normalcolor, focuscolor;
	//std::unique_ptr<Fade> fadeeffect;
};

#endif /* SRC_MAINMENUCANVAS_H_ */
