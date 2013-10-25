#include "HelloWorldScene.h"
#include "Player.h"
#include "MapObject.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                        menu_selector(HelloWorld::menuCloseCallback));
    
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
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
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
    

    _player = new Player();
    _player->create();

    this->addChild(_player->getNode(), 1);

    _item = new MapObject();
    _item->create();
    _item->setPosition(400,400);
    this->addChild(_item->getNode(),1);

    _item->show();


    this->setTouchEnabled(true);
    this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt) {
	_player->tick(dt);
	_item->tick(dt);

	if (checkCollisions() && _item->isLive()) {
		CCLog("CRAAAAAASH!!!");
		_player->getNode()->setStartColor(_item->getNode()->getStartColor());
		_player->getNode()->setStartColorVar(_item->getNode()->getStartColorVar());
		_player->getNode()->setEndColor(_item->getNode()->getEndColor());
		_player->getNode()->setEndColorVar(_item->getNode()->getEndColorVar());

		_item->setLive(false);
		_item->hide();


	}
}

bool HelloWorld::checkCollisions() {
	CCRect rect1 = _player->getNode()->boundingBox();
	CCRect rect2 = _item->getNode()->boundingBox();

	return rect1.intersectsRect(rect2);
}


void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	ccTouchesEnded(pTouches, pEvent);
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	ccTouchesEnded(pTouches, pEvent);
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)pTouches->anyObject();

	CCPoint target = touch->getLocation();
	_player->moveTo(target.x,target.y);

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


void HelloWorld::menuCloseCallback(CCObject* pSender)
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
