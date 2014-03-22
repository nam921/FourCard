#include "SplashScene.h"
#include "MainScene.h"

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	
	/* 스플래시 애니메이션 시작 */
	Sprite* sprite = Sprite::create("sprites/splash/1.png");
	sprite->setAnchorPoint(Point(0.0f, 0.0f));

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(1.0f);

	for(int i=1; i<=4; i++) {
		animation->addSpriteFrameWithFile(__stringf("sprites/splash/%d.png", i).c_str());
	}

	CallFunc* callFunc = CallFunc::create(std::bind(&SplashScene::onSplashFinished, this));
	// 스플래시 애니메이션이 끝났을 때 함수를 호출하기 위한 콜백

	sprite->runAction(Sequence::create(Animate::create(animation), callFunc, nullptr));
	this->addChild(sprite);

	/* 스플래시 애니메이션 끝 */

	/* 터치했을 때 스플래시 스킵 시작 */

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&] (Touch *touch, Event *event) -> bool {
		return true;
	};
	listener->onTouchEnded = [&] (Touch *touch, Event *event) {
		this->onSplashFinished();
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
    
	/* 터치했을 때 스플래시 스킵 끝 */

    return true;
}
void SplashScene::onSplashFinished()
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}
