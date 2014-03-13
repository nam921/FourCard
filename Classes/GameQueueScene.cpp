#include "GameQueueScene.h"

Scene* GameQueueScene::createScene(int32_t queue_type, const vector<string>& queue_user_list)
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameQueueScene::create();
	
	layer->m_queue_type = queue_type;
	layer->m_queue_user_list = queue_user_list;
	layer->m_queue_time = 0.0f;
	layer->m_queue_packet_received = false;

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameQueueScene::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	label_time = LabelTTF::create("00:00", "", 18.0f, Size(visibleSize.width, 680.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_time->setPosition(0.0f, 0.0f);
	label_time->setContentSize(Size(visibleSize.width, 680.0f));
	label_time->setAnchorPoint(Point(0.0f, 0.0f));

	this->addChild(label_time);

	LayerColor* layer_menu = LayerColor::create(Color4B(245, 245, 245, 255));
	layer_menu->setContentSize(Size(visibleSize.width, 120.0f));
	layer_menu->setPosition(0.0f, 0.0f);

	Menu* menu_menu = Menu::create();
	menu_menu->setPosition(layer_menu->getContentSize().width / 2, layer_menu->getContentSize().height / 2);
	
	MenuItemImage* menuItem_menu_dequeue = MenuItemImage::create("sprites/game/queue/button.png", "sprites/game/queue/button.png", [] (Object* pSender) {
	});
	
	LabelTTF* label_menu_dequeue = LabelTTF::create("³ª°¡±â", "", 18.0f, menuItem_menu_dequeue->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_menu_dequeue->setPosition(menuItem_menu_dequeue->getContentSize().width / 2, menuItem_menu_dequeue->getContentSize().height / 2);
	label_menu_dequeue->setColor(Color3B(255, 255, 255));

	menuItem_menu_dequeue->addChild(label_menu_dequeue);
	menu_menu->addChild(menuItem_menu_dequeue);

	layer_menu->addChild(menu_menu);
	
	this->addChild(layer_menu);

    return true;
}

void GameQueueScene::update(float dt)
{
	m_queue_time += dt;

	char time[6];
	sprintf_s(time, sizeof(time), "%2d:%2d", (int) m_queue_time / 60, (int) m_queue_time % 60);

	label_time->setString(time);

	if(m_queue_packet_received) {
		if(m_queue_status == PROTOCOL_GAME_QUEUE_ENQUEUE_SUCCESS) {
		}
		else if(m_queue_status == PROTOCOL_GAME_QUEUE_ENQUEUE_ERROR) {
		}
	}
}