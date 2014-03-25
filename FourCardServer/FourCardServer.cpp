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
			server->m_file_log << "rank refresh start"<<endl;
			server->m_rank_win.clear();
			server->m_rank_total.clear();
			server->m_rank_winrate.clear();

			vector<map<string, string>> result_win;
			vector<map<string, string>> result_total;
			vector<map<string, string>> result_winrate;

			// SQL을 사용하여 구현
			server->m_mysql.result("SELECT `nickname`, `win` FROM `user` ORDER BY `win` DESC LIMIT 10", result_win);
			server->m_mysql.result("SELECT `nickname`, `win`+`lose` FROM `user` ORDER BY `win`+`lose` DESC LIMIT 10", result_total);
			server->m_mysql.result("SELECT `nickname`, 100/((`win`+`lose`)/(`win`)) FROM `user` WHERE `win` >= 30 ORDER BY 100/((`win`+`lose`)/(`win`)) DESC LIMIT 10", result_winrate);


			vector<map<string, string>> query_result;


			
			for(auto it=result_win.begin(); it!=result_win.end(); it++){
				string nick;
				string content;
				int j=0;

				for(auto it_col=it->begin(); it_col!=it->end(); it_col++){
					if(j==0) nick = it_col->second;
					if(j==1) content = it_col->second;
					j++;
				}

				Rank m_rank = {nick, content};
				server->m_rank_win.push_back(m_rank);
			}

			for(auto it=result_total.begin(); it!=result_total.end(); it++){
				string nick;
				string content;
				int j=0;

				for(auto it_col=it->begin(); it_col!=it->end(); it_col++){
					if(j==0) nick = it_col->second;
					if(j==1) content = it_col->second;
					j++;
				}

				Rank m_rank = {nick, content};
				server->m_rank_total.push_back(m_rank);
			}

			for(auto it=result_winrate.begin(); it!=result_winrate.end(); it++){
				string nick;
				string content;
				int j=0;

				for(auto it_col=it->begin(); it_col!=it->end(); it_col++){
					if(j==1) nick = it_col->second;
					if(j==0) content = it_col->second;
					j++;
				}

				Rank m_rank = {nick, content};
				server->m_rank_winrate.push_back(m_rank);
			}
			
			
			

			server->m_file_log<<"rank refresh complete"<<(int32_t)result_win.size()<<(int32_t)result_total.size()<<(int32_t)result_winrate.size()<<endl;
			this_thread::sleep_for(chrono::seconds(10800));
		}
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
	m_refresh.detach();

	delete client_data;
}

void FourCardServer::DB_QUERY(const ClientData* client_data, Packet& packet)
{
	string query;
	packet >> query;
	m_mysql.query(query.c_str());
}

void FourCardServer::DB_RESULT(const ClientData* client_data, Packet& packet)
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
}

void FourCardServer::DB_RESULT_ROWS(const ClientData* client_data, Packet& packet)
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
}

