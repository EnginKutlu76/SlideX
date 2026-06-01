#ifndef SRC_CREDITSMENU_H_
#define SRC_CREDITSMENU_H_

#include <gBaseCanvas.h>
#include "gApp.h"
#include "gRect.h"
#include "gImage.h"

class CreditsMenu: public gBaseCanvas {
public:
	CreditsMenu(gApp* root);
	virtual ~CreditsMenu();

	void setup();
	void update();
	void draw();

	void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

private:
	gApp* root;

	void setupTexts();
	void drawTexts();

	void setupButton();
	void drawButton();

	void updateButtonState(int x, int y);
	void checkButtonPressed(int x, int y);
	void checkButtonReleased(int x, int y);

	std::string line1, line2, line3, line4, line5, line6, line7;

	int centerx, starty, linegap;

	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnstate;

	gColor normalcolor, focuscolor, pressedcolor;

	std::string title;
	int titley;

	gImage backgroundimg;
	int bgx, bgy, bgw, bgh;
};

#endif
