#pragma once
#include "ClientData.h"
#include "User.h"

struct FourCardClientData : Realize::ClientData
{
	User* m_user;
};