#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SplashScene.h"
#include "FourCard.h"
#include "Dialog.h"
#include "User.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScene : public cocos2d::LayerColor
{
private:
	Layer *layer_register;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);

	~LoginScene();
};

#endif // __LOGIN_SCENE_H__
