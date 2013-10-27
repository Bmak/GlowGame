#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Player;
class MapObject;

class GameScene : public cocos2d::CCLayer
{
public:


    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void deleteItem();

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
    void update(float dt);
    int checkCollisions(MapObject *item);

    int NUM_ITEMS;

    std::vector<MapObject*> *_items;


    Player *_player;

    MapObject *_item;
};


#endif // __GAMESCENE_SCENE_H__