void FourCardServer::DB_LOGIN(const ClientData* client_data, Packet& packet)
{
	FourCardClientData* client = (FourCardClientData*) client_data;
	string id;
	string pw;
	packet >> id >> pw;
	packet.clear();

	if(id == "") {
		packet << PROTOCOL_LOGIN_FAIL << "아이디를 입력해주세요.";
	}
	else {
		vector<string> result;
	
		m_mysql.result(stringf("SELECT `id`, `password` FROM `user` where `id` = \'%s\'", id.c_str()).c_str(), result);

		if(result.size()==0){
			packet << PROTOCOL_LOGIN_FAIL << "존재하지 않는 아이디 입니다.";
		}


		else if(result[0] == id) {
			if(result[1] == pw) {
				packet << PROTOCOL_LOGIN_SUCCESS;
				User* user = new User;
				// map을 사용해야 되는 이유 - 추가 / 삭제시 매우 불편함
				vector<string> query_result;

				m_mysql.result(stringf("SELECT `id`, `password`, `nickname`, `email`, `address`, `phone`, `elo_normal`, `elo_rank`, `win`, `lose` FROM `user` WHERE `id` = \'%s\'", id.c_str()).c_str(), query_result);

				packet << (int32_t)query_result.size();
						
						
				user->id = query_result[0];
				user->password = query_result[1];
				user->nickname = query_result[2];
				user->email = query_result[3];
				user->address = query_result[4];
				user->phone = query_result[5];
				user->elo_normal = atoi(query_result[6].c_str());
				user->elo_rank = atoi(query_result[7].c_str());
				user->win = atoi(query_result[8].c_str());
				user->lose = atoi(query_result[9].c_str());

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
}

void FourCardServer::DB_REGISTER(const ClientData* client_data, Packet& packet)
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

    


	regex reg_id("[a-zA-Z0-9]{4,14}");
	regex reg_email("[A-Za-z0-9!#$%&\'*+/=?^_`{|}~-]+(?:\\.[A-Za-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[A-Za-z0-9](?:[A-Za-z0-9-]*[A-Za-z0-9])?\\.)+[A-Za-z0-9](?:[A-Za-z0-9-]*[A-Za-z0-9])");
	//if(4 > map_user["id"].size() || 14 < map_user["id"].size()){
	if(!regex_match(map_user["id"], reg_id)){
		packet << PROTOCOL_REGISTER_FAIL << "아이디를 4-14자의 영어, 숫자로 맞춰주세요.";
	}

	else if(4 > map_user["password"].size() || 14 < map_user["password"].size()){
		packet << PROTOCOL_REGISTER_FAIL << "비밀번호를 4-14자의 영어, 숫자, 특수문자로 맞춰주세요.";
	}

	else if(4 > map_user["nickname"].size() || 14 < map_user["nickname"].size()){
		packet << PROTOCOL_REGISTER_FAIL << "닉네임을 4-14자로 맞춰주세요.";
	}

	else if(!regex_match(map_user["email"], reg_email)){
		packet << PROTOCOL_REGISTER_FAIL << "이메일의 형식을 맞춰주세요.";
	}

	else{
		vector<string> result_id;
		vector<string> result_nick;
		m_mysql.result(stringf("SELECT `id` FROM `user` where `id` = '%s'", map_user["id"].c_str()).c_str(), result_id);
		m_mysql.result(stringf("SELECT `nickname` FROM `user` where `nickname` = '%s'", map_user["nickname"].c_str()).c_str(), result_nick);

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
}

void FourCardServer::DB_LOGOUT(const ClientData* client_data, Packet& packet)
{
	FourCardClientData* client = (FourCardClientData*) client_data;
	m_users.remove(client->m_user);
}

void FourCardServer::RANK_TOTAL(const ClientData* client_data, Packet& packet)
{
	packet.clear();
	packet << (int32_t)m_rank_total.size();
	for(auto it = m_rank_total.begin(); it != m_rank_total.end(); it++)
		packet << it->nickname << (int32_t)atoi(it->content.c_str());
	this->async_send((ClientData*) client_data, packet);
}

void FourCardServer::RANK_WIN(const ClientData* client_data, Packet& packet)
{
	packet.clear();
	packet << (int32_t)m_rank_win.size();
	for(auto it = m_rank_win.begin(); it != m_rank_win.end(); it++)
		packet << it->nickname << (int32_t)atoi(it->content.c_str());
	this->async_send((ClientData*) client_data, packet);
}

void FourCardServer::RANK_WINRATE(const ClientData* client_data, Packet& packet)
{
	packet.clear();
	packet << (int32_t)m_rank_winrate.size();
	for(auto it = m_rank_winrate.begin(); it != m_rank_winrate.end(); it++)
		packet << it->nickname << (float)atof(it->content.c_str());
	this->async_send((ClientData*) client_data, packet);
}

void FourCardServer::VERSION(const ClientData* client_data, Packet& packet)
{
	packet.clear();
	packet<<(int32_t)100;
	this->async_send((ClientData*) client_data, packet);
}

void FourCardServer::onRead(const ClientData* client_data, Packet& packet)
{
	FourCardClientData* client = (FourCardClientData*) client_data;
	
	switch(packet.getID())
	{
	case Protocol::DB_QUERY:
		{
			DB_QUERY(client_data, packet);
			break;
		}
	case Protocol::DB_RESULT:
		{
			DB_RESULT(client_data, packet);
			break;
		}
	case Protocol::DB_RESULT_ROWS:
		{
			DB_RESULT_ROWS(client_data, packet);
			break;
		}

	case Protocol::LOGIN:
		{
			DB_LOGIN(client_data, packet);
			break;
		}

	case Protocol::REGISTER:
		{
			DB_REGISTER(client_data, packet);
			break;
		}

	case Protocol::LOGOUT:
		{
			DB_LOGOUT(client_data, packet);
			break;
		}
		
	case Protocol::RANK_TOTAL:
		{
			RANK_TOTAL(client_data, packet);
			break;
		}
		
	case Protocol::RANK_WIN:
		{
			RANK_WIN(client_data, packet);
			break;
		}

	case Protocol::RANK_WINRATE:
		{
			RANK_WINRATE(client_data, packet);
			break;
		}
		
	case Protocol::VERSION:
		{
			VERSION(client_data, packet);
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
