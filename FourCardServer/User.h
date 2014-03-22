#pragma once
#include "stdafx.h"
struct User {
	string id;
	string pw;
	string nick;
	int32_t elo_normal;
	int32_t elo_rank;
	int32_t win;
	int32_t lose;
};