/*
 * Player.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: probigi
 */

#include "Player.h"

USING_NS_CC;

Player::Player() { }

void Player::create() {
	_skin = new CCParticleSystem();
	_skin = CCParticleMeteor::create();
	_skin->setGravity(ccp(-300,0));
	_skin->setStartColor(ccc4f(1.0f,1.0f,1.0f,1.0f));
//	_skin->setStartColorVar(ccc4f(1.0f,1.0f,1.0f,1.0f));

	_skin->setEndColor(ccc4f(1.0f,1.0f,1.0f,0.1f));
	//_skin->setEndColorVar(ccc4f(1.0f,1.0f,1.0f,1.0f));

//	_skin->setStartColorVar(ccc4f(50,50,0,50));
//	_skin->setEndColorVar(ccc4f(150,150,150,0));
	_skin->setStartSize(50);
	_skin->setStartSizeVar(50);
//	CCRect rect = _skin->boundingBox();
//	rect = new CCRect(-10,-10,20,20);

	CCSize *size = new CCSize(30,30);
	_skin->setContentSize(*size);

	_speed = 500;
	_target = CCPointZero;
	_velocity = CCPointZero;

	delete size;
}

CCParticleSystem* Player::getNode() {
	return _skin;
}

void Player::tick(float dt) {
	if (_target.x != 0 || _target.y != 0) {
		_pos = _skin->getPosition();

		int dx = _target.x - _pos.x;
		int dy = _target.y - _pos.y;
		if (abs(dx) <= 5 && abs(dy) <= 5) { return; }

		_skin->setPositionX((_pos.x + _velocity.x*dt));
		_skin->setPositionY((_pos.y + _velocity.y*dt));
	}
}

void Player::moveTo(float tx, float ty) {
	_target.x = tx;
	_target.y = ty;

	_pos = _skin->getPosition();

	float dx = _target.x - _pos.x;
	float dy = _target.y - _pos.y;

	float h = (float) sqrt( (double) (dx * dx + dy * dy) );
	float vx = dx / h * _speed;
	float vy = dy / h * _speed;

	setVelocity(vx,vy);
}

void Player::setVelocity(float vx, float vy) {
	_velocity.x = vx;
	_velocity.y = vy;
}

