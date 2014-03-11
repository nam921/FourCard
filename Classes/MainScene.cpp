#include "MainScene.h"
#include "MainContentLayers.h"

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	/* menu */
	layer_menu = LayerColor::create(Color4B(60, 60, 60, 255));
	layer_menu->setContentSize(Size(visibleSize.width, 55.0f));
	layer_menu->setPosition(0.0f, visibleSize.height - layer_menu->getContentSize().height);

	menu_menu = Menu::create();
	menu_menu->setContentSize(Size(208.0f, 32.0f));
	menu_menu->setPosition(154.0f, layer_menu->getContentSize().height / 2);

	menuItem_menu_main = MenuItemImage::create("sprites/main/menu/main_disabled.png", "sprites/main/menu/main_enabled.png", "sprites/main/menu/main_enabled.png", [=] (Object* pSender) {
		this->changeContent(menuItem_menu_main, 0);
	});
	menuItem_menu_main->setPosition(0.0f, 0.0f);
	menuItem_menu_main->setContentSize(Size(32.0f, 32.0f));
	
	menu_menu->addChild(menuItem_menu_main);

	menuItem_menu_rank = MenuItemImage::create("sprites/main/menu/rank_disabled.png", "sprites/main/menu/rank_enabled.png", "sprites/main/menu/rank_enabled.png", [=] (Object* pSender) {
		this->changeContent(menuItem_menu_rank, 1);
	});
	menuItem_menu_rank->setPosition(44.0f, 0.0f);
	
	menu_menu->addChild(menuItem_menu_rank);

	menuItem_menu_help = MenuItemImage::create("sprites/main/menu/help_disabled.png", "sprites/main/menu/help_enabled.png", "sprites/main/menu/help_enabled.png", [=] (Object* pSender) {
		this->changeContent(menuItem_menu_help, 2);
	});
	menuItem_menu_help->setPosition(88.0f, 0.0f);
	
	menu_menu->addChild(menuItem_menu_help);

	menuItem_menu_setting = MenuItemImage::create("sprites/main/menu/setting_disabled.png", "sprites/main/menu/setting_enabled.png", "sprites/main/menu/setting_enabled.png", [=] (Object* pSender) {
		this->changeContent(menuItem_menu_setting, 3);
	});
	menuItem_menu_setting->setPosition(132.0f, 0.0f);
	
	menu_menu->addChild(menuItem_menu_setting);

	menuItem_menu_info = MenuItemImage::create("sprites/main/menu/info_disabled.png", "sprites/main/menu/info_enabled.png", "sprites/main/menu/info_enabled.png", [&] (Object* pSender) {
		this->changeContent(menuItem_menu_info, 4);
	});
	menuItem_menu_info->setPosition(176.0f, 0.0f);
	
	menu_menu->addChild(menuItem_menu_info);

	layer_menu->addChild(menu_menu);

	this->addChild(layer_menu);

	/* content */
	
	layer_content_main = MainContentMainLayer::create();
	layer_content_rank = MainContentRankLayer::create();
	layer_content_help = MainContentHelpLayer::create();
	layer_content_setting = MainContentSettingLayer::create();
	layer_content_info = MainContentInfoLayer::create();

	layer_content = LayerMultiplex::create(layer_content_main, layer_content_rank, layer_content_help, layer_content_setting, layer_content_info, nullptr);
	layer_content->setContentSize(Size(visibleSize.width, 625.0f));
	layer_content->setPosition(0.0f, 120.0f);
	
	layer_content_main->setContentSize(layer_content->getContentSize());
	layer_content_rank->setContentSize(layer_content->getContentSize());
	layer_content_help->setContentSize(layer_content->getContentSize());
	layer_content_setting->setContentSize(layer_content->getContentSize());
	layer_content_info->setContentSize(layer_content->getContentSize());
	
	this->addChild(layer_content);

	/* game start */

	layer_game_start = LayerColor::create(Color4B(245, 245, 245, 255));
	layer_game_start->setContentSize(Size(visibleSize.width, 120.0f));
	layer_game_start->setPosition(0.0f, 0.0f);

	menu_game_start = Menu::create();
	menu_game_start->setPosition(layer_game_start->getContentSize().width / 2, layer_game_start->getContentSize().height / 2);
	
	menuItem_game_start = MenuItemImage::create("sprites/main/game_start.png", "sprites/main/game_start.png", [] (Object* pSender) {
		Packet packet(1);
		packet << "cocos2d" << 3;
		FourCard::client->sync_send(packet);
		FourCard::client->sync_recv(packet);
		cocos2d::log("%s", packet.toString("s4").c_str());
	});
	
	LabelTTF* label_game_start = LabelTTF::create("���� ����", "", 20.0f, menuItem_game_start->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_game_start->setPosition(menuItem_game_start->getContentSize().width / 2, menuItem_game_start->getContentSize().height / 2);
	label_game_start->setColor(Color3B(255, 255, 255));

	menuItem_game_start->addChild(label_game_start);

	menu_game_start->addChild(menuItem_game_start);

	layer_game_start->addChild(menu_game_start);
	
	this->addChild(layer_game_start);

	menuItem_menu_current = menuItem_menu_main;
	menuItem_menu_current->setEnabled(false);
	layer_content->switchTo(0);

    return true;
}

void MainScene::changeContent(MenuItemImage* menuItem, int index)
{
	menuItem_menu_current->setEnabled(true);
	menuItem_menu_current = menuItem;
	menuItem_menu_current->setEnabled(false);
	layer_content->switchTo(index);
}