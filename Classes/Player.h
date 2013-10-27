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
	void addSkin();
	void removeSkin(int id);
	std::vector<CCParticleSystem*>* getNodes();
	void tick(float dt);
	void moveTo(int id, float tx, float ty);
	void setVelocity(int id, float vx, float vy);
	void setSkin(int id, CCParticleSystem* item);

	int activeTouches;

private:
	bool checkClonePos(int id);


	std::vector<CCParticleSystem*> *_skins;
	int _speed;
	std::vector<CCPoint*> *_velocityes;
	std::vector<CCPoint*> *_targets;
};

#endif /* PLAYER_H_ */
