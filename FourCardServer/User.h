#pragma once
#include "stdafx.h"
struct User {
	string id;
	string password;
	string nickname;
	string email;
	string address;
	string phone;

	int32_t elo_normal;
	int32_t elo_rank;
	int32_t win;
	int32_t lose;
};