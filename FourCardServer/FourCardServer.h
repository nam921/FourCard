#pragma once
#include "RealizeServer.h"
#include "FourCardServerProtocol.h"
#include <fstream>
#include "Protocol.h"
#include "rank.h"
#include "User.h"
#include <thread>
#include "FourCardClientData.h"

USING_NS_REALIZE;

class FourCardServer : public Server
{
private:
	MySQL m_mysql;
	ofstream m_file_log;
	list<User*> m_users;
	list<Rank> m_rank;
	thread m_refresh;
	
public:
	

	FourCardServer(void);
	virtual ~FourCardServer(void);

	virtual ClientData* onAccept(SOCKET socket);
	virtual void onAcceptFailed(const ClientData* client_data);
	virtual void onClose(const ClientData* client_data);
	virtual void onRead(const ClientData* client_data, Packet& packet);

	virtual void onError(const char* message);
	virtual void onWarning(const char* message);
	virtual void onLog(const char* message);
	
	static void refresh(FourCardServer*);
};