 /*
 * gCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#ifndef GCANVAS_H_
#define GCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gCamera.h"
#include "gBox.h"
#include "gLight.h"
#include "gMaterial.h"
#include "gTexture.h"
#include "gShadowMap.h"


class gCanvas : public gBaseCanvas {
public:
	gCanvas(gApp* root);
	virtual ~gCanvas();

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
	static const int KEY_NONE = 0, KEY_W = 1, KEY_S = 2, KEY_D = 4, KEY_A = 8, KEY_E = 16, KEY_R = 32, KEY_Z = 64, KEY_X = 128, KEY_ESC = 256;
	static const int LINE_LEFT = 0, LINE_MID = 1, LINE_RIGHT = 2;
	enum { GAMESTATE_LOAD, GAMESTATE_PLAY, GAMESTATE_GAMEOVER, GAMESTATE_PAUSE };
	int gamestate;
	int keystate;
	int linestate;
	void moveCharacter();
	void moveCamera();
	void fpsSetup();
	void fpsDraw();
	void drawGui();

	gApp* root;
	std::vector<gBox> plane;
	gBox plane1;
	gBox player;
	gCamera cam;
	gLight light;
	gMaterial material;
	gTexture diffusemap, specularmap;
	gShadowMap shadow;
	float velocityy;
	float gravity;
	bool isgrounded;

	bool isjumping;
	float jumprotation;
	float lastplanez;
	int linelocation;

	float speed;
	float maxspeed;
	float acceleration;

	int score;
	int scorex, scorey;

	int fpscounterx, fpscountery;

	float lastPlayerZ;
	float scoreFloat;

	gImage resumepanel;
	bool resumepanelshown;
	int rpx, rpy, rpw, rph;
	int scorepanelx, scorepanely;
};

#endif /* GCANVAS_H_ */
