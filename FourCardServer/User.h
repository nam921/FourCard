#pragma once
#include "RealizeServer.h"
#include "FourCardServerProtocol.h"

struct user{
	string id;
	string nick;
	int32_t elo_normal;
	int32_t elo_rank;
};