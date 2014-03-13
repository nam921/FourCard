#ifndef __GAME_QUEUE_SCENE_H__
#define __GAME_QUEUE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameQueueScene : public cocos2d::LayerColor
{
private:
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameQueueScene);
};

#endif // __GAME_QUEUE_SCENE_H__
