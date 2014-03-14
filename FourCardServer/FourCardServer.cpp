#include "FourCardServer.h"
#include <regex>

//hanc is real troller

FourCardServer::FourCardServer(void) : m_file_log("FourCardServerLog.txt", ios::app)
{
	if(!m_mysql.connect("127.0.0.1", "root", "", "fourcard", 3306))
	m_file_log << stringf("mysqlserver connect failed")<<endl;

	/*
	map<string, string> query_result;
	m_mysql.result("SELECT * FROM test", query_result);
	for(auto it = query_result.begin(); it != query_result.end(); it++) {
		m_file_log << it->first << it->second << endl;
	}*/

	users = m_mysql.sql_result("SELECT * FROM user");
	for(auto it = users.begin(); it != users.end(); it++) 
		m_file_log << it->id << it->pw << it->nick << it->elo_normal << it->elo_rank << endl;

	/*
	map<string, string> query_result;
	m_mysql.result("select * from user", query_result);
	m_mysql.result("user", query_result);



	m_file_log<<query_result.size()<<"size"<<endl;

	int i=0;
	user temp;
	for(auto it = query_result.begin(); it != query_result.end(); it++, i++){
		

		if(i%4==1){
			user temp={it->first, "pw", 1200, 1200};
			users.push_front(temp);
		}
	}

	for(auto it = query_result.begin(); it != query_result.end(); it++) {
		m_file_log << it->first<< it->second<<endl;
	}*/



}

FourCardServer::~FourCardServer(void)
{
	m_mysql.disconnect();
}

ClientData* FourCardServer::onAccept(SOCKET socket) // onAccept 상태에서는 m_socket이 초기화되지않은 상태 입니다. 바꿀까? 안됨 ㅎㅇㅋㅋ
{
	m_file_log << stringf("FourCardServer::onAccept > %s", getIPFromSocket(socket)) << endl;
	
	ClientData* client_data = new ClientData;
	client_data->m_socket = socket; // onAccept에서 아무런 행동을 수행하지 않을경우 이 줄은 삭제해도 됩니다.

	return client_data;
}

void FourCardServer::onAcceptFailed(const ClientData* client_data)
{
	m_file_log << stringf("FourCardServer::onAcceptFailed > %s", getIPFromSocket(client_data->m_socket)) << endl;
	delete client_data;
}

void FourCardServer::onClose(const ClientData* client_data)
{
	m_file_log << stringf("FourCardServer::onClose > %s", getIPFromSocket(client_data->m_socket)) << endl;
	delete client_data;
}

void FourCardServer::onRead(const ClientData* client_data, Packet& packet)
{
	switch(packet.getID())
	{
	case Protocol::DB_QUERY:
		{
			int32_t awr;
			string query;

			

			packet >> awr >> query;
			packet.clear();

			

			if(m_mysql.query(query.c_str())) {
				packet << "query 성공";
			}

			 packet << "query 실패";

			
			
			

			this->async_send((ClientData*) client_data, packet);
			break;
		}
	case Protocol::DB_RESULT:
		{
			string query;
			packet >> query;

			map<string, string> query_result;
			m_mysql.result(query.c_str(), query_result);

			packet.clear();
			packet << (int32_t) query_result.size();

			for(auto it = query_result.begin(); it != query_result.end(); it++) {
				packet << it->first << it->second;
			}

			this->async_send((ClientData*) client_data, packet);

			break;
		}

	case Protocol::LOGIN:
		{
			string id;
			string pw;
			packet >> id >> pw;
			packet.clear();
			int login=0;

			string login_ID="";
			string login_PW="";
			
			/*
			string query;
			query="SELECT * FROM `user` where `id` = \'"+id+"\'";
			list<user> login_ID = m_mysql.sql_result(query.c_str());

			query="SELECT * FROM `user` where `pw` = \'"+pw+"\'";
			list<user> login_PW = m_mysql.sql_result(query.c_str());*/

			for(auto it = users.begin(); it != users.end(); it++){
				if(it->id==id){
					if(it->pw==pw){
						packet << "Login Complete";
						if(it->login){
							packet.clear();
							packet << "login failed: already logined..";
						}
						else{
							it->login=1;
							login=1;
						}
					}else packet<<"login failed: invaild PW";
				}
			}

			if(!login)packet<<"login failed: invaild ID";
			


			/*
				if(login_ID.size()==0||login_PW.size()==0) packet << "Failed";
				else{
					auto it1 = login_ID.begin();
					auto it2 = login_PW.begin();

					if(login_ID==it2->id){
						packet << "Login Complete: "+ it1->id;
						for(auto it = users.begin(); it != users.end(); it++){
						if(it->id==it1->id){
							if(it->login)
								login=1;
						}
					}
					if(login){
						packet.clear();
						packet<< "login failed: already logined..";
					}

					
					else{
					for(auto it = users.begin(); it != users.end(); it++)
						if(it->id==it1->id)
							it->login=1;

					}
					}
					
				}*/
			

			

			this->async_send((ClientData*) client_data, packet);
			
			break;
		}

	case Protocol::REGISTER:
		{
			map<string, string> map_user;

			int row;
			packet >> row;

			for(int i=0; i<row; i++){
				string column;
				string value;

				packet >> column >> value;

				map_user[column] = value;
			}
			

			m_mysql.insert("user", map_user);

			packet.clear();

			if(m_mysql.getErrno() != 0){
				m_file_log << stringf("mysqlserver query failed")<<endl;
				m_file_log << stringf(m_mysql.getError())<<endl;
				packet<<PROTOCOL_REGISTER_FAIL;
			}

			else{
				packet<<PROTOCOL_REGISTER_SUCCESS;
				user us = {map_user["id"], map_user["pw"], map_user["nick"], 1200, 1200, 0};
				users.push_back(us);
			}

				
	
			

			this->async_send((ClientData*) client_data, packet);

			break;
		}

		

	case Protocol::LOGOUT:
		{
			string id;
			int flag=0;

			packet >> id;

			packet.clear();
			
			for(auto it = users.begin(); it != users.end(); it++)
				if(it->id==id){
					it->login=0;
					flag=1;
				}

			if(!flag) packet << "error: can't find ID";
			else packet << "logout complete.";

			this->async_send((ClientData*) client_data, packet);

			

			break;
		}

	case Protocol::RANK_TOTAL:
		{
			break;
		}

	case Protocol::RANK_WIN:
		{
			break;
		}

	case Protocol::RANK_WINRATE:
		{
			break;
		}

	case Protocol::VERSION:
		{
			packet.clear();
			packet<<"9.0";

			this->async_send((ClientData*) client_data, packet);
			break;
		}

	case -1:
		{
			string content;
			int32_t int_content;

			packet >> content >> int_content;

			packet.clear();
			packet << content + "!" << int_content + 1;

			this->async_send((ClientData*) client_data, packet);

			break;
		}
	}
}

void FourCardServer::onError(const char* message)
{
	m_file_log << message << endl;
}

void FourCardServer::onWarning(const char* message)
{
	m_file_log << message << endl;
}

void FourCardServer::onLog(const char* message)
{
	m_file_log << message << endl;
}
