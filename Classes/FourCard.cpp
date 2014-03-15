#include "FourCard.h"

namespace FourCard
{
	const int VERSION = 10;

	const char* SERVER_IP = "127.0.0.1";
	const int SERVER_PORT = 5807;

	FourCardClient* client;

	void Initialize() {
		client = new FourCardClient();
		client->connect(SERVER_IP, SERVER_PORT);
	}

	void Release() {
		client->disconnect();
		delete client;
	}
}
