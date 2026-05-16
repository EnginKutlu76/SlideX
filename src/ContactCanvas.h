/*
 * ContactCanvas.h
 *
 *  Created on: 15 May 2026
 *      Author: Engin
 */

#ifndef CONTACTCANVAS_H_
#define CONTACTCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gColor.h"
#include "gGUIManager.h"
#include "gRect.h"
#include <vector>
#include <string>

class ContactCanvas : public gBaseCanvas {
public:
	ContactCanvas(gApp* root);
	virtual ~ContactCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);

	void mouseMoved(int x, int y);
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
	void tabSetup();
	void tabDraw();

	void containerSetup();
	void containerDraw();

	void contactSetup();
	void contactDraw();

	void returnSetup();
	void returnDraw();

	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

private:
	static const int  BUTTON_NONE = 0, BUTTON_PRESSED = 1, BUTTON_CANCELED = -1, BUTTON_PERFORMED = 2, BUTTON_FOCUS = 3;

	gApp* root;

	float tabx, taby, tabw, tabh;
	float tabtextx, tabtexty;
	float tabtextw, tabtexth;

	float containerx, containery, containerw, containerh;

	float contactx, contacty;
	float contactlineh;

	float returnx, returny;
	float returnw, returnh;

	std::string tabtitle;
	std::string returntext;

	gColor tabcolor;
	gColor normalcolor;
	gColor pressedcolor;
	gColor focuscolor;
	gColor containercolor;

	gRect returnhitbox;

	int returnbuttonstate;

	std::vector<std::string> contactlines;
};

#endif
