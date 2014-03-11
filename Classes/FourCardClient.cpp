#include "FourCardClient.h"

FourCardClient::FourCardClient(void) : Client()
{
}

FourCardClient::~FourCardClient(void)
{
}

void FourCardClient::onError(const char* message)
{
	cocos2d::log("error : %s", message);
}

void FourCardClient::onWarning(const char* message)
{
	cocos2d::log("warning : %s", message);
}

void FourCardClient::onLog(const char* message)
{
	cocos2d::log("log : %s", message);
}