#ifndef __FOURCARD_CLIENT_H__
#define __FOURCARD_CLIENT_H__

#include "cocos2d.h"
#include "RealizeClient.h"
#include "../FourCardServer/Protocol.h"

USING_NS_REALIZE;

class FourCardClient : public Client
{
private:
public:
	FourCardClient(void);
	virtual ~FourCardClient(void);

	virtual void onError(const char* message);
	virtual void onWarning(const char* message);
	virtual void onLog(const char* message);
};

#endif // __FOURCARD_CLIENT_H__