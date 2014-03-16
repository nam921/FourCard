#ifndef __USER_H__
#define __USER_H__

#include "FourCard.h"
#include "FourCardClient.h"

using namespace std;

class User
{
private:
	static string s_logged_in_user_id;
public:
	string m_id;
	string m_nickname;
	int m_win;
	int m_lose;
	
	static User getUser(string id);

	static User getLoggedInUser();
	static void setLoggedInUser(string id);
};

#endif // __USER_H__