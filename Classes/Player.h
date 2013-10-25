/*
 * Player.h
 *
 *  Created on: Oct 24, 2013
 *      Author: probigi
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class Player {
public:
	Player();

	void create();
	CCParticleSystem* getNode();
	void tick(float dt);
	void moveTo(float tx, float ty);
	void setVelocity(float vx, float vy);

private:
	CCParticleSystem *_skin;
	int _speed;
	CCPoint _velocity;
	CCPoint _target;
	CCPoint _pos;
};

#endif /* PLAYER_H_ */
