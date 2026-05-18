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
	static const int KEY_NONE = 0, KEY_W = 1, KEY_S = 2, KEY_D = 4, KEY_A = 8, KEY_E = 16, KEY_R = 32, KEY_Z = 64, KEY_X = 128;
	int keystate;
	void moveCharacter();
	void moveCamera();

	gApp* root;
	gBox plane;
	gBox player;
	gCamera cam;
	gLight light;
	gMaterial material;
	gTexture diffusemap, specularmap;
};

#endif /* GCANVAS_H_ */
