#include "FourCardServer.h"
#include <regex>
#include <thread>

//hanc is real troller
unsigned int __stdcall FourCardServer::refresh(void *parameter){
	FourCardServer* server = (FourCardServer*) parameter;

	while(1){
		if(server->is_running()){
			server->m_rank.clear();
			for(auto it = server->users.begin(); it != server->users.end(); it++){
					Rank rank = {it->nick, it->win, it->lose};
					server->m_rank.push_back(rank);
			}
			server->m_file_log<<"rank refresh complete"<<endl;
		}
			Sleep(10800000);
		
	}
	
	return 0;
}


FourCardServer::FourCardServer(void) : m_file_log("FourCardServerLog.txt", ios::app)
{
	if(!m_mysql.connect("127.0.0.1", "root", "", "fourcard", 3306))
	m_file_log << stringf("mysqlserver connect failed")<<endl;

	Rank r={"",0,0};
	m_rank.push_back(r);

	/*
	map<string, string> query_result;
	m_mysql.result("SELECT * FROM test", query_result);
	for(auto it = query_result.begin(); it != query_result.end(); it++) {
		m_file_log << it->first << it->second << endl;
	}*/

	users = m_mysql.sql_result("SELECT * FROM user");
	for(auto it = users.begin(); it != users.end(); it++)
		m_file_log << it->id << it->pw << it->nick << it->elo_normal << it->elo_rank << it->win << it->lose << endl;

	m_refresh = (HANDLE)_beginthreadex(NULL, 0, FourCardServer::refresh, this, 0, NULL);
	
	
	

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
	case Protocol::DB_RESULT_ROWS:
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
				user us = {map_user["id"], map_user["pw"], map_user["nick"], 1200, 1200, 0, 0, 0};
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
			string temp;
			packet >> temp;
			
			int32_t* tot = new int32_t[m_rank.size()];
			string* nick = new string[m_rank.size()];

			int size=0;
			
			for(auto it = m_rank.begin(); it != m_rank.end(); it++, size++){
				tot[size]=it->win+it->lose;
				nick[size]=it->nickname;
			}
			
			
			int32_t tmp;
			string rank="";
			for(int i=size-1; i>=0; i--)
				for(int j=0; j<i; j++)
					if(tot[j]<tot[j+1]){
						tmp=tot[j];
						tot[j]=tot[j+1];
						tot[j+1]=tmp;

						temp=nick[j];
						nick[j]=nick[j+1];
						nick[j+1]=temp;
					}
			
			char Temp[30]="";
			int gofor = size<=10?size:10;

			for(int i=0; i<gofor; i++){
				sprintf(Temp, "%s - %d\n",  nick[i].c_str(), tot[i]);
				rank+=(Temp);
			}
			
			packet.clear();
			packet << rank;
			delete[] tot;
			this->async_send((ClientData*) client_data, packet);



			
			break;
		}

	case Protocol::RANK_WIN:
		{
			string temp;
			packet >> temp;
			
			int32_t* win = new int32_t[m_rank.size()];
			string* nick = new string[m_rank.size()];

			int size=0;
			
			for(auto it = m_rank.begin(); it != m_rank.end(); it++, size++){
				win[size]=it->win;
				nick[size]=it->nickname;
			}
			
			
			int32_t tmp;
			string rank="";
			for(int i=size-1; i>=0; i--)
				for(int j=0; j<i; j++)
					if(win[j]<win[j+1]){
						tmp=win[j];
						win[j]=win[j+1];
						win[j+1]=tmp;

						temp=nick[j];
						nick[j]=nick[j+1];
						nick[j+1]=temp;
					}
			
			char Temp[30]="";
			int gofor = size<=10?size:10;

			for(int i=0; i<gofor; i++){
				sprintf(Temp, "%s - %d\n",  nick[i].c_str(), win[i]);
				rank+=(Temp);
			}
			
			packet.clear();
			packet << rank;
			delete[] win;
			this->async_send((ClientData*) client_data, packet);
			
			break;
		}

	case Protocol::RANK_WINRATE:
		{
			string temp;
			packet >> temp;
			
			double* winrate = new double[m_rank.size()];
			string* nick = new string[m_rank.size()];

			int size=0;
			
			for(auto it = m_rank.begin(); it != m_rank.end(); it++){
				if(it->win>30){
					winrate[size]=100/((double)(it->lose+it->win)/it->win);
					nick[size]=it->nickname;
					size++;
				}
			}
			
			
			double tmp;
			string rank="";
			for(int i=size-1; i>=0; i--)
				for(int j=0; j<i; j++)
					if(winrate[j]<winrate[j+1]){
						tmp=winrate[j];
						winrate[j]=winrate[j+1];
						winrate[j+1]=tmp;

						temp=nick[j];
						nick[j]=nick[j+1];
						nick[j+1]=temp;
					}
			
			char Temp[30]="";
			int gofor = size<=10?size:10;

			for(int i=0; i<gofor; i++){
				sprintf(Temp, "%s - %.2lf\n",  nick[i].c_str(), winrate[i]);
				rank+=(Temp);
			}
			
			packet.clear();
			packet << rank;
			delete[] winrate;
			this->async_send((ClientData*) client_data, packet);
			break;
		}

	case Protocol::VERSION:
		{
			string temp;
			packet >> temp;

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
