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
	_player = new CCParticleSystem();
	_player = CCParticleMeteor::create();
	_player->setGravity(ccp(-300,0));
//	_player->setStartColor(ccc4f(1.0f,0,0.0f,1.0f));
//	_player->setStartColorVar(ccc4f(0.0f,1,0.0f,0.1f));

	_player->setStartColorVar(ccc4f(50,50,0,50));
	_player->setEndColorVar(ccc4f(150,150,150,0));
	_player->setStartSize(50);
	_player->setStartSizeVar(50);

	_speed = 500;
	_target = CCPointZero;
	_velocity = CCPointZero;
}

CCParticleSystem* Player::getNode() {
	return _player;
}

void Player::tick(float dt) {

	if (_target.x != 0 || _target.y != 0) {
		_pos = _player->getPosition();

		if (_target.x == _pos.x && _target.y == _pos.y) { return; }

		int dx = _target.x - _pos.x;
		int dy = _target.y - _pos.y;
		if (abs(dx) <= 5 && abs(dy) <= 5) { return; }

		_player->setPositionX((_pos.x + _velocity.x*dt));
		_player->setPositionY((_pos.y + _velocity.y*dt));
	}
}

void Player::moveTo(float tx, float ty) {
	_target.x = tx;
	_target.y = ty;

	_pos = _player->getPosition();

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

