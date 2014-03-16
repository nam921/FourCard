#include "FourCardClient.h"

FourCardClient* FourCardClient::s_instance = nullptr;

FourCardClient::FourCardClient(void) : Client()
{
}

FourCardClient::~FourCardClient(void)
{
}

FourCardClient* FourCardClient::getInstance()
{
	if(s_instance == nullptr) {
		s_instance = new FourCardClient();
	}
	return s_instance;
}

void FourCardClient::destroyInstance()
{
	if(s_instance != nullptr) {
		delete s_instance;
	}
}

void FourCardClient::onError(const char* message)
{
	Dialog* dialog = Dialog::create();
	dialog->setTitle("통신 중 오류 발생");
	dialog->setMessage(message);
	dialog->addButton("게임 종료", [=] () {
		Director::getInstance()->getRunningScene()->removeChild(dialog);
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	});
	dialog->updateLayout();

	Director::getInstance()->getRunningScene()->addChild(dialog);
}

void FourCardClient::onWarning(const char* message)
{
	Dialog* dialog = Dialog::create();
	dialog->setTitle("통신 중 경고 발생");
	dialog->setMessage(message);
	dialog->addButton("확인", [=] () {
		Director::getInstance()->getRunningScene()->removeChild(dialog);
	});
	dialog->updateLayout();

	Director::getInstance()->getRunningScene()->addChild(dialog);
}

void FourCardClient::onLog(const char* message)
{
	cocos2d::log("log : %s", message);
}