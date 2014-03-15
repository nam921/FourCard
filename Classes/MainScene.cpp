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
	menu_game_start->setContentSize(Size(371.0f, 74.0f));
	
	menuItem_game_start_create_room = MenuItemImage::create("sprites/main/game_start_button.png", "sprites/main/game_start_button.png", [] (Object* pSender) {
	});
	menuItem_game_start_create_room->setPosition(0.0f, 0.0f);
	
	LabelTTF* label_game_start_create_room = LabelTTF::create("방 만들기", "", 20.0f, menuItem_game_start->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_game_start_create_room->setPosition(menuItem_game_start_create_room->getContentSize().width / 2, menuItem_game_start_create_room->getContentSize().height / 2);
	label_game_start_create_room->setColor(Color3B(255, 255, 255));

	menuItem_game_start_create_room->addChild(label_game_start_create_room);

	menu_game_start->addChild(menuItem_game_start_create_room);

	menuItem_game_start = MenuItemImage::create("sprites/main/game_start_button.png", "sprites/main/game_start_button.png", [=] (Object* pSender) {
		Dialog* dialog = Dialog::create();

		Layer* layer_queue_select = Layer::create();
		layer_queue_select->setContentSize(Size(211.0f, 100.0f));

		Menu* menu_queue_select = Menu::create();
		menu_queue_select->setContentSize(layer_queue_select->getContentSize());

		LabelTTF* label_queue_select_normal = LabelTTF::create("일반", "", 30.0f, Size(100.0f, 100.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_queue_select_normal->setAnchorPoint(Point(0.0f, 0.0f));
		label_queue_select_normal->setColor(Color3B(255, 255, 255));

		MenuItemLabel* menuItem_queue_select_normal = MenuItemLabel::create(label_queue_select_normal, [=] (Object* pSender) {
			list<string> queue_user_list;
			queue_user_list.push_back(User::getLoggedInUser().m_id);

			Director::getInstance()->replaceScene(GameQueueScene::createScene(PROTOCOL_GAME_QUEUE_ENQUEUE_NORMAL, queue_user_list));

			this->removeChild(dialog);
		});
		menuItem_queue_select_normal->setPosition(0.0f, 0.0f);
		menuItem_queue_select_normal->setAnchorPoint(Point(0.0f, 0.0f));

		DrawObject* draw_queue_select_normal = DrawObject::create();
		draw_queue_select_normal->setOnDraw([=] () {
			DrawPrimitives::drawSolidRect(Point(0.0f, 0.0f), Point(draw_queue_select_normal->getContentSize()), Color4F(Color3B(115, 162, 191)));
		});
		draw_queue_select_normal->setContentSize(label_queue_select_normal->getContentSize());

		menuItem_queue_select_normal->addChild(draw_queue_select_normal);

		menu_queue_select->addChild(menuItem_queue_select_normal);

		DrawObject* draw_queue_select_seperator = DrawObject::create();
		draw_queue_select_seperator->setOnDraw([] () {
			DrawPrimitives::setDrawColor4B(127, 127, 127, 255);
			DrawPrimitives::drawLine(Point(110.0f, 15.0f), Point(110.0f, 85.0f));
		});
		draw_queue_select_seperator->setContentSize(Size(1.0f, 70.0f));

		menu_queue_select->addChild(draw_queue_select_seperator);

		LabelTTF* label_queue_select_rank = LabelTTF::create("랭크", "", 30.0f, Size(100.0f, 100.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_queue_select_rank->setAnchorPoint(Point(0.0f, 0.0f));
		label_queue_select_rank->setColor(Color3B(255, 255, 255));

		MenuItemLabel* menuItem_queue_select_rank = MenuItemLabel::create(label_queue_select_rank, [=] (Object* pSender) {
			list<string> queue_user_list;
			queue_user_list.push_back(User::getLoggedInUser().m_id);

			Director::getInstance()->replaceScene(GameQueueScene::createScene(PROTOCOL_GAME_QUEUE_ENQUEUE_RANK, queue_user_list));

			this->removeChild(dialog);
		});
		menuItem_queue_select_rank->setPosition(111.0f, 0.0f);
		menuItem_queue_select_rank->setAnchorPoint(Point(0.0f, 0.0f));

		DrawObject* draw_queue_select_rank = DrawObject::create();
		draw_queue_select_normal->setOnDraw([=] () {
			DrawPrimitives::drawSolidRect(Point(0.0f, 0.0f), Point(draw_queue_select_rank->getContentSize()), Color4F(Color3B(224, 135, 135)));
		});
		draw_queue_select_rank->setContentSize(label_queue_select_rank->getContentSize());

		menuItem_queue_select_rank->addChild(draw_queue_select_rank);

		menu_queue_select->addChild(menuItem_queue_select_rank);

		layer_queue_select->addChild(menu_queue_select);

		dialog->setTitle("게임 대기열 종류 선택");
		dialog->setMessage("");
		dialog->setLayer(layer_queue_select);
		dialog->addButton("확인", [=] () {
			this->removeChild(dialog);
		});
		dialog->updateLayout();

		this->addChild(dialog);
	});
	menuItem_game_start->setPosition(191.0f, 0.0f);
	
	LabelTTF* label_game_start = LabelTTF::create("게임 시작", "", 20.0f, menuItem_game_start->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
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
