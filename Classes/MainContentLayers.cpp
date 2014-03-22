#include "MainContentLayers.h"

// on "init" you need to initialize your instance
bool MainContentMainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	User logged_in_user = User::getLoggedInUser();

	Sprite* sprite_logo = Sprite::create("sprites/main/logo.png");
	sprite_logo->setPosition(visibleSize.width / 2, 411.0f);
	sprite_logo->setAnchorPoint(Point(0.5f, 0.0f));

	this->addChild(sprite_logo);

	LabelTTF* label_name = LabelTTF::create(logged_in_user.m_nickname, FourCard::DEFAULT_FONT, 16.0f);
	label_name->setPosition(135.0f, 369.0f);
	label_name->setAnchorPoint(Point(0.0f, 0.0f));
	label_name->setColor(Color3B(0,0,0));

	this->addChild(label_name);

	Sprite* sprite_name_box = Sprite::create("sprites/main/name_box.png");
	sprite_name_box->setPosition(130.0f, 364.0f);
	sprite_name_box->setAnchorPoint(Point(0.0f, 0.0f));

	this->addChild(sprite_name_box);

	LabelTTF* label_record_total = LabelTTF::create(__stringf("%d", logged_in_user.m_win + logged_in_user.m_lose), FourCard::DEFAULT_FONT, 16.0f);
	label_record_total->setPosition(135.0f, 324.0f);
	label_record_total->setAnchorPoint(Point(0.0f, 0.0f));
	label_record_total->setColor(Color3B(0,0,0));

	this->addChild(label_record_total);

	Sprite* sprite_record_total_box = Sprite::create("sprites/main/record_box.png");
	sprite_record_total_box->setPosition(130.0f, 319.0f);
	sprite_record_total_box->setAnchorPoint(Point(0.0f, 0.0f));

	this->addChild(sprite_record_total_box);

	LabelTTF* label_record_win = LabelTTF::create(__stringf("%d", logged_in_user.m_win), FourCard::DEFAULT_FONT, 16.0f);
	label_record_win->setPosition(211.0f, 324.0f);
	label_record_win->setAnchorPoint(Point(0.0f, 0.0f));
	label_record_win->setColor(Color3B(0,0,0));

	this->addChild(label_record_win);

	Sprite* sprite_record_win_box = Sprite::create("sprites/main/record_box.png");
	sprite_record_win_box->setPosition(206.0f, 319.0f);
	sprite_record_win_box->setAnchorPoint(Point(0.0f, 0.0f));

	this->addChild(sprite_record_win_box);

	LabelTTF* label_record_lose = LabelTTF::create(__stringf("%d", logged_in_user.m_lose), FourCard::DEFAULT_FONT, 16.0f);
	label_record_lose->setPosition(286.0f, 324.0f);
	label_record_lose->setAnchorPoint(Point(0.0f, 0.0f));
	label_record_lose->setColor(Color3B(0,0,0));

	this->addChild(label_record_lose);

	Sprite* sprite_record_lose_box = Sprite::create("sprites/main/record_box.png");
	sprite_record_lose_box->setPosition(281.0f, 319.0f);
	sprite_record_lose_box->setAnchorPoint(Point(0.0f, 0.0f));

	this->addChild(sprite_record_lose_box);

	LabelTTF* label_rate = LabelTTF::create(__stringf("´ç½ÅÀÇ ½Â·ü %d%", (int) ((double) logged_in_user.m_win / (logged_in_user.m_win + logged_in_user.m_lose) * 100.0)), FourCard::DEFAULT_FONT, 30.0f, Size(visibleSize.width, 44.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_rate->setPosition(0.0f, 255.0f);
	label_rate->setAnchorPoint(Point(0.0f, 0.0f));
	label_rate->setHorizontalAlignment(TextHAlignment::CENTER);
	label_rate->setColor(Color3B(0,0,0));

	this->addChild(label_rate);

	Sprite* sprite_profile = Sprite::create("sprites/main/profile.png");
	sprite_profile->setPosition(visibleSize.width / 2, 25.0f);
	sprite_profile->setAnchorPoint(Point(0.5f, 0.0f));

	this->addChild(sprite_profile);

    return true;
}

// on "init" you need to initialize your instance
bool MainContentRankLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	menuItem_category_recent = MenuItemLabel::create(LabelTTF::create("ÃÖ±Ù", FourCard::DEFAULT_FONT, 18.0f, Size(88.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER), [=] (Object* pSender) {
		this->changeLayer(menuItem_category_recent, 0);
	});
	menuItem_category_recent->setScale(1.0f);
	menuItem_category_recent->setPosition(0.0f, 0.0f);
	menuItem_category_recent->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_category_recent->setColor(Color3B(140, 140, 140));
	menuItem_category_recent->setDisabledColor(Color3B(60, 60, 60));

	menuItem_category_winrate = MenuItemLabel::create(LabelTTF::create("½Â·ü", FourCard::DEFAULT_FONT, 18.0f, Size(88.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER), [=] (Object* pSender) {
		this->changeLayer(menuItem_category_winrate, 1);
	});
	menuItem_category_winrate->setPosition(88.0f, 0.0f);
	menuItem_category_winrate->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_category_winrate->setColor(Color3B(140, 140, 140));
	menuItem_category_winrate->setDisabledColor(Color3B(60, 60, 60));

	menuItem_category_win = MenuItemLabel::create(LabelTTF::create("´Ù½Â", FourCard::DEFAULT_FONT, 18.0f, Size(88.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER), [=] (Object* pSender) {
		this->changeLayer(menuItem_category_win, 2);
	});
	menuItem_category_win->setPosition(176.0f, 0.0f);
	menuItem_category_win->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_category_win->setColor(Color3B(140, 140, 140));
	menuItem_category_win->setDisabledColor(Color3B(60, 60, 60));

	menuItem_category_lose = MenuItemLabel::create(LabelTTF::create("´ÙÆÐ", FourCard::DEFAULT_FONT, 18.0f, Size(88.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER), [=] (Object* pSender) {
		this->changeLayer(menuItem_category_lose, 3);
	});
	menuItem_category_lose->setPosition(264.0f, 0.0f);
	menuItem_category_lose->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_category_lose->setColor(Color3B(140, 140, 140));
	menuItem_category_lose->setDisabledColor(Color3B(60, 60, 60));

	menuItem_category_total = MenuItemLabel::create(LabelTTF::create("´ÙÀü", FourCard::DEFAULT_FONT, 18.0f, Size(88.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER), [=] (Object* pSender) {
		this->changeLayer(menuItem_category_total, 4);
	});
	menuItem_category_total->setPosition(352.0f, 0.0f);
	menuItem_category_total->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_category_total->setColor(Color3B(140, 140, 140));
	menuItem_category_total->setDisabledColor(Color3B(60, 60, 60));

	menu_category = Menu::create(menuItem_category_recent, menuItem_category_winrate, menuItem_category_win, menuItem_category_lose, menuItem_category_total, nullptr);
	menu_category->setPosition(20.0f, 588.0f);
	menu_category->setContentSize(Size(440.0f, 24.0f));

	this->addChild(menu_category);
	
	LayerColor* layer_seperator_1 = LayerColor::create(Color4B(246, 245, 244, 255));
	layer_seperator_1->setPosition(Point(20.0f, 10.0f));
	layer_seperator_1->setContentSize(Size(440.0f, 2.0f));

	this->addChild(layer_seperator_1);

	layer_rank_current = LayerMultiplex::create();
	layer_rank_current->setPosition(25.0f, 13.0f);
	layer_rank_current->setContentSize(Size(430.0f, 560.0f));

	layer_rank_recent = Layer::create();
	layer_rank_recent->setContentSize(layer_rank_current->getContentSize());

	Color4B layer_rank_recent_item_color_table[6] = {
		Color4B(115, 162, 191, 255),
		Color4B(127, 212, 152, 255),
		Color4B(74, 74, 74, 255),
		Color4B(224, 135, 135, 255),
		Color4B(224, 135, 135, 255),
		Color4B(224, 135, 135, 255)
	};

	for(int i=0; i<6; i++) {
		LayerColor* layer_rank_recent_item = LayerColor::create(layer_rank_recent_item_color_table[i], layer_rank_recent->getContentSize().width, 85.0f);
		layer_rank_recent_item->setPosition(0.0f, 460.0f - 90.0f * i);

		LabelTTF* label_rank = LabelTTF::create(__stringf("%dµî", i + 1).c_str(), FourCard::DEFAULT_FONT, 30.0f, Size(70.0f, layer_rank_recent_item->getContentSize().height), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_rank->setPosition(10.0f, 0.0f);
		label_rank->setAnchorPoint(Point(0.0f, 0.0f));
		label_rank->setColor(Color3B(60, 60, 60));

		layer_rank_recent_item->addChild(label_rank);

		for(int j=0; j<4; j++) {
			Layer* layer_rank_recent_detail_item = Layer::create();
			layer_rank_recent_detail_item->setPosition(103.0f + 85.0f * j, 8.0f);
			layer_rank_recent_detail_item->setContentSize(Size(60.0f, 69.0f));

			LabelTTF* label_name = LabelTTF::create(__stringf("%d%d", i, j).c_str(), FourCard::DEFAULT_FONT, 10.0f, Size(layer_rank_recent_detail_item->getContentSize().width, 14.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
			label_name->setPosition(0.0f, 55.0f);
			label_name->setAnchorPoint(Point(0.0f, 0.0f));
			label_name->setColor(i % 4 == j ? Color3B(60, 60, 60) : Color3B(255, 255, 255));

			layer_rank_recent_detail_item->addChild(label_name);

			Sprite* sprite_user = Sprite::create("sprites/main/profile.png");
			sprite_user->setPosition(10.0f, 15.0f);
			sprite_user->setScale(40.0f / sprite_user->getContentSize().width);
			sprite_user->setAnchorPoint(Point(0.0f, 0.0f));

			layer_rank_recent_detail_item->addChild(sprite_user);

			LabelTTF* label_score = LabelTTF::create(__stringf("%d%dÁ¡", i, j).c_str(), FourCard::DEFAULT_FONT, 11.0f, Size(layer_rank_recent_detail_item->getContentSize().width, 15.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
			label_score->setPosition(0.0f, 0.0f);
			label_score->setAnchorPoint(Point(0.0f, 0.0f));
			label_score->setColor(i % 4 == j ? Color3B(60, 60, 60) : Color3B(255, 255, 255));

			layer_rank_recent_detail_item->addChild(label_score);

			layer_rank_recent_item->addChild(layer_rank_recent_detail_item);
		}

		layer_rank_recent->addChild(layer_rank_recent_item);
	}

	layer_rank_current->addLayer(layer_rank_recent);

	layer_rank_winrate = Layer::create();
	layer_rank_winrate->setContentSize(layer_rank_current->getContentSize());

	for(int i=0; i<10; i++) {
		LabelTTF* label_rank = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(40.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_rank->setPosition(0.0f, 504.0f - 56.0f * i);
		label_rank->setAnchorPoint(Point(0.0f, 0.0f));
		label_rank->setColor(Color3B(60, 60, 60));

		layer_rank_winrate->addChild(label_rank);

		LabelTTF* label_name = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(200.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_name->setPosition(50.0f, 504.0f - 56.0f * i);
		label_name->setAnchorPoint(Point(0.0f, 0.0f));
		label_name->setColor(Color3B(60, 60, 60));

		layer_rank_winrate->addChild(label_name);

		LabelTTF* label_win = LabelTTF::create(__stringf("%d%%", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(170.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_win->setPosition(260.0f, 504.0f - 56.0f * i);
		label_win->setAnchorPoint(Point(0.0f, 0.0f));
		label_win->setColor(Color3B(60, 60, 60));

		layer_rank_winrate->addChild(label_win);
	}

	layer_rank_current->addLayer(layer_rank_winrate);

	layer_rank_win = Layer::create();
	layer_rank_win->setContentSize(layer_rank_current->getContentSize());

	for(int i=0; i<10; i++) {
		LabelTTF* label_rank = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(40.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_rank->setPosition(0.0f, 504.0f - 56.0f * i);
		label_rank->setAnchorPoint(Point(0.0f, 0.0f));
		label_rank->setColor(Color3B(60, 60, 60));

		layer_rank_win->addChild(label_rank);

		LabelTTF* label_name = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(200.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_name->setPosition(50.0f, 504.0f - 56.0f * i);
		label_name->setAnchorPoint(Point(0.0f, 0.0f));
		label_name->setColor(Color3B(60, 60, 60));

		layer_rank_win->addChild(label_name);

		LabelTTF* label_win = LabelTTF::create(__stringf("%d½Â", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(170.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_win->setPosition(260.0f, 504.0f - 56.0f * i);
		label_win->setAnchorPoint(Point(0.0f, 0.0f));
		label_win->setColor(Color3B(60, 60, 60));

		layer_rank_win->addChild(label_win);
	}

	layer_rank_current->addLayer(layer_rank_win);

	layer_rank_lose = Layer::create();
	layer_rank_lose->setContentSize(layer_rank_current->getContentSize());

	for(int i=0; i<10; i++) {
		LabelTTF* label_rank = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(40.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_rank->setPosition(0.0f, 504.0f - 56.0f * i);
		label_rank->setAnchorPoint(Point(0.0f, 0.0f));
		label_rank->setColor(Color3B(60, 60, 60));

		layer_rank_lose->addChild(label_rank);

		LabelTTF* label_name = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(200.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_name->setPosition(50.0f, 504.0f - 56.0f * i);
		label_name->setAnchorPoint(Point(0.0f, 0.0f));
		label_name->setColor(Color3B(60, 60, 60));

		layer_rank_lose->addChild(label_name);

		LabelTTF* label_win = LabelTTF::create(__stringf("%dÆÐ", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(170.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_win->setPosition(260.0f, 504.0f - 56.0f * i);
		label_win->setAnchorPoint(Point(0.0f, 0.0f));
		label_win->setColor(Color3B(60, 60, 60));

		layer_rank_lose->addChild(label_win);
	}

	layer_rank_current->addLayer(layer_rank_lose);

	layer_rank_total = Layer::create();
	layer_rank_total->setContentSize(layer_rank_current->getContentSize());

	for(int i=0; i<10; i++) {
		LabelTTF* label_rank = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(40.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_rank->setPosition(0.0f, 504.0f - 56.0f * i);
		label_rank->setAnchorPoint(Point(0.0f, 0.0f));
		label_rank->setColor(Color3B(60, 60, 60));

		layer_rank_total->addChild(label_rank);

		LabelTTF* label_name = LabelTTF::create(__stringf("%d", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(200.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_name->setPosition(50.0f, 504.0f - 56.0f * i);
		label_name->setAnchorPoint(Point(0.0f, 0.0f));
		label_name->setColor(Color3B(60, 60, 60));

		layer_rank_total->addChild(label_name);

		LabelTTF* label_win = LabelTTF::create(__stringf("%dÀü", i + 1).c_str(), FourCard::DEFAULT_FONT, 16.0f, Size(170.0f, 56.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label_win->setPosition(260.0f, 504.0f - 56.0f * i);
		label_win->setAnchorPoint(Point(0.0f, 0.0f));
		label_win->setColor(Color3B(60, 60, 60));

		layer_rank_total->addChild(label_win);
	}

	layer_rank_current->addLayer(layer_rank_total);

	this->addChild(layer_rank_current);
	
	LayerColor* layer_seperator_2 = LayerColor::create(Color4B(246, 245, 244, 255));
	layer_seperator_2->setPosition(Point(20.0f, 574.0f));
	layer_seperator_2->setContentSize(Size(440.0f, 2.0f));

	this->addChild(layer_seperator_2);

	menuItem_category_current = menuItem_category_recent;
	menuItem_category_current->setEnabled(false);
	layer_rank_current->switchTo(0);

    return true;
}

void MainContentRankLayer::changeLayer(MenuItemLabel* menuItem, int index) {
	menuItem_category_current->setEnabled(true);
	menuItem_category_current = menuItem;
	menuItem_category_current->setEnabled(false);
	layer_rank_current->switchTo(index);
}

// on "init" you need to initialize your instance
bool MainContentHelpLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	const int page_count = 8;
	float page_width;

	layer_page = Layer::create();

	for(int i=0; i<page_count; i++) {
		Sprite* sprite = Sprite::create(__stringf("sprites/main/help/page%d.png", i).c_str());
		sprite->setPosition(sprite->getContentSize().width * i, 0.0f);
		sprite->setAnchorPoint(Point(0.0f, 0.0f));

		page_width = sprite->getContentSize().width;

		layer_page->addChild(sprite);
	}

	layer_page->setContentSize(Size(layer_page->getChildren().at(0)->getContentSize().width * page_count, layer_page->getChildren().at(0)->getContentSize().height));

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=] (Touch* touch, Event* e) -> bool {
		Node* target = e->getCurrentTarget();
		Point location = target->convertToNodeSpace(touch->getLocation());
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);

		if(rect.containsPoint(location)) {
			return true;
		}
		else {
			return false;
		}
	};
	listener->onTouchMoved = [=] (Touch* touch, Event* e) {
		float result = layer_page->getPosition().x + touch->getDelta().x;

		cocos2d::log("result = %.0f, delta = %.0f", result, touch->getDelta().x);

		if(result > 0.0f) {
			result = 0.0f;
		}
		else if(result < -page_width * (page_count - 1)) {
			result = -page_width * (page_count - 1);
		}
		else if(result > -page_width * page_index + page_width) {
			result = -page_width * page_index + page_width;
		}
		else if(result < -page_width * page_index - page_width) {
			result = -page_width * page_index - page_width;
		}

		layer_page->setPosition(result, layer_page->getPosition().y);
	};
	listener->onTouchEnded = listener->onTouchCancelled = [=] (Touch* touch, Event* e) {
		float result = layer_page->getPosition().x + touch->getDelta().x;

		if(result > 0.0f) {
			result = 0.0f;
		}
		else if(result < -page_width * (page_count - 1)) {
			result = -page_width * (page_count - 1);
		}
		else if(result > -page_width * page_index + page_width * 0.25f) {
			result = -page_width * page_index + page_width;
		}
		else if(result < -page_width * page_index - page_width * 0.25f) {
			result = -page_width * page_index - page_width;
		}
		else {
			result = -page_width * page_index;
		}

		MoveTo* animation = MoveTo::create(0.3f, Point(result, layer_page->getPosition().y));
		layer_page->runAction(CCEaseOut::create(animation, 1.0f));
		
		page_index = static_cast<int>(-result / page_width);

		menuItem_page_current->setEnabled(true);
		menuItem_page_current = (MenuItemImage*) this->menu_index->getChildren().at(static_cast<ssize_t>(page_index));
		menuItem_page_current->setEnabled(false);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer_page);

	this->addChild(layer_page);

	menu_index = Menu::create();
	menu_index->setContentSize(Size(14.0f * page_count + 12.0f * (page_count - 1), 14.0f));
	menu_index->setPosition((visibleSize.width - menu_index->getContentSize().width) / 2, 20.0f);

	for(int i=0; i<page_count; i++) {
		MenuItemImage* menuItem = MenuItemImage::create("sprites/main/help/index.png", "sprites/main/help/index_current.png", "sprites/main/help/index_current.png", [=] (Object *pSender) {
			changeIndex(layer_page, i);
		});
		menuItem->setPosition(26.0f * i, 0.0f);
		menuItem->setAnchorPoint(Point(0.0f, 0.0f));

		menu_index->addChild(menuItem);
	}

	this->page_index = 0;
	this->menuItem_page_current = (MenuItemImage*) menu_index->getChildren().at(0);
	this->menuItem_page_current->setEnabled(false);

	this->addChild(menu_index);

    return true;
}

void MainContentHelpLayer::changeIndex(Layer* layer_page, int index)
{
	menuItem_page_current->setEnabled(true);
	menuItem_page_current = (MenuItemImage*) this->menu_index->getChildren().at(static_cast<ssize_t>(index));
	menuItem_page_current->setEnabled(false);

	MoveTo* animation = MoveTo::create(0.3f, Point(-layer_page->getContentSize().width / layer_page->getChildrenCount() * index, layer_page->getPosition().y));
	layer_page->runAction(animation);

	page_index = index;
}

// on "init" you need to initialize your instance
bool MainContentSettingLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage* menuItem_notification_enabled = MenuItemImage::create("sprites/main/setting/notification_enabled.png", "sprites/main/setting/notification_disabled.png");
	MenuItemImage* menuItem_notification_disabled = MenuItemImage::create("sprites/main/setting/notification_disabled.png", "sprites/main/setting/notification_enabled.png");

	MenuItemToggle* menuItem_notification = MenuItemToggle::createWithCallback(
		[=] (Object* pSender) {
			MenuItemToggle* pMenuItemToggle = static_cast<MenuItemToggle*>(pSender);

			if(pMenuItemToggle->getSelectedIndex() == 0) {
				UserDefault::getInstance()->setBoolForKey("notification", true);
			}
			else {
				UserDefault::getInstance()->setBoolForKey("notification", false);
			}
		},
		menuItem_notification_enabled,
		menuItem_notification_disabled,
		nullptr
	);

	menuItem_notification->setPosition(0.0f, 0.0f);
	menuItem_notification->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_notification->setSelectedIndex(UserDefault::getInstance()->getBoolForKey("notification", true) ? 0 : 1);

	MenuItemImage* menuItem_sound_enabled = MenuItemImage::create("sprites/main/setting/sound_enabled.png", "sprites/main/setting/sound_disabled.png");
	MenuItemImage* menuItem_sound_disabled = MenuItemImage::create("sprites/main/setting/sound_disabled.png", "sprites/main/setting/sound_enabled.png");

	MenuItemToggle* menuItem_sound = MenuItemToggle::createWithCallback(
		[=] (Object* pSender) {
			MenuItemToggle* pMenuItemToggle = static_cast<MenuItemToggle*>(pSender);

			if(pMenuItemToggle->getSelectedIndex() == 0) {
				UserDefault::getInstance()->setBoolForKey("sound", true);
			}
			else {
				UserDefault::getInstance()->setBoolForKey("sound", false);
			}
		},
		menuItem_sound_enabled,
		menuItem_sound_disabled,
		nullptr
	);

	menuItem_sound->setPosition(102.0f, 0.0f);
	menuItem_sound->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_sound->setSelectedIndex(UserDefault::getInstance()->getBoolForKey("sound", true) ? 0 : 1);

	MenuItemImage* menuItem_vibrate_enabled = MenuItemImage::create("sprites/main/setting/vibrate_enabled.png", "sprites/main/setting/vibrate_disabled.png");
	MenuItemImage* menuItem_vibrate_disabled = MenuItemImage::create("sprites/main/setting/vibrate_disabled.png", "sprites/main/setting/vibrate_enabled.png");

	MenuItemToggle* menuItem_vibrate = MenuItemToggle::createWithCallback(
		[=] (Object* pSender) {
			MenuItemToggle* pMenuItemToggle = static_cast<MenuItemToggle*>(pSender);

			if(pMenuItemToggle->getSelectedIndex() == 0) {
				UserDefault::getInstance()->setBoolForKey("vibrate", true);
			}
			else {
				UserDefault::getInstance()->setBoolForKey("vibrate", false);
			}
		},
		menuItem_vibrate_enabled,
		menuItem_vibrate_disabled,
		nullptr
	);

	menuItem_vibrate->setPosition(204.0f, 0.0f);
	menuItem_vibrate->setAnchorPoint(Point(0.0f, 0.0f));
	menuItem_vibrate->setSelectedIndex(UserDefault::getInstance()->getBoolForKey("vibrate", true) ? 0 : 1);

	Menu* menu_setting = Menu::create(menuItem_notification, menuItem_sound, menuItem_vibrate, nullptr);
	menu_setting->setPosition(104.0f, 290.0f);

	this->addChild(menu_setting);

    return true;
}

// on "init" you need to initialize your instance
bool MainContentInfoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite* sprite_logo = Sprite::create("sprites/main/info/logo.png");
	sprite_logo->setPosition(visibleSize.width / 2, 328.0f);
	sprite_logo->setAnchorPoint(Point(0.5f, 0.0f));

	this->addChild(sprite_logo);

	int current_version = FourCard::VERSION;
	int32_t latest_version = current_version;

	Packet packet((int32_t) Protocol::VERSION);
	FourCardClient::getInstance()->sync_send(packet);
	if(FourCardClient::getInstance()->sync_recv(packet)) {
		packet >> latest_version;
	}

	LabelTTF* label_version_current = LabelTTF::create(__stringf("ÇöÀç¹öÀü   v.%3d", current_version).c_str(), FourCard::DEFAULT_FONT, 20.0f, Size(visibleSize.width, 27.0f), TextHAlignment::CENTER);
	label_version_current->setPosition(0.0f, 265.0f);
	label_version_current->setContentSize(Size(visibleSize.width, 27.0f));
	label_version_current->setAnchorPoint(Point(0.0f, 0.0f));
	label_version_current->setColor(Color3B(0, 0, 0));

	this->addChild(label_version_current);

	LabelTTF* label_version_latest = LabelTTF::create(__stringf("ÃÖ½Å¹öÀü   v.%3d", latest_version).c_str(), FourCard::DEFAULT_FONT, 20.0f, Size(visibleSize.width, 27.0f), TextHAlignment::CENTER);
	label_version_latest->setPosition(0.0f, 215.0f);
	label_version_latest->setContentSize(Size(visibleSize.width, 27.0f));
	label_version_latest->setAnchorPoint(Point(0.0f, 0.0f));
	label_version_latest->setColor(Color3B(0, 0, 0));

	this->addChild(label_version_latest);

	MenuItemImage* menuItem_update = MenuItemImage::create("sprites/main/info/update.png", "sprites/main/info/update.png", [] (Object* pSender) {
	});
	menuItem_update->setAnchorPoint(Point(0.5f, 0.0f));
	if(current_version >= latest_version) {
		menuItem_update->setEnabled(false);
	}

	LabelTTF* label_update = LabelTTF::create("¾÷µ¥ÀÌÆ®", FourCard::DEFAULT_FONT, 20.0f, menuItem_update->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_update->setPosition(menuItem_update->getContentSize().width / 2, menuItem_update->getContentSize().height / 2);
	label_update->setColor(Color3B(60, 60, 60));

	menuItem_update->addChild(label_update);

	Menu* menu_update = Menu::create(menuItem_update, nullptr);
	menu_update->setPosition(visibleSize.width / 2, 100.0f);

	this->addChild(menu_update);

    return true;
}
