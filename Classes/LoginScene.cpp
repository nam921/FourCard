#include "LoginScene.h"
#include "SplashScene.h"

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	
	Sprite* sprite_logo = Sprite::create("sprites/login/logo.png");
	sprite_logo->setPosition(visibleSize.width / 2, 532.0f);
	sprite_logo->setAnchorPoint(Point(0.5f, 0.0f));

	this->addChild(sprite_logo);

	EditBox* editBox_id = EditBox::create(Size(298.0f, 54.0f), Scale9Sprite::create("sprites/login/edit_box.png"));
	editBox_id->setFont("", 16);
	editBox_id->setPlaceHolder("아이디");
	editBox_id->setPosition(Point(visibleSize.width / 2, 458.0f));
	editBox_id->setAnchorPoint(Point(0.5f, 0.0f));
	editBox_id->setFontColor(Color3B(60, 60, 60));
	editBox_id->setMaxLength(14);
	editBox_id->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_id->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_id->setInputFlag(EditBox::InputFlag::SENSITIVE);

	this->addChild(editBox_id);

	EditBox* editBox_password = EditBox::create(Size(298.0f, 54.0f), Scale9Sprite::create("sprites/login/edit_box.png"));
	editBox_password->setFont("", 16);
	editBox_password->setPlaceHolder("비밀번호");
	editBox_password->setPosition(Point(visibleSize.width / 2, 390.0f));
	editBox_password->setAnchorPoint(Point(0.5f, 0.0f));
	editBox_password->setFontColor(Color3B(60, 60, 60));
	editBox_password->setMaxLength(14);
	editBox_password->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_password->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_password->setInputFlag(EditBox::InputFlag::PASSWORD);
	
	this->addChild(editBox_password);

	LabelTTF* label_login = LabelTTF::create("로그인", "", 20.0f, Size(298.0f, 54.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_login->setColor(Color3B(255, 255, 255));

	MenuItemLabel* menuItem_login = MenuItemLabel::create(label_login, [] (Object* pSender) {
		Director::getInstance()->replaceScene(SplashScene::createScene());
	});
	menuItem_login->setContentSize(Size(298.0f, 54.0f));
	menuItem_login->setPosition(Point(149.0f, 27.0f));

	Menu* menu_login = Menu::create(menuItem_login, nullptr);
	menu_login->setPosition(visibleSize.width / 2 - menuItem_login->getContentSize().width / 2, 321.0f);
	menu_login->setContentSize(menuItem_login->getContentSize());
	menu_login->setAnchorPoint(Point(0.5f, 0.0f));
	
	LayerColor* layer_login = LayerColor::create(Color4B(60, 60, 60, 255));
	layer_login->setContentSize(menuItem_login->getContentSize());
	layer_login->setPosition(menu_login->getPosition());

	this->addChild(layer_login);

	this->addChild(menu_login);

	layer_register = Layer::create();
	layer_register->setContentSize(Size(340.0f, 321.0f));
	layer_register->setPosition((visibleSize.width - layer_register->getContentSize().width) / 2, (visibleSize.height - layer_register->getContentSize().height) / 2);
	
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [] (Touch* touch, Event* e) {
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
	listener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer_register);

	Sprite* sprite_register_background = Sprite::create("sprites/login/register/background.png");
	sprite_register_background->setAnchorPoint(Point(0.0f, 0.0f));

	layer_register->addChild(sprite_register_background);

	LabelTTF* label = LabelTTF::create("아이디 *", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 359.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_id = EditBox::create(Size(197.0f, 24.0f), Scale9Sprite::create("sprites/login/register/normal_box.png"));
	editBox_register_id->setFont("", 15);
	editBox_register_id->setPlaceHolder("4 ~ 14자의 영어, 숫자 사용");
	editBox_register_id->setPosition(Point(113.0f, 359.0f));
	editBox_register_id->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_id->setFontColor(Color3B(60, 60, 60));
	editBox_register_id->setMaxLength(14);
	editBox_register_id->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_id->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_register_id->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_id);

	label = LabelTTF::create("비밀번호 *", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 313.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_password = EditBox::create(Size(197.0f, 24.0f), Scale9Sprite::create("sprites/login/register/normal_box.png"));
	editBox_register_password->setFont("", 15);
	editBox_register_password->setPlaceHolder("4 ~ 14자의 영어, 숫자, 특수문자 사용");
	editBox_register_password->setPosition(Point(113.0f, 313.0f));
	editBox_register_password->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_password->setFontColor(Color3B(60, 60, 60));
	editBox_register_password->setMaxLength(14);
	editBox_register_password->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_password->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_register_password->setInputFlag(EditBox::InputFlag::PASSWORD);
	
	layer_register->addChild(editBox_register_password);

	label = LabelTTF::create("비밀번호 확인 *", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 267.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_password_check = EditBox::create(Size(197.0f, 24.0f), Scale9Sprite::create("sprites/login/register/normal_box.png"));
	editBox_register_password_check->setFont("", 15);
	editBox_register_password_check->setPlaceHolder("비밀번호 다시 입력");
	editBox_register_password_check->setPosition(Point(113.0f, 267.0f));
	editBox_register_password_check->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_password_check->setFontColor(Color3B(60, 60, 60));
	editBox_register_password_check->setMaxLength(14);
	editBox_register_password_check->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_password_check->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_register_password_check->setInputFlag(EditBox::InputFlag::PASSWORD);

	layer_register->addChild(editBox_register_password_check);

	label = LabelTTF::create("별명 *", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 221.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_name = EditBox::create(Size(197.0f, 24.0f), Scale9Sprite::create("sprites/login/register/normal_box.png"));
	editBox_register_name->setFont("", 15);
	editBox_register_name->setPlaceHolder("2 ~ 14자");
	editBox_register_name->setPosition(Point(113.0f, 221.0f));
	editBox_register_name->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_name->setFontColor(Color3B(60, 60, 60));
	editBox_register_name->setMaxLength(14);
	editBox_register_name->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_name->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_register_name->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_name);

	label = LabelTTF::create("이메일 *", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 175.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_email = EditBox::create(Size(197.0f, 24.0f), Scale9Sprite::create("sprites/login/register/normal_box.png"));
	editBox_register_email->setFont("", 15);
	editBox_register_email->setPlaceHolder("");
	editBox_register_email->setPosition(Point(113.0f, 175.0f));
	editBox_register_email->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_email->setFontColor(Color3B(60, 60, 60));
	editBox_register_email->setMaxLength(100);
	editBox_register_email->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_email->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
	editBox_register_email->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_email);

	label = LabelTTF::create("주소", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 129.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_address = EditBox::create(Size(197.0f, 24.0f), Scale9Sprite::create("sprites/login/register/normal_box.png"));
	editBox_register_address->setFont("", 15);
	editBox_register_address->setPlaceHolder("도로명주소 입력");
	editBox_register_address->setPosition(Point(113.0f, 129.0f));
	editBox_register_address->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_address->setFontColor(Color3B(60, 60, 60));
	editBox_register_address->setMaxLength(100);
	editBox_register_address->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_address->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBox_register_address->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_address);

	label = LabelTTF::create("연락처", "", 15.0f, Size(113.0f, 24.0f), TextHAlignment::RIGHT, TextVAlignment::CENTER);
	label->setPosition(0.0f, 83.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_phone_1 = EditBox::create(Size(50.0f, 24.0f), Scale9Sprite::create("sprites/login/register/phone_box_1.png"));
	editBox_register_phone_1->setFont("", 15);
	editBox_register_phone_1->setPlaceHolder("");
	editBox_register_phone_1->setPosition(Point(113.0f, 83.0f));
	editBox_register_phone_1->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_phone_1->setFontColor(Color3B(60, 60, 60));
	editBox_register_phone_1->setMaxLength(3);
	editBox_register_phone_1->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_phone_1->setInputMode(EditBox::InputMode::NUMERIC);
	editBox_register_phone_1->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_phone_1);

	label = LabelTTF::create("-", "", 15.0f, Size(15.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setPosition(163.0f, 83.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_phone_2 = EditBox::create(Size(58.0f, 24.0f), Scale9Sprite::create("sprites/login/register/phone_box_2.png"));
	editBox_register_phone_2->setFont("", 15);
	editBox_register_phone_2->setPlaceHolder("");
	editBox_register_phone_2->setPosition(Point(178.0f, 83.0f));
	editBox_register_phone_2->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_phone_2->setFontColor(Color3B(60, 60, 60));
	editBox_register_phone_2->setMaxLength(4);
	editBox_register_phone_2->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_phone_2->setInputMode(EditBox::InputMode::NUMERIC);
	editBox_register_phone_2->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_phone_2);

	label = LabelTTF::create("-", "", 15.0f, Size(17.0f, 24.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setPosition(236.0f, 83.0f);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(60, 60, 60));

	layer_register->addChild(label);

	EditBox* editBox_register_phone_3 = EditBox::create(Size(58.0f, 24.0f), Scale9Sprite::create("sprites/login/register/phone_box_3.png"));
	editBox_register_phone_3->setFont("", 15);
	editBox_register_phone_3->setPlaceHolder("");
	editBox_register_phone_3->setPosition(Point(253.0f, 83.0f));
	editBox_register_phone_3->setAnchorPoint(Point(0.0f, 0.0f));
	editBox_register_phone_3->setFontColor(Color3B(60, 60, 60));
	editBox_register_phone_3->setMaxLength(4);
	editBox_register_phone_3->setReturnType(EditBox::KeyboardReturnType::DONE);
	editBox_register_phone_3->setInputMode(EditBox::InputMode::NUMERIC);
	editBox_register_phone_3->setInputFlag(EditBox::InputFlag::SENSITIVE);

	layer_register->addChild(editBox_register_phone_3);

	MenuItemImage* menuItem_register_ok = MenuItemImage::create("sprites/login/register/button_background.png", "sprites/login/register/button_background.png", [=] (Object* pSender) {
	});
	menuItem_register_ok->setPosition(0.0f, 0.0f);
	menuItem_register_ok->setAnchorPoint(Point(0.0f, 0.0f));

	label = LabelTTF::create("가입", "", 20.0f, menuItem_register_ok->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(255, 255, 255));

	menuItem_register_ok->addChild(label);

	MenuItemImage* menuItem_register_cancel = MenuItemImage::create("sprites/login/register/button_background.png", "sprites/login/register/button_background.png", [=] (Object* pSender) {
		this->removeChild(layer_register, false);
	});
	menuItem_register_cancel->setPosition(162.0f, 0.0f);
	menuItem_register_cancel->setAnchorPoint(Point(0.0f, 0.0f));

	label = LabelTTF::create("취소", "", 20.0f, menuItem_register_cancel->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setAnchorPoint(Point(0.0f, 0.0f));
	label->setColor(Color3B(255, 255, 255));

	menuItem_register_cancel->addChild(label);

	Menu* menu_register_ok_cancel = Menu::create(menuItem_register_ok, menuItem_register_cancel, nullptr);
	menu_register_ok_cancel->setPosition(14.0f, 9.0f);
	menu_register_ok_cancel->setContentSize(Size(311.0f, 54.0f));

	layer_register->addChild(menu_register_ok_cancel);
	layer_register->retain();

	MenuItemLabel* menuItem_register = MenuItemLabel::create(LabelTTF::create("회원가입", "", 15.0f, Size(218.0f, 20.0f), TextHAlignment::CENTER, TextVAlignment::CENTER), [=] (Object* pSender) {
		this->addChild(this->layer_register);
	});
	menuItem_register->setPosition(0.0f, 0.0f);
	menuItem_register->setAnchorPoint(Point(0.5f, 0.0f));
	menuItem_register->setColor(Color3B(60, 60, 60));

	Menu* menu_register = Menu::create(menuItem_register, nullptr);
	menu_register->setPosition(visibleSize.width / 2, 285.0f);
	menu_register->setContentSize(menuItem_login->getContentSize());

	this->addChild(menu_register);

    return true;
}

LoginScene::~LoginScene()
{
	layer_register->release();
}