/*
 * MapObject.cpp
 *
 *  Created on: Oct 25, 2013
 *      Author: probigi
 */

#include "MapObject.h"

USING_NS_CC;

MapObject::MapObject() {
}

void MapObject::create() {
	_skin = new CCParticleSystem();
	_skin = CCParticleMeteor::create();
	_skin->setGravity(ccp(0,0));
	initOptions();

	/*
	//_skin->setEmitterMode(kCCParticleModeRadius);

	_skin->setStartColor(ccc4f(0.0f,1,0.0f,1.0f));
	_skin->setStartColorVar(ccc4f(0.5f,0.1f,0.0f,0.1f));

//	_skin->setStartColorVar(ccc4f(50,50,0,50));
//	_skin->setEndColorVar(ccc4f(150,150,150,0));
	CCSize *size = new CCSize(30,30);
	_skin->setContentSize(*size);
	_skin->setStartSize(30);
	_skin->setStartSizeVar(30);
*/
	_skin->setScale(0);

	_lifeTime = 500;
	_isLive = true;
}

void MapObject::initOptions() {
	_skin->setStartColor(ccc4f(0.0f,1,0.0f,1.0f));
	_skin->setStartColorVar(ccc4f(0.5f,0.1f,0.0f,0.1f));

	CCSize *size = new CCSize(30,30);
	_skin->setContentSize(*size);
	_skin->setStartSize(30);
	_skin->setStartSizeVar(30);
}

CCParticleSystem* MapObject::getNode() {
	return _skin;
}

bool MapObject::isLive() {
	return _isLive;
}

void MapObject::setLive(bool b) {
	_isLive = b;
}

void MapObject::tick(float dt) {
	//_lifeTime -= dt;
	if (_lifeTime <= 0 && _isLive) {
		_isLive = false;
		hide();
		//CCLog("TIME IS UP!!! - ITEM DEAD");
	}
}

void MapObject::setPosition(float x, float y) {
	_pos.x = x;
	_pos.y = y;
	_skin->setPosition(_pos);
}

void MapObject::show() {
	CCLog("SHOW ITEM");
	CCScaleTo *actionScale = CCScaleTo::create(1,1);

//	CCCallFuncN* callback = CCCallFuncN::create(_callbackTarget, _onMoveToPointCompleteFunc);
//	CCFiniteTimeAction* action = CCSequence::create(moveAction, callback, NULL);

	_skin->runAction(actionScale);
}

void MapObject::hide() {
	CCLog("HIDE ITEM");
	/*
	_skin->cleanup();
	CCNode *parent = _skin->getParent();
	parent->removeChild(_skin);
	_skin = CCParticleExplosion::create();
	initOptions();
//	_skin->setSpeed(200);
	_skin->setSpeedVar(200);
	_skin->setPosition(_pos);
	parent->addChild(_skin);*/
	_skin->setSpeed(300);
	_skin->setLife(0.2);
	_skin->setLifeVar(0.2);

	//CCScaleTo *actionScale = CCScaleTo::create(1,0);

//	_skin->runAction(actionScale);
}
