#ifndef __USER_H__
#define __USER_H__

#include "FourCard.h"

using namespace std;

class User
{
public:
	string m_id;

	static User getUser(string id);
};

#endif // __USER_H__