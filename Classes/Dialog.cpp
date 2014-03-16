#include "Dialog.h"

// on "init" you need to initialize your instance
bool Dialog::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 127)) ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	m_dialog = Layer::create();
	this->addChild(m_dialog);
	
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [] (Touch* touch, Event* e) {
		return true;
	};
	listener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	clearLayout();

    return true;
}

void Dialog::setTitle(const char* title)
{
	m_title = title;
}

void Dialog::setMessage(const char* message)
{
	m_message = message;
}

void Dialog::setLayer(Layer* layer)
{
	m_layer = layer;
}

void Dialog::addButton(const char* name, const function<void()>& listener)
{
	m_list_button.push_back(pair<string, function<void()>>(name, listener));
}

void Dialog::clearLayout()
{
	m_title = m_message = "";
	m_layer = nullptr;
	m_list_button.clear();

	m_dialog->removeAllChildren();
}

void Dialog::updateLayout()
{
	Size content_size = this->getContentSize();

	Menu* menu = Menu::create();
	menu->setPosition(15.0f, 10.0f);
	menu->setContentSize(Size(240.0f, 27.0f));

	float button_size = (240.0f - 1.0f * (m_list_button.size() - 1)) / m_list_button.size();
	int i = 0;

	for(auto it = m_list_button.begin(); it != m_list_button.end(); it++, i++) {
		if(it != m_list_button.begin()) {
			DrawObject* draw_line = DrawObject::create();
			draw_line->setPosition(button_size + 1.0f * (i - 1), 1.0f);
			draw_line->setContentSize(Size(1.0f, 25.0f));
			draw_line->setOnDraw([=] () {
				DrawPrimitives::setDrawColor4B(127, 127, 127, 255);
				DrawPrimitives::drawLine(Point(0.0f, 0.0f), Point(0.0f, draw_line->getContentSize().height));
			});
			draw_line->setAnchorPoint(Point(0.0f, 0.0f));

			menu->addChild(draw_line);
		}

		LabelTTF* label = LabelTTF::create(it->first, FourCard::DEFAULT_FONT, 20.0f, Size(button_size, 27.0f), TextHAlignment::CENTER, TextVAlignment::CENTER);
		label->setColor(Color3B(127, 127, 127));
		label->setAnchorPoint(Point(0.0f, 0.0f));

		MenuItemLabel* menuItem = MenuItemLabel::create(label, [=] (Object* pSender) {
			it->second();
		});
		menuItem->setAnchorPoint(Point(0.0f, 0.0f));
		menuItem->setPosition(button_size * i + 1.0f * i, 0.0f);
		
		menu->addChild(menuItem);
	}

	m_dialog->addChild(menu);

	DrawObject* draw_line_message = DrawObject::create();
	draw_line_message->setPosition(15.0f, 47.0f);
	draw_line_message->setContentSize(Size(240.0f, 1.0f));
	draw_line_message->setOnDraw([=] () {
		DrawPrimitives::setDrawColor4B(127, 127, 127, 255);
		DrawPrimitives::drawLine(Point(0.0f, 0.0f), Point(draw_line_message->getContentSize().width, 0.0f));
	});
	draw_line_message->setAnchorPoint(Point(0.0f, 0.0f));

	m_dialog->addChild(draw_line_message);

	if(m_layer != nullptr) {
		m_layer->setPosition(15.0f + (240.0f - m_layer->getContentSize().width) / 2, 48.0f);
		m_dialog->addChild(m_layer);
	}

	LabelTTF* label_message = LabelTTF::create(m_message, FourCard::DEFAULT_FONT, 18.0f, Size(240.0f, 0.0f), TextHAlignment::CENTER);
	label_message->setPosition(15.0f, 63.0f + ((m_layer != nullptr) ? m_layer->getContentSize().height : 0));
	label_message->setColor(Color3B(60, 60, 60));
	label_message->setAnchorPoint(Point(0.0f, 0.0f));

	m_dialog->addChild(label_message);

	DrawObject* draw_line_title = DrawObject::create();
	draw_line_title->setPosition(15.0f, 63.0f + ((m_layer != nullptr) ? m_layer->getContentSize().height : 0) + label_message->getContentSize().height + 15.0f);
	draw_line_title->setContentSize(Size(240.0f, 1.0f));
	draw_line_title->setOnDraw([=] () {
		DrawPrimitives::setDrawColor4B(127, 127, 127, 255);
		DrawPrimitives::drawLine(Point(0.0f, 0.0f), Point(draw_line_title->getContentSize().width, 0.0f));
	});
	draw_line_title->setAnchorPoint(Point(0.0f, 0.0f));

	m_dialog->addChild(draw_line_title);

	LabelTTF* label_title = LabelTTF::create(m_title, FourCard::DEFAULT_FONT, 20.0f, Size(240.0f, 27.0f), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_title->setPosition(15.0f, 78.0f + ((m_layer != nullptr) ? m_layer->getContentSize().height : 0) + label_message->getContentSize().height + 1.0f + 10.0f);
	label_title->setColor(Color3B(60, 60, 60));
	label_title->setAnchorPoint(Point(0.0f, 0.0f));

	m_dialog->addChild(label_title);

	m_dialog->setContentSize(Size(270.0f, 128.0f + ((m_layer != nullptr) ? m_layer->getContentSize().height : 0) + label_message->getContentSize().height));
	m_dialog->setPosition((content_size.width - m_dialog->getContentSize().width) / 2, (content_size.height - m_dialog->getContentSize().height) / 2);

	Scale9Sprite* sprite_background = Scale9Sprite::create(Rect(10, 10, 1, 1), "sprites/dialog/background.png");
	sprite_background->setContentSize(m_dialog->getContentSize());
	sprite_background->setAnchorPoint(Point(0.0f, 0.0f));

	m_dialog->addChild(sprite_background, -1);
}