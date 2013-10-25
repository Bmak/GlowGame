/*
 * MapObject.h
 *
 *  Created on: Oct 25, 2013
 *      Author: probigi
 */

#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "cocos2d.h"
USING_NS_CC;

class MapObject : public CCSprite {
public:
	MapObject();

	void create();
	void initOptions();
	CCParticleSystem* getNode();
	void tick(float dt);
	void setPosition(float x, float y);
	void show();
	void hide();
	bool isLive();
	void setLive(bool b);

private:
	bool _isLive;
	CCParticleSystem *_skin;
	CCPoint _pos;
	int _lifeTime;
};

#endif /* MAPOBJECT_H_ */
