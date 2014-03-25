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
	list<Rank> m_rank_win;
	list<Rank> m_rank_winrate;
	list<Rank> m_rank_total;
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

	void DB_QUERY(const ClientData* client_data, Packet& packet);
	void DB_RESULT(const ClientData* client_data, Packet& packet);
	void DB_RESULT_ROWS(const ClientData* client_data, Packet& packet);
	void DB_LOGIN(const ClientData* client_data, Packet& packet);
	void DB_REGISTER(const ClientData* client_data, Packet& packet);
	void DB_LOGOUT(const ClientData* client_data, Packet& packet);
	void RANK_WIN(const ClientData* client_data, Packet& packet);
	void RANK_WINRATE(const ClientData* client_data, Packet& packet);
	void RANK_TOTAL(const ClientData* client_data, Packet& packet);
	void VERSION(const ClientData* client_data, Packet& packet);
	
	static void refresh(FourCardServer*);
};