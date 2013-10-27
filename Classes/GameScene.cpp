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

    _player = new Player();
    _player->create();

    CCParticleSystem* node = _player->getNodes()->front();
	this->addChild(node, 1);

    NUM_ITEMS = 3;

	_items = new std::vector<MapObject*>();
	for (int i = 0; i < NUM_ITEMS; ++i) {
		MapObject *item = new MapObject();
		item->create(i);
		this->addChild(item->getNode());
		_items->push_back(item);
		item->show();
	}

    this->setTouchEnabled(true);
    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
	_player->tick(dt);

	for (int i = 0; i < NUM_ITEMS; ++i) {
		MapObject *item = _items->at(i);
		item->tick(dt);

		int coll = checkCollisions(item);
		if (coll != -1 && item->isLive()) {
			_player->setSkin(coll, item->getNode());

			item->setLive(false);
			item->hide();
		}
	}
}

int GameScene::checkCollisions(MapObject *item) {
	CCRect rect1 = item->getNode()->boundingBox();
	int size = _player->getNodes()->size();
	for (int i = 0; i < size; ++i) {
		CCRect rect2 = _player->getNodes()->at(i)->boundingBox();
		if (rect2.intersectsRect(rect1)) {
			return i;
		}
	}
	return -1;
}

void GameScene::deleteItem() {
	CCLog("WTF!!!!");
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
	int size = pTouches->count();
	if (size > 3) { size = 3; }
	int nodes = _player->getNodes()->size();
	if (size > 1) {
		if (nodes < size) {
			int len = size - nodes;
			for (int j = 0; j < len; ++j) {
				_player->addSkin();
			}
		}
		_player->activeTouches = size;

		int i = 0;

		for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
		{
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


    //CCTouch *touch = (CCTouch*)pTouches->anyObject();

    //CCPoint location = touch->getLocation();

    //CCPoint pos = CCPointZero;
    /*
    if (m_background)
    {
        pos = m_background->convertToWorldSpace(CCPointZero);
    }
	*/
	/*
    if (_player != NULL)
    {
    	//_player->setPosition( ccpSub(location, pos) );
    	CCMoveTo* moveAction = CCMoveTo::create(.5, location);
    	_player->runAction(moveAction);

    }*/
}


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
