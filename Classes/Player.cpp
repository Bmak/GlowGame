/*
 * Player.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: probigi
 */

#include "Player.h"

USING_NS_CC;

Player::Player() {
}

void Player::create() {
	//if (_skins == NULL) {
		_skins = new std::vector<CCParticleSystem*>();
	//}

	_speed = 500;

	//if (_velocityes== NULL) {
		_velocityes = new std::vector<CCPoint*>();
	//}
	//if (_targets== NULL) {
		_targets = new std::vector<CCPoint*>();
	//}

	activeTouches = 1;

	addSkin();
}

void Player::addSkin() {
	CCParticleSystem* skin = new CCParticleSystem();
	skin = CCParticleMeteor::create();
	skin->setStartColor(ccc4f(1,1,1,1));
	skin->setGravity(ccp(-200,0));
	skin->setStartSize(50);
	skin->setStartSizeVar(50);
	CCSize *size = new CCSize(30, 30);
	skin->setContentSize(*size);

	_skins->push_back(skin);

	CCPoint *v = new CCPoint(0,0);
	CCPoint *t = new CCPoint(0,0);
	_velocityes->push_back(v);
	_targets->push_back(t);

	if (_skins->size() > 1) {
		CCParticleSystem* first = _skins->front();
		skin->setPosition(first->getPosition());
		first->getParent()->addChild(skin);
	}

	delete size;
}

void Player::removeSkin(int id) {
	CCParticleSystem *skin = _skins->at(id);
	skin->setAutoRemoveOnFinish(true);
	skin->stopSystem();
	_skins->erase(_skins->begin()+id);
	_targets->erase(_targets->begin() + id);
	_velocityes->erase(_velocityes->begin() + id);
}

std::vector<CCParticleSystem*>* Player::getNodes() {
	return _skins;
}

void Player::tick(float dt) {
//	int size = _skins->size();
	for (unsigned i = 0; i < _skins->size(); ++i) {
		CCParticleSystem* skin = _skins->at(i);
		if (activeTouches == 1 && i > 0) {
			CCParticleSystem* first = _skins->at(0);
			moveTo(i, first->getPositionX(), first->getPositionY());
			if (checkClonePos(i)) {
				removeSkin(i);
				i--;
				continue;
			}
		}
		CCPoint* target = _targets->at(i);
		CCPoint* velocity = _velocityes->at(i);

		//if (target->x != 0 || target->y != 0) {
			CCPoint pos = skin->getPosition();

			int dx = target->x - pos.x;
			int dy = target->y - pos.y;
			if (abs(dx) <= 5 && abs(dy) <= 5) {
				continue;
			}

			skin->setPositionX((pos.x + velocity->x * dt));
			skin->setPositionY((pos.y + velocity->y * dt));
		//}
	}
}

bool Player::checkClonePos(int id) {
	CCParticleSystem *front = _skins->at(0);
	CCParticleSystem *skin = _skins->at(id);

	CCPoint pos = skin->getPosition();
	int dx = front->getPositionX() - pos.x;
	int dy = front->getPositionY() - pos.y;
	if (abs(dx) <= 10 && abs(dy) <= 10) {
		return true;
	}
	return false;
}

void Player::setSkin(int id, CCParticleSystem *item) {
	//for (int i = 0; i < _skins->size(); ++i) {
		CCParticleSystem* skin = _skins->at(id);
		skin->setStartColor(item->getStartColor());
		skin->setStartColorVar(item->getStartColorVar());
		skin->setEndColor(item->getEndColor());
		skin->setEndColorVar(item->getEndColorVar());
	//}
}

void Player::moveTo(int id, float tx, float ty) {
	CCParticleSystem* skin = _skins->at(id);
	if (skin == NULL) { return; }
	CCPoint* target = _targets->at(id);

	target->x = tx;
	target->y = ty;

	CCPoint pos = skin->getPosition();

	float dx = target->x - pos.x;
	float dy = target->y - pos.y;

	float h = (float) sqrt((double) (dx * dx + dy * dy));
	float vx = dx / h * _speed;
	float vy = dy / h * _speed;

	setVelocity(id, vx, vy);
}

void Player::setVelocity(int id, float vx, float vy) {
	CCPoint *velocity = _velocityes->at(id);
	if (velocity == NULL) { return; }

	velocity->x = vx;
	velocity->y = vy;
}

