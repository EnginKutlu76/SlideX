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
#include "gRect.h"
#include "Player.h"
#include "UiManager.h"
#include "Obstacle.h"
#include "GameState.h"

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
	struct Row {
		bool cell[3][3];
		float z;
	};

	static constexpr float LANE_OFFSET = 3.0f;
	static constexpr float GROUND_Y = 2.0f;
	static constexpr float GRAVITY = -0.015f;
	static constexpr float ROW_SPACING = 150.0f;

	std::vector<Row> rows;
	float nextRowZ;
	float rowSpacing;
	struct ObstacleRow {
		bool left1;
		bool left2;
		bool left3;
		bool mid1;
		bool mid2;
		bool mid3;
		bool right1;
		bool right2;
		bool right3;

		float z;
	};

	void fpsSetup();
	void guiSetup();
	void obstacleSetup();
	void scoreSetup();
	void planeSetup();
	void timingSetup();
	void camSetup();
	void camUpdate();
	void planeUpdate();
	void timingUpdate();
	void fpsDraw();
	void guiDraw();
	void obstacleDraw();
	void scoreDraw();
	void planeDraw();
	void enabling();
	void disabling();
	void obstacleUpdate();

	void handleMovementInput();
	void handleGameplayInput();
	void collision();
	void controlSetup();
	void controlUpdate();

	void updatePlayState();
	void updatePauseState();
	void updateGameOverState();

	gApp* root;

	//states
	int gamestate;
	int keystate;
	int linestate;

	//plane
	std::vector<gBox> plane;
	gBox plane1;

	gBox player;
	gCamera cam;
	gLight light;

	//controlling
	float velocityy;
	float gravity;
	bool isgrounded;
	bool isjumping;
	bool secondjump;
	bool isdownfall = false;
	float downfallVelocity = 0.0f;
	float jumprotation;

	float lastplanez;

	int linelocation;

	//speed
	float speed;
	float maxspeed;
	float acceleration;

	//score
	int score;
	int scorex, scorey;
	float scoreFloat;
	int highscore;

	int fpscounterx, fpscountery;

	float lastplayerz;

	//gui
	gImage resumepanel;
	gImage mainmbutton;
	gImage continuebutton;
	bool resumepanelshown;
	int rpx, rpy, rpw, rph;
	int scorepanelx, scorepanely;
	int leftbx, leftby, leftbw, leftbh;
	int rightbx, rightby, rightbw, rightbh;
	gRect hitbox;

	//timing
	float resumetimer;
	bool isresuming;

	//obstacle
	gBox obstacle;
	ObstacleRow currentrow;

	//color
	glm::vec3 color;
	glm::vec3 targetColor;
	float colorphase;
};

#endif /* GCANVAS_H_ */
