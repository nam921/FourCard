#ifndef __FOURCARD_H__
#define __FOURCARD_H__

#include "cocos2d.h"
#include "FourCardClient.h"
#include <fstream>

USING_NS_CC;

namespace FourCard
{
	extern const int VERSION;

	extern const char* SERVER_IP;
	extern const int SERVER_PORT;

	extern FourCardClient* client;

	void Initialize();
	void Release();
}

#endif // __FOURCARD_H__
