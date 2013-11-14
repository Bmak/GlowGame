#include "GameScene.h"
#include "Player.h"
#include "MapObject.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("GLOW", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
    


//    CCParticleSystem *ex1 = new CCParticleSystem();
//    ex1 = CCParticleFireworks::create();
//	ex1 = CCParticleFire::create();
//	ex1 = CCParticleExplosion::create();
//	ex1 = CCParticleFlower::create();
//	ex1 = CCParticleGalaxy::create();
//    ex1 = CCParticleMeteor::create();
//    ex1 = CCParticleRain::create();
//    ex1 = CCParticleSmoke::create();
//    ex1 = CCParticleSnow::create();
//    ex1 = CCParticleSpiral::create();
//    ex1 = CCParticleSun::create();
//	this->addChild(ex1);

    //_player = new Player();
    //_player->create();

    //CCParticleSystem* node = _player->getNodes()->front();
	//this->addChild(node, 1);

    NUM_ITEMS = 0;
    MAX_TOUCHES = 3;

	_items = new std::vector<MapObject*>();
	for (int i = 0; i < NUM_ITEMS; ++i) {
		MapObject *item = new MapObject();
		item->create(i);
		this->addChild(item->getNode());
		_items->push_back(item);
		item->show();
	}

	MAX_ASTERS = 10;

	_asteroids = new std::vector<Player*>();
	for (int i = 0; i < MAX_ASTERS; ++i) {
		Player *aster = new Player();
		aster->create();
		CCParticleSystem* node = aster->getNodes()->front();
		this->addChild(node);
		_asteroids->push_back(aster);
		aster->redraw();
	}

    this->setTouchEnabled(true);
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
	/*_player->tick(dt);

	for (int i = 0; i < NUM_ITEMS; ++i) {
		MapObject *item = _items->at(i);
		item->tick(dt);

		int id = checkCollisions(item);
		if (id != -1 && item->isLive()) {
			_player->setSkin(id, item->getNode());

			item->setLive(false);
			item->hide();
		}
	}*/

	for (int i = 0; i < MAX_ASTERS; ++i) {
		Player* aster = _asteroids->at(i);
		aster->tick(dt);

		aster->checkForRemove();

		if (!aster->isLive) {
			aster->removeSkin(0);
			aster->addSkin();
			CCParticleSystem* node = aster->getNodes()->front();
			this->addChild(node);
			aster->redraw();
		}
	}
}

int GameScene::checkCollisions(MapObject *item) {
	CCRect rect1 = item->getNode()->boundingBox();
	for (unsigned i = 0; i < _player->getNodes()->size(); ++i) {
		CCRect rect2 = _player->getNodes()->at(i)->boundingBox();
		if (rect2.intersectsRect(rect1)) {
			return i;
		}
	}
	return -1;
}

void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	ccTouchesEnded(pTouches, pEvent);
}

void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	ccTouchesEnded(pTouches, pEvent);
}

void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *touch = (CCTouch*) *it;
		CCPoint target = touch->getLocation();

		for (int i = 0; i < MAX_ASTERS; ++i) {
			Player *aster = _asteroids->at(i);
			if (!aster->isLive) { continue; }
			CCRect rect = aster->getNodes()->at(0)->boundingBox();
			if (rect.containsPoint(target)) {
				aster->isLive = false;
			}
		}
	}
}

/*
void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	int count = pTouches->count();
	if (count > MAX_TOUCHES) { count = MAX_TOUCHES; }
	if (count > 1) {
		int nodes = _player->getNodes()->size();
		if (nodes < count) {
			int len = count - nodes;
			for (int j = 0; j < len; ++j) {
				_player->addSkin();
			}
		}
		_player->activeTouches = count;

		int i = 0;

		for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
			if (i >= MAX_TOUCHES) { break; }
			CCTouch *touch = (CCTouch*) *it;
			CCPoint target = touch->getLocation();

			_player->moveTo(i, target.x,target.y);
			i++;
		}
	} else {
		CCTouch *touch = (CCTouch*)pTouches->anyObject();

		CCPoint target = touch->getLocation();

		_player->moveTo(0, target.x,target.y);
		_player->activeTouches = 1;
	}

}
*/

void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
