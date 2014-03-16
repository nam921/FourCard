#include <User.h>

string User::s_logged_in_user_id = "";

User User::getUser(string id)
{
	Packet packet((int32_t) Protocol::DB_RESULT);
	packet << __stringf("SELECT `id`, `nickname`, `win`, `lose` FROM `user` WHERE `id`='%s'", id.c_str());

	FourCardClient::getInstance()->sync_send(packet);
	if(!FourCardClient::getInstance()->sync_recv(packet)) {
		return User();
	}

	map<string, string> result;
	int32_t number_of_result;
	
	packet >> number_of_result;

	for(int i=0; i<number_of_result; i++) {
		string column, value;
		packet >> column >> value;

		result[column] = value;
	}

	User user;
	user.m_id = result["id"];
	user.m_nickname = result["nickname"];
	user.m_win = atoi(result["win"].c_str());
	user.m_lose = atoi(result["lose"].c_str());

	return user;
}

User User::getLoggedInUser()
{
	return getUser(s_logged_in_user_id);
}
void User::setLoggedInUser(string id)
{
	s_logged_in_user_id = id;
}