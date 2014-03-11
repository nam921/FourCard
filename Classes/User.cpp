#include <User.h>

User User::getUser(string id)
{
	Packet packet(Protocol::DB_RESULT);
	packet << stringf("SELECT * FROM `user` WHERE `id`='%s'", id.c_str());

	if(!FourCard::client->sync_send(packet)) {
	}
	if(!FourCard::client->sync_recv(packet)) {
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

	return user;
}