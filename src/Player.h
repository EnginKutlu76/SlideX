/*
 * Player.h
 *
 *  Created on: 25 May 2026
 *      Author: Engin
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "gObject.h"

class Player: public gObject {
public:
	Player();
	Player(const Player& original);
	virtual ~Player();

	void setAnimationNo(int animationNo);
	int getAnimationNo();
	void setFrameNo(int frameNo);
	int getFrameNo();

	static int getAnimationNum();
	int getFrameNum(int animationNo);

	void setFrameCounter(int frameCounter);
	int getFrameCounter();
	int getFrameCounterLimit();

private:

	static const int animationnum = 3;
	static const int maxframenum = 16;

	int animationno, frameno;
	int framecounter, framecounterlimit;
	int framenum[animationnum];
	std::string data;
};

#endif /* SRC_PLAYER_H_ */
