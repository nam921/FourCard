#include "FourCardServer.h"
#include <regex>
#include <thread>

bool match_regex(TCHAR* strData, TCHAR* pattern){
	string data(strData);
	smatch regexMatchResult;
	regex mPattern(pattern);
	return regex_match(data, regexMatchResult, mPattern);
}

//hanc is real troller
void FourCardServer::refresh(FourCardServer *server){

	while(1){
		if(server->is_running()){
			/*server->m_rank_win.clear();
			vector<string> result;
			// SQL을 사용하여 구현
			server->m_mysql.result("SELECT `win`, `lose` FROM `user` order by win desc 0, 10;", result);
			for(auto it=result.begin(); it!=result.end(); it++){
				
				server->m_rankwin.push_back();
			}

			for(auto it = result.begin(); it != result.end(); it++) {
				
				//packet << it->first << it->second;
			}
			server->m_file_log<<"rank refresh complete"<<endl;*/
		}
		Sleep(10800000);
	}
}


FourCardServer::FourCardServer(void) : m_file_log("FourCardServerLog.txt", ios::app)
{
	if(!m_mysql.connect("127.0.0.1", "root", "", "fourcard", 3306))
		m_file_log << stringf("mysqlserver connect failed")<<endl;

	m_refresh = thread(bind(FourCardServer::refresh, this)); // std:thread 사용 그
}


FourCardServer::~FourCardServer(void)
{
	m_mysql.disconnect();
}

ClientData* FourCardServer::onAccept(SOCKET socket) // onAccept 상태에서는 m_socket이 초기화되지않은 상태 입니다. 바꿀까? 안됨 ㅎㅇㅋㅋ
{
	m_file_log << stringf("FourCardServer::onAccept > %s", getIPFromSocket(socket)) << endl;
	
	FourCardClientData* client_data = new FourCardClientData;
	client_data->m_socket = socket;
	client_data->m_user = nullptr;

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

	const FourCardClientData* client = reinterpret_cast<const FourCardClientData*>(client_data);
	m_users.remove(client->m_user);

	delete client_data;
}

void FourCardServer::onRead(const ClientData* client_data, Packet& packet)
{
	FourCardClientData* client = (FourCardClientData*) client_data;
	
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

			vector<map<string, string>> query_result;
			m_mysql.result(query.c_str(), query_result);

			packet.clear();
			packet << (int32_t) query_result.size();

			for(auto it = query_result.begin(); it != query_result.end(); it++) {
				for(auto it_col = it->begin(); it_col != it->end(); it_col++){
					packet << it_col->first << it_col->second;
				}
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

			if(id == "") {
				packet << PROTOCOL_LOGIN_FAIL << "아이디를 입력해주세요.";
			}
			else {
				vector<string> result;
			
				m_mysql.result(stringf("SELECT `id`, `pw` FROM `user` where `id` = \'%s\'", id.c_str()).c_str(), result);

				if(result.size()==0){
					packet << PROTOCOL_LOGIN_FAIL << "존재하지 않는 아이디 입니다.";
				}


				else if(result[0] == id) {
					if(result[1] == pw) {
						packet << PROTOCOL_LOGIN_SUCCESS;
						User* user = new User;
						// map을 사용해야 되는 이유 - 추가 / 삭제시 매우 불편함
						vector<string> query_result;

						m_mysql.result(stringf("SELECT `id`, `pw`, `nick`, `elo_normal`, `elo_rank`, `win`, `lose` FROM `user` WHERE `id` = \'%s\'", id.c_str()).c_str(), query_result);

						//packet << (int32_t)query_result.size();
						
						
						user->id = query_result[0];
						user->pw = query_result[1];
						user->nick = query_result[2];
						user->elo_normal = atoi(query_result[3].c_str());
						user->elo_rank = atoi(query_result[4].c_str());
						user->win = atoi(query_result[5].c_str());
						user->lose = atoi(query_result[6].c_str());

						client->m_user=user;
					}
					else {
						packet << PROTOCOL_LOGIN_FAIL << "비밀번호가 틀립니다.";
					}
				}
				else {
					packet << PROTOCOL_LOGIN_FAIL << "존재하지 않는 아이디 입니다.";
				}
			}

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
			
			packet.clear();
			//packet << (int32_t)map_user.size();
			
			if(4 > map_user["id"].size() || 14 < map_user["id"].size()){
				packet << PROTOCOL_REGISTER_FAIL << "아이디를 4-14자로 맞춰주세요.";
			}

			else if(4 > map_user["pw"].size() || 14 < map_user["pw"].size()){
				packet << PROTOCOL_REGISTER_FAIL << "비밀번호를 4-14자로 맞춰주세요.";
			}

			else if(4 > map_user["nick"].size() || 14 < map_user["nick"].size()){
				packet << PROTOCOL_REGISTER_FAIL << "닉네임을 4-14자로 맞춰주세요.";
			}

			else{
				vector<string> result_id;
				vector<string> result_nick;
				m_mysql.result(stringf("SELECT `id` FROM `user` where `id` = '%s'", map_user["id"].c_str()).c_str(), result_id);
				m_mysql.result(stringf("SELECT `nick` FROM `user` where `nick` = '%s'", map_user["nick"].c_str()).c_str(), result_nick);

				if(result_id.size() != 0){
					packet << PROTOCOL_REGISTER_FAIL << "이미 존재하는 아이디 입니다.";
				}

				else if(result_nick.size() != 0){
					packet << PROTOCOL_REGISTER_FAIL << "이미 존재하는 닉네임 입니다.";
				}

				else{
					m_mysql.insert("user", map_user);

					if(m_mysql.getErrno() != 0){
						m_file_log << stringf("mysqlserver query failed")<<endl;
						m_file_log << stringf(m_mysql.getError())<<endl;
						packet<<PROTOCOL_REGISTER_FAIL;
					}

					else{
						packet<<PROTOCOL_REGISTER_SUCCESS;
					}
				}
			}

				
	
			

			this->async_send((ClientData*) client_data, packet);

			break;
		}

		

	case Protocol::LOGOUT:
		{

			m_users.remove(client->m_user);

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
			int32_t gofor = size<=10?size:10;

			packet.clear();
			packet<<gofor;
			for(int i=0; i<gofor; i++){
				//sprintf(Temp, "%s - %d\n",  nick[i].c_str(), tot[i]);
				//rank+=(Temp);
				packet<<nick[i]<<tot[i];
			}
			
			//packet.clear();
			//packet << rank;
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
			int32_t gofor = size<=10?size:10;
			packet.clear();
			packet << gofor;

			for(int i=0; i<gofor; i++){
				//sprintf(Temp, "%s - %d\n",  nick[i].c_str(), win[i]);
				//rank+=(Temp);
				packet<<nick[i]<<win[i];
			}
			
			//packet.clear();
			//packet << rank;
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
			packet<<100;

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
