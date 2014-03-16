#ifndef __FOURCARD_CLIENT_H__
#define __FOURCARD_CLIENT_H__

#include "cocos2d.h"
#include "RealizeClient.h"
#include "../FourCardServer/Protocol.h"
#include "Dialog.h"

USING_NS_CC;
USING_NS_REALIZE;

class FourCardClient : public Client
{
protected:
	static FourCardClient* s_instance;
public:
	FourCardClient(void);
	virtual ~FourCardClient(void);

	static FourCardClient* getInstance();
	static void destroyInstance();

	virtual void onError(const char* message);
	virtual void onWarning(const char* message);
	virtual void onLog(const char* message);
};

#endif // __FOURCARD_CLIENT_H__